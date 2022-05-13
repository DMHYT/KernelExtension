#include <jni.h>

#include <innercore/id_conversion_map.h>
#include <innercore/item_extra.h>
#include <innercore/item_registry.h>
#include <innercore/vtable.h>

#include <commontypes.hpp>

#include <LocalPlayer.hpp>

#include "../utils/java_utils.hpp"


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_Player_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(jboolean, IsAutoJumpEnabled) {
        VTABLE_FIND_OFFSET(Player_isAutoJumpEnabled, _ZTV6Player, _ZNK6Player17isAutoJumpEnabledEv);
        return VTABLE_CALL<bool>(Player_isAutoJumpEnabled, (Player*) ptr);
    }
    __EXPORT__(jint, GetCommandPermissionLevel) {
        VTABLE_FIND_OFFSET(Player_getCommandPermissionLevel, _ZTV6Player, _ZNK6Player25getCommandPermissionLevelEv);
        return VTABLE_CALL<int>(Player_getCommandPermissionLevel, (Player*) ptr);
    }
    __EXPORT__(void, SetPermissions, jint level) {
        VTABLE_FIND_OFFSET(Player_setPermissions, _ZTV6Player, _ZN6Player14setPermissionsE22CommandPermissionLevel);
        VTABLE_CALL<void>(Player_setPermissions, (Player*) ptr, (CommandPermissionLevel) level);
    }
    __EXPORT__(jint, GetPlayerPermissionLevel) {
        return (int) ((Player*) ptr)->getPlayerPermissionLevel();
    }
    __EXPORT__(void, DisplayChatMessage, jstring prefix, jstring message) {
        const char* cPrefix = env->GetStringUTFChars(prefix, 0);
        const char* cMessage = env->GetStringUTFChars(message, 0);
        VTABLE_FIND_OFFSET(Player_displayChatMessage, _ZTV6Player, _ZN6Player18displayChatMessageERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES8_);
        VTABLE_CALL<void>(Player_displayChatMessage, (Player*) ptr, std::__ndk1::string(cPrefix), std::__ndk1::string(cMessage));
        env->ReleaseStringUTFChars(prefix, cPrefix);
        env->ReleaseStringUTFChars(message, cMessage);
    }
    __EXPORT__(void, DisplayClientMessage, jstring message) {
        const char* cMessage = env->GetStringUTFChars(message, 0);
        VTABLE_FIND_OFFSET(Player_displayClientMessage, _ZTV6Player, _ZN6Player20displayClientMessageERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE);
        VTABLE_CALL<void>(Player_displayClientMessage, (Player*) ptr, std::__ndk1::string(cMessage));
        env->ReleaseStringUTFChars(message, cMessage);
    }
    __EXPORT__(void, DisplayWhisperMessage, jstring s1, jstring s2, jstring s3, jstring s4) {
        const char* c1 = env->GetStringUTFChars(s1, 0);
        const char* c2 = env->GetStringUTFChars(s2, 0);
        const char* c3 = env->GetStringUTFChars(s3, 0);
        const char* c4 = env->GetStringUTFChars(s4, 0);
        VTABLE_FIND_OFFSET(Player_displayWhisperMessage, _ZTV6Player, _ZN6Player21displayWhisperMessageERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES8_S8_S8_);
        VTABLE_CALL<void>(Player_displayWhisperMessage, (Player*) ptr, std::__ndk1::string(c1), std::__ndk1::string(c2), std::__ndk1::string(c3), std::__ndk1::string(c4));
        env->ReleaseStringUTFChars(s1, c1);
        env->ReleaseStringUTFChars(s2, c2);
        env->ReleaseStringUTFChars(s3, c3);
        env->ReleaseStringUTFChars(s4, c4);
    }
    __EXPORT__(void, StartSleepInBed, jint x, jint y, jint z) {
        VTABLE_FIND_OFFSET(Player_startSleepInBed, _ZTV6Player, _ZN6Player15startSleepInBedERK8BlockPos);
        VTABLE_CALL<void>(Player_startSleepInBed, (Player*) ptr, BlockPos(x, y, z));
    }
    __EXPORT__(void, StopSleepInBed, jboolean b1, jboolean b2) {
        VTABLE_FIND_OFFSET(Player_stopSleepInBed, _ZTV6Player, _ZN6Player14stopSleepInBedEbb);
        VTABLE_CALL<void>(Player_stopSleepInBed, (Player*) ptr, b1, b2);
    }
    __EXPORT__(jboolean, CanStartSleepInBed) {
        VTABLE_FIND_OFFSET(Player_canStartSleepInBed, _ZTV6Player, _ZN6Player18canStartSleepInBedEv);
        return VTABLE_CALL<bool>(Player_canStartSleepInBed, (Player*) ptr);
    }
    __EXPORT__(jint, GetSleepTimer) {
        VTABLE_FIND_OFFSET(Player_getSleepTimer, _ZTV6Player, _ZNK6Player13getSleepTimerEv);
        return VTABLE_CALL<int>(Player_getSleepTimer, (Player*) ptr);
    }
    __EXPORT__(jint, GetPreviousTickSleepTimer) {
        VTABLE_FIND_OFFSET(Player_getPreviousTickSleepTimer, _ZTV6Player, _ZNK6Player25getPreviousTickSleepTimerEv);
        return VTABLE_CALL<int>(Player_getPreviousTickSleepTimer, (Player*) ptr);
    }
    __EXPORT__(void, OpenSign, jint x, jint y, jint z) {
        VTABLE_FIND_OFFSET(Actor_isLocalPlayer, _ZTV5Actor, _ZNK5Actor13isLocalPlayerEv);
        if(VTABLE_CALL<bool>(Actor_isLocalPlayer, (Actor*) ptr)) {
            LocalPlayer* localPlayer = (LocalPlayer*) ptr;
            BlockPos pos(x, y, z);
            BlockSource* region = ((Actor*) ptr)->getRegion();
            if(region != nullptr) {
                BlockActor* tile = region->getBlockEntity(pos);
                if(tile != nullptr && tile->type == BlockActorType::SIGN) {
                    std::__ndk1::string& signMessage = ((SignBlockActor*) tile)->getMessage();
                    ClientInstance* clientInstance = localPlayer->getClientInstance();
                    if(clientInstance != nullptr) {
                        VTABLE_FIND_OFFSET(ClientInstance_getClientSceneStack, _ZTV14ClientInstance, _ZNK14ClientInstance19getClientSceneStackEv);
                        VTABLE_FIND_OFFSET(ClientInstance_getSceneFactory, _ZTV14ClientInstance, _ZNK14ClientInstance15getSceneFactoryEv);
                        SceneStack* sceneStack = VTABLE_CALL<SceneStack*>(ClientInstance_getClientSceneStack, clientInstance);
                        SceneFactory* sceneFactory = VTABLE_CALL<SceneFactory*>(ClientInstance_getSceneFactory, clientInstance);
                        if(sceneStack != nullptr && sceneFactory != nullptr) {
                            std::__ndk1::shared_ptr<UIScene> scene = sceneFactory->createSignScreen(pos);
                            sceneStack->pushScreen(scene, false);
                            KEXJavaBridge::KernelExtension::setMinecraftTextboxText(signMessage.c_str());
                        }
                    }
                }
            }
        }
    }
    __EXPORT__(void, PlayEmote, jstring emote) {
        const char* cEmote = env->GetStringUTFChars(emote, 0);
        VTABLE_FIND_OFFSET(Player_playEmote, _ZTV6Player, _ZN6Player9playEmoteERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE);
        VTABLE_CALL<void>(Player_playEmote, (Player*) ptr, std::__ndk1::string(cEmote));
        env->ReleaseStringUTFChars(emote, cEmote);
    }
    __EXPORT__(jboolean, IsHostingPlayer) {
        VTABLE_FIND_OFFSET(Player_isHostingPlayer, _ZTV6Player, _ZNK6Player15isHostingPlayerEv);
        return VTABLE_CALL<bool>(Player_isHostingPlayer, (Player*) ptr);
    }
    __EXPORT__(void, SetGameMode, jint mode) {
        VTABLE_FIND_OFFSET(Player_setPlayerGameType, _ZTV6Player, _ZN6Player17setPlayerGameTypeE8GameType);
        VTABLE_CALL<void>(Player_setPlayerGameType, (Player*) ptr, mode);
    }
    __EXPORT__(void, AddLevels, jint levels) {
        VTABLE_FIND_OFFSET(Player_addLevels, _ZTV6Player, _ZN6Player9addLevelsEi);
        VTABLE_CALL<void>(Player_addLevels, (Player*) ptr, levels);
    }
    __EXPORT__(void, SetFieldOfViewModifier, jfloat modifier) {
        VTABLE_FIND_OFFSET(Player_setFOVModifier, _ZTV6Player, _ZN6Player22setFieldOfViewModifierEf);
        VTABLE_CALL<void>(Player_setFOVModifier, (Player*) ptr, modifier);
    }
    __EXPORT__(void, StartCooldown, jint id) {
        int dynamicId = IdConversion::staticToDynamic(id, IdConversion::ITEM);
        Item* item = ItemRegistry::getItemById(dynamicId);
        if(item != nullptr) {
            VTABLE_FIND_OFFSET(Player_startCooldown, _ZTV6Player, _ZN6Player13startCooldownEPK4Item);
            VTABLE_CALL<void>(Player_startCooldown, (Player*) ptr, item);
        }
    }
    // TODO getItemCooldownLeft, isItemInCooldown
    __EXPORT__(void, StartGliding) {
        ((Player*) ptr)->startGliding();
    }
    __EXPORT__(void, StopGliding) {
        ((Player*) ptr)->stopGliding();
    }
    __EXPORT__(jboolean, IsChatAllowed) {
        return ((Player*) ptr)->isChatAllowed();
    }
    __EXPORT__(jboolean, GetHasSeenCredits) {
        return ((Player*) ptr)->getHasSeenCredits();
    }
    __EXPORT__(void, SetHasSeenCredits, jboolean seen) {
        ((Player*) ptr)->setHasSeenCredits(seen);
    }
    __EXPORT__(jboolean, ShouldShowCredits) {
        return ((Player*) ptr)->shouldShowCredits();
    }
    __EXPORT__(jint, GetLuck) {
        return ((Player*) ptr)->getLuck();
    }
    __EXPORT__(jboolean, ForceAllowEating) {
        return ((Player*) ptr)->forceAllowEating();
    }
    __EXPORT__(void, Eat, jint nutrition, jfloat saturation) {
        Player* player = (Player*) ptr;
        VTABLE_FIND_OFFSET(Actor_getAttribute, _ZTV5Actor, _ZNK5Actor12getAttributeERK9Attribute);
        if(nutrition > 0) {
            AttributeInstance* hunger = VTABLE_CALL<AttributeInstance*>(Actor_getAttribute, player, Player::HUNGER);
            InstantaneousAttributeBuff buff((float) nutrition, (AttributeBuffType) 10);
            hunger->addBuff(buff);
        }
        if(saturation > 0.0f) {
            AttributeInstance* sat = VTABLE_CALL<AttributeInstance*>(Actor_getAttribute, player, Player::SATURATION);
            sat->setMaxValue(sat->getCurrentValue());
            InstantaneousAttributeBuff buff(saturation, (AttributeBuffType) 10);
            sat->addBuff(buff);
        }
    }
    __EXPORT__(void, Eat2, jint nutrition, jfloat saturationModifier) {
        ((Player*) ptr)->eat(nutrition, saturationModifier);
    }
    __EXPORT__(void, CauseFoodExhaustion, jfloat value) {
        ((Player*) ptr)->causeFoodExhaustion(value);
    }
    __EXPORT__(jboolean, IsBouncing) {
        return ((Player*) ptr)->isBouncing();
    }
    __EXPORT__(jboolean, IsForcedRespawn) {
        return ((Player*) ptr)->isForcedRespawn();
    }
    __EXPORT__(jint, GetEnchantmentSeed) {
        return ((Player*) ptr)->getEnchantmentSeed();
    }
    __EXPORT__(void, SetEnchantmentSeed, jint seed) {
        ((Player*) ptr)->setEnchantmentSeed(seed);
    }
    __EXPORT__(jint, GetNewEnchantmentSeed) {
        return ((Player*) ptr)->getNewEnchantmentSeed();
    }
    __EXPORT__(jint, GetTicksUsingItem) {
        return ((Player*) ptr)->getTicksUsingItem();
    }
    __EXPORT__(jboolean, CanUseOperatorBlocks) {
        return ((Player*) ptr)->canUseOperatorBlocks();
    }
    __EXPORT__(jboolean, IsOperator) {
        return ((Player*) ptr)->isOperator();
    }
    __EXPORT__(jboolean, IsViewer) {
        return ((Player*) ptr)->isViewer();
    }
    __EXPORT__(jint, GetXpNeededForNextLevel) {
        return ((Player*) ptr)->getXpNeededForNextLevel();
    }
    __EXPORT__(jint, GetXpNeededForLevelRange, jint min, jint max) {
        return ((Player*) ptr)->getXpNeededForLevelRange(min, max);
    }
    __EXPORT__(jboolean, IsEmoting) {
        return ((Player*) ptr)->isEmoting();
    }
    __EXPORT__(jfloat, GetLevelProgress) {
        return ((Player*) ptr)->getLevelProgress();
    }
    // TODO [has/get]Respawn[Anchor]Position()
    __EXPORT__(jint, GetMapIndex) {
        return ((Player*) ptr)->getMapIndex();
    }
    __EXPORT__(void, SetMapIndex, jint index) {
        ((Player*) ptr)->setMapIndex(index);
    }
    __EXPORT__(jint, GetAttackDamage) {
        return ((Player*) ptr)->getAttackDamage();
    }
    __EXPORT__(jboolean, IsHungry) {
        return ((Player*) ptr)->isHungry();
    }
    __EXPORT__(jboolean, IsInRaid) {
        return ((Player*) ptr)->isInRaid();
    }
    __EXPORT__(jboolean, HasOpenContainer) {
        return ((Player*) ptr)->hasOpenContainer();
    }
    __EXPORT__(jboolean, IsUsingItem) {
        return ((Player*) ptr)->isUsingItem();
    }
    __EXPORT__(jfloat, GetUnderwaterLightLevel) {
        return ((Player*) ptr)->getUnderwaterLightLevel();
    }
    __EXPORT__(void, SetUnderwaterLightLevel, jfloat level) {
        ((Player*) ptr)->setUnderwaterLightLevel(level);
    }
    __EXPORT__(jboolean, CanBeSeenOnMap) {
        return ((Player*) ptr)->canBeSeenOnMap();
    }
}


#undef __EXPORT__