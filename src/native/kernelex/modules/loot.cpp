#include <regex>
#include <hook.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include "../../../../../../DMH/cppheaders/json/value.h"
#include "../../../../../../DMH/cppheaders/json/reader.h"
#include "../utils/java_utils.hpp"
#include "loot.hpp"


Json::Reader* KEXLootModule::jsonReader = new Json::Reader();
std::unordered_map<std::string, std::string> KEXLootModule::cachedModifiedTables;

std::string KEXLootModule::getLootTableName(LootTable* table) {
    std::__ndk1::string tableDir = table->getDir();
    std::string tableName = std::regex_replace(std::string(tableDir.c_str()), std::regex("loot_tables/"), "");
    tableName = std::regex_replace(tableName, std::regex(".json"), "");
    return tableName;
}

void KEXLootModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    HookManager::addCallback(SYMBOL("mcpe", "_ZN9LootTable11deserializeEN4Json5ValueE"), LAMBDA((HookManager::CallbackController* controller, LootTable* table, Json::Value* json), {
        std::string tableName = getLootTableName(table);
        auto search = cachedModifiedTables.find(tableName);
        if(search != cachedModifiedTables.end()) {
            Json::Value newJson(0);
            jsonReader->parse(std::__ndk1::string(search->second.c_str()), newJson, true);
            void* result = controller->callAndReplace<void*>(table, &newJson);
            return result;
        } else {
            JNIEnv* env = KEXJavaUtils::attach();
            Json::Value newJson = nullptr;
            jstring modified = KEXJavaBridge::LootModule::modify(tableName.c_str(), json->toStyledString().c_str());
            if(modified != NULL) {
                const char* cModified = env->GetStringUTFChars(modified, 0);
                cachedModifiedTables.emplace(tableName, std::string(cModified));
                newJson = Json::Value(0);
                jsonReader->parse(std::__ndk1::string(cModified), newJson, true);
                env->ReleaseStringUTFChars(modified, cModified);
            }
            if(newJson != nullptr) {
                void* result = controller->callAndReplace<void*>(table, &newJson);
                return result;
            }
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
}