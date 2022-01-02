#include <regex>
#include <hook.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include "../../../../../../DMH/cppheaders/json/value.h"
#include "loot.hpp"


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
            Json::Value newJson(search->second.c_str());
            return controller->callAndReplace<void>(newJson);
        } else {
            JNIEnv* env;
            ATTACH_JAVA(env, JNI_VERSION_1_4) {
                jclass clazz = env->FindClass("vsdum/kex/modules/LootModule");
                jmethodID method = env->GetStaticMethodID(clazz, "modify", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
                jstring jTableName = env->NewStringUTF(tableName.c_str());
                jstring jTableJson = env->NewStringUTF(json->toStyledString().c_str());
                jobject result = env->CallStaticObjectMethod(clazz, method, jTableName, jTableJson);
                if(result != NULL) {
                    const char* cmodified = env->GetStringUTFChars((jstring) result, 0);
                    cachedModifiedTables.insert(std::unordered_map<std::string, std::string>::value_type(tableName, std::string(cmodified)));
                    Json::Value newJson(cmodified);
                    env->ReleaseStringUTFChars((jstring) result, cmodified);
                    return controller->callAndReplace<void>(newJson);
                }
            }
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
}