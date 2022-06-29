#include <jni.h>
#include <string>

#include <static_symbol.h>

#include <innercore/block_registry.h>
#include <innercore/id_conversion_map.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/vtable.h>

#include <commontypes.hpp>

#include <Actor.hpp>
#include <BlockLegacy.hpp>
#include <Item.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>

#include "../../utils/java_utils.hpp"
#include "tooltypes/custom.hpp"
#include "module.hpp"


extern "C" {
    JNIEXPORT jlongArray JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGrabVanillaItemTiers
    (JNIEnv* env, jclass) {
        jlongArray result = env->NewLongArray(6);
        jlong fill[6];
        fill[0] = (jlong)( &VanillaItemTiers::WOOD );
        fill[1] = (jlong)( &VanillaItemTiers::STONE );
        fill[2] = (jlong)( &VanillaItemTiers::IRON );
        fill[3] = (jlong)( &VanillaItemTiers::DIAMOND );
        fill[4] = (jlong)( &VanillaItemTiers::GOLD );
        fill[5] = (jlong)( &VanillaItemTiers::NETHERITE );
        env->SetLongArrayRegion(result, 0, 6, fill);
        return result;
    }
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeNewItemTier
    (JNIEnv*, jclass, jint level, jint uses, jfloat speed, jint attackDamageBonus, jint enchantmentValue) {
        Item::Tier* tier = new Item::Tier(level, uses, speed, attackDamageBonus, enchantmentValue);
        return (jlong) tier;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetItemTierLevel
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getLevel();
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetItemTierUses
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getUses();
    }
    JNIEXPORT jfloat JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetItemTierSpeed
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getSpeed();
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetItemTierAttackDamageBonus
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getAttackDamageBonus();
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetItemTierEnchantmentValue
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getEnchantmentValue();
    }
    JNIEXPORT jfloat JNICALL Java_vsdum_kex_modules_ToolsModule_getBlockDestroyTime
    (JNIEnv*, jclass, jint id) {
        int dynamicId = IdConversion::staticToDynamic(id, IdConversion::BLOCK);
        BlockLegacy* block = BlockRegistry::getBlockById(dynamicId);
        if(block != nullptr) {
            return block->getDestroySpeed();
        }
        return 0.0f;
    }
    JNIEXPORT jstring JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetBlockMaterialName
    (JNIEnv* env, jclass, jint id) {
        std::string materialName = KEXToolsModule::ToolAPI::getBlockMaterialName(id);
        if(materialName.empty()) return NULL;
        return env->NewStringUTF(materialName.c_str());
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetBlockDestroyLevel
    (JNIEnv*, jclass, jint id) {
        return KEXToolsModule::ToolAPI::getBlockDestroyLevel(id);
    }
    JNIEXPORT jboolean JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetBlockIsNative
    (JNIEnv*, jclass, jint id) {
        return KEXToolsModule::ToolAPI::getBlockIsNative(id);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeSetBlockMaterialName
    (JNIEnv* env, jclass, jint id, jstring materialName) {
        const char* cMaterialName = env->GetStringUTFChars(materialName, 0);
        KEXToolsModule::ToolAPI::setBlockMaterialName(id, cMaterialName);
        env->ReleaseStringUTFChars(materialName, cMaterialName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeSetBlockDestroyLevel
    (JNIEnv*, jclass, jint id, jint destroyLevel) {
        KEXToolsModule::ToolAPI::setBlockDestroyLevel(id, destroyLevel);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeSetBlockIsNative
    (JNIEnv*, jclass, jint id, jboolean isNative) {
        KEXToolsModule::ToolAPI::setBlockIsNative(id, isNative);
    }
    JNIEXPORT jobject JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetBlockData
    (JNIEnv* env, jclass, jint id) {
        auto found = KEXToolsModule::Data::blockData.find(id);
        if(found == KEXToolsModule::Data::blockData.end()) {
            KEXToolsModule::Data::blockData.emplace(id, new KEXToolsModule::BlockDataInterface());
            found = KEXToolsModule::Data::blockData.find(id);
        }
        auto iface = found->second;
        jclass dataClass = env->FindClass("vsdum/kex/modules/tools/DataSets$BlockData");
        jstring jMaterialName = env->NewStringUTF(iface->materialName.c_str());
        jobject result = env->NewObject(dataClass, env->GetMethodID(dataClass, "<init>", "(Ljava/lang/String;IZ)V"), env->GetStringUTFLength(jMaterialName) != 0 ? jMaterialName : NULL, iface->destroyLevel, iface->isNative);
        env->DeleteLocalRef(dataClass);
        env->DeleteLocalRef(jMaterialName);
        return result;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeSetBlockData
    (JNIEnv* env, jclass, jint id, jstring materialName, jint destroyLevel, jboolean isNative) {
        const char* cMaterialName = env->GetStringUTFChars(materialName, 0);
        auto found = KEXToolsModule::Data::blockData.find(id);
        if(found == KEXToolsModule::Data::blockData.end()) {
            KEXToolsModule::Data::blockData.emplace(id, new KEXToolsModule::BlockDataInterface());
            found = KEXToolsModule::Data::blockData.find(id);
        }
        auto iface = found->second;
        iface->materialName = cMaterialName;
        env->ReleaseStringUTFChars(materialName, cMaterialName);
        iface->destroyLevel = destroyLevel;
        iface->isNative = isNative;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_getToolLevel
    (JNIEnv*, jclass, jint id) {
        int dynamicId = IdConversion::staticToDynamic(id, IdConversion::ITEM);
        Item* item = ItemRegistry::getItemById(dynamicId);
        if(item == nullptr) return 0;
        auto tier = KEXToolsModule::ToolAPI::getItemTier((DiggerItem*) item);
        if(tier == nullptr) return 0;
        return tier->getLevel() + 1;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_getToolLevelViaBlock
    (JNIEnv*, jclass, jint itemID, jint blockID) {
        auto find = KEXToolsModule::Data::blockData.find(blockID);
        if(find == KEXToolsModule::Data::blockData.end()) return 0;
        auto iface = find->second;
        int dynamicId = IdConversion::staticToDynamic(itemID, IdConversion::ITEM);
        Item* item = ItemRegistry::getItemById(dynamicId);
        if(item == nullptr) return 0;
        auto tier = KEXToolsModule::ToolAPI::getItemTier((DiggerItem*) item);
        if(tier == nullptr) return 0;
        int toolLevel = tier->getLevel() + 1;
        return toolLevel >= iface->destroyLevel ? toolLevel : 0;
    }
    JNIEXPORT jfloat JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeGetDestroyTimeViaTool
    (JNIEnv* env, jclass, jint id, jint data, jint itemID, jint itemCount, jint itemData, jlong itemExtra, jint x, jint y, jint z, jint side) {
        BlockLegacy* block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(id, IdConversion::BLOCK));
        if(block != nullptr) {
            float baseDestroyTime = block->getDestroySpeed();
            Item* item = ItemRegistry::getItemById(IdConversion::staticToDynamic(itemID, IdConversion::ITEM));
            if(item != nullptr) {
                VTABLE_FIND_OFFSET(Item_getDestroySpeed, _ZTV4Item, _ZNK4Item15getDestroySpeedERK13ItemStackBaseRK5Block);
                ItemStack stack(*item, itemCount, itemData);
                if(itemExtra != 0L) ((ItemInstanceExtra*) itemExtra)->apply(&stack);
                float speed = VTABLE_CALL<float>(Item_getDestroySpeed, item, &stack, BlockRegistry::getBlockStateForIdData(id, data));
                float materialDivider = 1.0f;
                auto itemTier = KEXToolsModule::ToolAPI::getItemTier((DiggerItem*) item);
                if(itemTier != nullptr) materialDivider = itemTier->getSpeed();
                float bonus = item->destroySpeedBonus(stack);
                return KEXJavaBridge::CustomToolEvents::calcDestroyTime(id, data, x, y, z, (char) side, baseDestroyTime, materialDivider, bonus, baseDestroyTime / speed);
            }
            return baseDestroyTime;
        }
        return 0.0f;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_enableDynamicDamageFor
    (JNIEnv*, jclass, jint id) {
        auto factory = LegacyItemRegistry::findFactoryById(id);
        if(factory != nullptr) {
            if(factory->getType() == ToolFactory::_factoryTypeId) {
                ToolFactory* toolFactory = (ToolFactory*) factory;
                auto tt = toolFactory->getToolType();
                if(tt == ToolFactory::CUSTOM_DIGGER || tt == ToolFactory::CUSTOM_WEAPON) {
                    CustomToolFactory* customToolFactory = (CustomToolFactory*) toolFactory;
                    customToolFactory->dynamicDamageEnabled =  true;
                }
            }
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_tools_ToolsNativeAPI_nativeDamageToolInHand
    (JNIEnv*, jclass, jlong player, jint damage) {
        Actor* actor = Actor::wrap(player);
        if(actor != nullptr) {
            VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
            ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
            if(stack != nullptr) {
                stack->hurtAndBreak(damage, actor);
            }
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_useCustomShearsOn
    (JNIEnv*, jclass, jint x, jint y, jint z, jbyte side, jfloat relX, jfloat relY, jfloat relZ, jlong actorUID) {
        Actor* actor = Actor::wrap(actorUID);
        if(actor != nullptr) {
            VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
            ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
            if(stack != nullptr) {
                Item* item = stack->getItem();
                if(item != nullptr) {
                    VTABLE_FIND_OFFSET(_checkUseOnPermissions, _ZTV4Item, _ZNK4Item22_checkUseOnPermissionsER5ActorR13ItemStackBaseRKhRK8BlockPos);
                    STATIC_SYMBOL(_useOn, "_ZNK10ShearsItem6_useOnER9ItemStackR5Actor8BlockPoshfff", (Item*, ItemStack*, Actor*, BlockPos*, unsigned char, float, float, float), void);
                    BlockPos pos(x, y, z);
                    if(VTABLE_CALL<bool>(_checkUseOnPermissions, item, actor, stack, &side, &pos)) {
                        _useOn(item, stack, actor, &pos, side, relX, relY, relZ);
                    }
                }
            }
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_useCustomFlintAndSteelOn
    (JNIEnv*, jclass, jint x, jint y, jint z, jbyte side, jfloat relX, jfloat relY, jfloat relZ, jlong actorUID) {
        Actor* actor = Actor::wrap(actorUID);
        if(actor != nullptr) {
            VTABLE_FIND_OFFSET(Actor_getCarriedItem, _ZTV5Actor, _ZNK5Actor14getCarriedItemEv);
            ItemStack* stack = VTABLE_CALL<ItemStack*>(Actor_getCarriedItem, actor);
            if(stack != nullptr) {
                Item* item = stack->getItem();
                if(item != nullptr) {
                    VTABLE_FIND_OFFSET(_checkUseOnPermissions, _ZTV4Item, _ZNK4Item22_checkUseOnPermissionsER5ActorR13ItemStackBaseRKhRK8BlockPos);
                    STATIC_SYMBOL(_useOn, "_ZNK17FlintAndSteelItem6_useOnER9ItemStackR5Actor8BlockPoshfff", (Item*, ItemStack*, Actor*, BlockPos*, unsigned char, float, float, float), void);
                    BlockPos pos(x, y, z);
                    if(VTABLE_CALL<bool>(_checkUseOnPermissions, item, actor, stack, &side, &pos)) {
                        _useOn(item, stack, actor, &pos, side, relX, relY, relZ);
                    }
                }
            }
        }
    }
    #define TOOL_TYPE_CHECKER(NAME) JNIEXPORT jboolean JNICALL Java_vsdum_kex_modules_ToolsModule_##NAME \
        (JNIEnv*, jclass, jint id) { \
            return KEXToolsModule::SimpleTests::NAME(id); \
        }
    TOOL_TYPE_CHECKER(isTool);
    TOOL_TYPE_CHECKER(isSword);
    TOOL_TYPE_CHECKER(isAxe);
    TOOL_TYPE_CHECKER(isPickaxe);
    TOOL_TYPE_CHECKER(isShovel);
    TOOL_TYPE_CHECKER(isHoe);
    TOOL_TYPE_CHECKER(isCustomTool);
    TOOL_TYPE_CHECKER(isShears);
    TOOL_TYPE_CHECKER(isFlintAndSteel);
    #undef TOOL_TYPE_CHECKER
}