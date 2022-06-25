#include <cstdlib>
#include <cstring>
#include <jni.h>

#include <static_symbol.h>

#include <loot/LootTableContext.hpp>


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_LootTableContext_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jlong, GetThisEntity) {
        Actor* actor = ((LootTableContext*) ptr)->getThisEntity();
        if(actor == nullptr) return 0;
        return (jlong) actor;
    }
    __EXPORT__(jstring, GetOriginalItemName) {
        auto name = ((LootTableContext*) ptr)->getOriginalItemName();
        return name.empty() ? NULL : env->NewStringUTF(name.c_str());
    }
    __EXPORT__(jlong, GetLevel) {
        Level* level = ((LootTableContext*) ptr)->getLevel();
        if(level == nullptr) return 0;
        return (jlong) level;
    }
    __EXPORT__(jfloat, GetExplosionRadius) {
        return ((LootTableContext*) ptr)->getExplosionRadius();
    }
    __EXPORT__(jfloat, GetLuck) {
        return ((LootTableContext*) ptr)->getLuck();
    }
    __EXPORT__(jlong, GetKillerPlayer) {
        Player* player = ((LootTableContext*) ptr)->getKillerPlayer();
        if(player == nullptr) return 0;
        return (jlong) player;
    }
    __EXPORT__(jlong, GetKillerPet) {
        Actor* actor = ((LootTableContext*) ptr)->getKillerPet();
        if(actor == nullptr) return 0;
        return (jlong) actor;
    }
    __EXPORT__(jlong, GetKillerEntity) {
        Actor* actor = ((LootTableContext*) ptr)->getKillerEntity();
        if(actor == nullptr) return 0;
        return (jlong) actor;
    }
    // TODO getDeathSource
    __EXPORT__(void, SetOriginalItemName, jstring name) {
        const char* cName = env->GetStringUTFChars(name, 0);
        ((LootTableContext*) ptr)->setOriginalItemName(cName);
        env->ReleaseStringUTFChars(name, cName);
    }
    __EXPORT__(jlong, BuilderConstruct) {
        LootTableContext::Builder* b = new LootTableContext::Builder((Level*) ptr);
        return (jlong) b;
    }
    __EXPORT__(void, BuilderExplosionRadius, jfloat radius) {
        ((LootTableContext::Builder*) ptr)->withExplosionRadius(radius);
    }
    __EXPORT__(void, BuilderThisEntity, jlong actorPtr) {
        ((LootTableContext::Builder*) ptr)->withThisEntity((Actor*) actorPtr);
    }
    __EXPORT__(void, BuilderLuck, jfloat luck) {
        ((LootTableContext::Builder*) ptr)->withLuck(luck);
    }
    __EXPORT__(void, BuilderItemName, jstring itemName) {
        const char* cName = env->GetStringUTFChars(itemName, 0);
        stl::string cppName(cName);
        ((LootTableContext::Builder*) ptr)->withOriginalItemName(cppName);
        env->ReleaseStringUTFChars(itemName, cName);
    }
    __EXPORT__(void, BuilderKillerPlayer, jlong playerPtr) {
        ((LootTableContext::Builder*) ptr)->withKillerPlayer((Player*) playerPtr);
    }
    // TODO withDeathSource
    __EXPORT__(jlong, BuilderCreate) {
        LootTableContext ctx = ((LootTableContext::Builder*) ptr)->create();
        LootTableContext* result = (LootTableContext*) malloc(56);
        memcpy(result, &ctx, 56);
        return (jlong) result;
    }
    __EXPORT__(void, FinalizeContext) {
        STATIC_SYMBOL(LootTableContextDestructor, "_ZN16LootTableContextD2Ev", (LootTableContext*), void);
        LootTableContextDestructor((LootTableContext*) ptr);
    }
    __EXPORT__(void, FinalizeBuilder) {
        delete ((LootTableContext::Builder*) ptr);
    }
}


#undef __EXPORT__