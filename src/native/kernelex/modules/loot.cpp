#include <regex>
#include <hook.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <logger.h>
#include "../../../../../../DMH/cppheaders/json/value.h"
#include "../../../../../../DMH/cppheaders/json/reader.h"
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
            JNIEnv* env;
            Json::Value newJson = nullptr;
            ATTACH_JAVA(env, JNI_VERSION_1_4) {
                jclass clazz = env->FindClass("vsdum/kex/modules/LootModule");
                jmethodID method = env->GetStaticMethodID(clazz, "modify", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
                jstring jTableName = env->NewStringUTF(tableName.c_str());
                jstring jTableJson = env->NewStringUTF(json->toStyledString().c_str());
                jobject result = env->CallStaticObjectMethod(clazz, method, jTableName, jTableJson);
                if(result != NULL) {
                    const char* cmodified = env->GetStringUTFChars((jstring) result, 0);
                    Logger::debug("KEX", "Modified LootTable from Java: %s", cmodified);
                    Logger::flush();
                    cachedModifiedTables.insert(std::unordered_map<std::string, std::string>::value_type(tableName, std::string(cmodified)));
                    newJson = Json::Value(0);
                    jsonReader->parse(std::__ndk1::string(cmodified), newJson, true);
                    env->ReleaseStringUTFChars((jstring) result, cmodified);
                }
            }
            if(newJson != nullptr) {
                void* result = controller->callAndReplace<void*>(table, &newJson);
                return result;
            }
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
}