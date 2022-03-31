#include <string>
#include <set>
#include <jni.h>
#include <innercore/id_conversion_map.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/block_registry.h>
#include <innercore/vtable.h>
#include <Actor.hpp>
#include <BlockLegacy.hpp>
#include <Item.hpp>
#include <ItemStackBase.hpp>
#include <ItemStack.hpp>
#include "../../utils/java_utils.hpp"
#include "classes.hpp"
#include "module.hpp"


extern "C" {
    JNIEXPORT jlongArray JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGrabVanillaItemTiers
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
    JNIEXPORT jlong JNICALL Java_vsdum_kex_modules_ToolsModule_nativeNewItemTier
    (JNIEnv*, jclass, jint level, jint uses, jfloat speed, jint attackDamageBonus, jint enchantmentValue) {
        Item::Tier* tier = new Item::Tier(level, uses, speed, attackDamageBonus, enchantmentValue);
        return (jlong) tier;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetItemTierLevel
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getLevel();
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetItemTierUses
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getUses();
    }
    JNIEXPORT jfloat JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetItemTierSpeed
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getSpeed();
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetItemTierAttackDamageBonus
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getAttackDamageBonus();
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetItemTierEnchantmentValue
    (JNIEnv*, jclass, jlong ptr) {
        return ((Item::Tier*) ptr)->getEnchantmentValue();
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterSword
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        SwordFactory* factory = new SwordFactory();
        factory->initParameters(id, "item_" + std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        factory->tier = (Item::Tier*) tierPtr;
        LegacyItemRegistry::registerItemFactory(factory);
        if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterAxe
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        AxeFactory* factory = new AxeFactory();
        factory->initParameters(id, "item_" + std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        factory->tier = (Item::Tier*) tierPtr;
        LegacyItemRegistry::registerItemFactory(factory);
        if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterPickaxe
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        PickaxeFactory* factory = new PickaxeFactory();
        factory->initParameters(id, "item_" + std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        factory->tier = (Item::Tier*) tierPtr;
        LegacyItemRegistry::registerItemFactory(factory);
        if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterShovel
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        ShovelFactory* factory = new ShovelFactory();
        factory->initParameters(id, "item_" + std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        factory->tier = (Item::Tier*) tierPtr;
        LegacyItemRegistry::registerItemFactory(factory);
        if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterHoe
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        HoeFactory* factory = new HoeFactory();
        factory->initParameters(id, "item_" + std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        factory->tier = (Item::Tier*) tierPtr;
        LegacyItemRegistry::registerItemFactory(factory);
        if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
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
    JNIEXPORT jstring JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockMaterialName
    (JNIEnv* env, jclass, jint id) {
        const char* materialName = KEXToolsModule::getBlockMaterialName(id);
        if(materialName == nullptr) return NULL;
        return env->NewStringUTF(materialName);
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockDestroyLevel
    (JNIEnv*, jclass, jint id) {
        return KEXToolsModule::getBlockDestroyLevel(id);
    }
    JNIEXPORT jboolean JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockIsNative
    (JNIEnv*, jclass, jint id) {
        return KEXToolsModule::getBlockIsNative(id);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockMaterialName
    (JNIEnv* env, jclass, jint id, jstring materialName) {
        const char* cMaterialName = env->GetStringUTFChars(materialName, 0);
        KEXToolsModule::setBlockMaterialName(id, cMaterialName);
        env->ReleaseStringUTFChars(materialName, cMaterialName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockDestroyLevel
    (JNIEnv*, jclass, jint id, jint destroyLevel) {
        KEXToolsModule::setBlockDestroyLevel(id, destroyLevel);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockIsNative
    (JNIEnv*, jclass, jint id, jboolean isNative) {
        KEXToolsModule::setBlockIsNative(id, isNative);
    }
    JNIEXPORT jobject JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockData
    (JNIEnv* env, jclass, jint id) {
        auto found = KEXToolsModule::blockData.find(id);
        if(found == KEXToolsModule::blockData.end()) {
            KEXToolsModule::blockData.emplace(id, new BlockDataInterface());
            found = KEXToolsModule::blockData.find(id);
        }
        BlockDataInterface* iface = found->second;
        jclass dataClass = env->FindClass("vsdum/kex/modules/ToolsModule$BlockData");
        jstring jMaterialName = env->NewStringUTF(iface->materialName.c_str());
        jobject result = env->NewObject(dataClass, env->GetMethodID(dataClass, "<init>", "(Ljava/lang/String;IZ)V"), env->GetStringUTFLength(jMaterialName) != 0 ? jMaterialName : NULL, iface->destroyLevel, iface->isNative);
        env->DeleteLocalRef(dataClass);
        env->DeleteLocalRef(jMaterialName);
        return result;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockData
    (JNIEnv* env, jclass, jint id, jstring materialName, jint destroyLevel, jboolean isNative) {
        const char* cMaterialName = env->GetStringUTFChars(materialName, 0);
        auto found = KEXToolsModule::blockData.find(id);
        if(found == KEXToolsModule::blockData.end()) {
            KEXToolsModule::blockData.emplace(id, new BlockDataInterface());
            found = KEXToolsModule::blockData.find(id);
        }
        BlockDataInterface* iface = found->second;
        iface->materialName = std::string(cMaterialName);
        env->ReleaseStringUTFChars(materialName, cMaterialName);
        iface->destroyLevel = destroyLevel;
        iface->isNative = isNative;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_getToolLevel
    (JNIEnv*, jclass, jint id) {
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(id);
        if(factory == nullptr) return 0;
        if(factory->getType() == ToolFactory::_factoryTypeId) {
            ToolFactory* toolFactory = (ToolFactory*) factory;
            return toolFactory->tier->getLevel();
        }
        return 0;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_getToolLevelViaBlock
    (JNIEnv*, jclass, jint itemID, jint blockID) {
        auto find = KEXToolsModule::blockData.find(blockID);
        if(find == KEXToolsModule::blockData.end()) return 0;
        BlockDataInterface* iface = find->second;
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(itemID);
        if(factory == nullptr) return 0;
        if(factory->getType() == ToolFactory::_factoryTypeId) {
            ToolFactory* toolFactory = (ToolFactory*) factory;
            int toolLevel = toolFactory->tier->getLevel();
            return toolLevel >= iface->destroyLevel ? toolLevel : 0;
        }
        return 0;
    }
    JNIEXPORT jfloat JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetDestroyTimeViaTool
    (JNIEnv* env, jclass, jint id, jint data, jlong stackptr, jint x, jint y, jint z, jint side) {
        ItemStackBase* stack = ((ItemStackBase*) stackptr);
        BlockLegacy* block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(id, IdConversion::BLOCK));
        if(block != nullptr) {
            float baseDestroyTime = block->getDestroySpeed();
            Item* item = stack->getItem();
            if(item != nullptr) {
                VTABLE_FIND_OFFSET(Item_getDestroySpeed, _ZTV4Item, _ZNK4Item15getDestroySpeedERK13ItemStackBaseRK5Block);
                float speed = VTABLE_CALL<float>(Item_getDestroySpeed, item, stack, *(BlockRegistry::getBlockStateForIdData(id, data)));
                float result = baseDestroyTime / speed;
                float materialDivider = 1.0f;
                Item::Tier* itemTier = KEXToolsModule::getItemTier((DiggerItem*) item);
                if(itemTier != nullptr) materialDivider = itemTier->getSpeed();
                float bonus = item->destroySpeedBonus(*stack);
                result = KEXJavaBridge::ToolsModule::calcDestroyTime(id, data, x, y, z, (char) side, baseDestroyTime, materialDivider, bonus, baseDestroyTime / speed);
                return result;
            }
            return baseDestroyTime;
        }
        return 0.0f;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterCustomTool
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech, jboolean isWeapon, jobjectArray blockMaterials, jint brokenId, jint baseAttackDamage, jint enchantType) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        CustomToolFactory* factory = new CustomToolFactory();
        factory->isWeapon = isWeapon;
        factory->baseAttackDamage = baseAttackDamage;
        factory->initParameters(id, "item_" + std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        factory->enchantType = enchantType;
        factory->tier = (Item::Tier*) tierPtr;
        if(brokenId != 0) KEXToolsModule::toolsToBrokenIds.emplace(id, brokenId);
        if(blockMaterials != NULL && !isWeapon) {
            std::set<std::string> materials;
            jsize l = env->GetArrayLength(blockMaterials);
            if(l > 0) {
                for(int i = 0; i < l; ++i) {
                    jobject el = env->GetObjectArrayElement(blockMaterials, i);
                    if(el != NULL) {
                        jstring sEl = (jstring) el;
                        const char* cEl = env->GetStringUTFChars(sEl, 0);
                        if(materials.find(cEl) == materials.end()) {
                            materials.emplace(std::string(cEl));
                        }
                        env->ReleaseStringUTFChars(sEl, cEl);
                    }
                }
                factory->blockMaterials = materials;
            }
        }
        LegacyItemRegistry::registerItemFactory(factory);
        // if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
        KEXToolsModule::customTools.emplace(id);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_enableDynamicDamageFor
    (JNIEnv*, jclass, jint id) {
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(id);
        if(factory != nullptr) {
            if(factory->getType() == ToolFactory::_factoryTypeId) {
                ToolFactory* toolFactory = (ToolFactory*) factory;
                ToolFactory::ToolType tt = toolFactory->getToolType();
                if(tt == ToolFactory::CUSTOM_DIGGER || tt == ToolFactory::CUSTOM_WEAPON) {
                    CustomToolFactory* customToolFactory = (CustomToolFactory*) toolFactory;
                    customToolFactory->dynamicDamageEnabled =  true;
                }
            }
        }
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeDamageToolInHand
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
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterShears
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech, jint durabilityIfWithoutTier) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        ShearsFactory* factory = new ShearsFactory();
        factory->initParameters(id, "item_" + std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        if(tierPtr != 0) factory->tier = (Item::Tier*) tierPtr;
        else factory->props.durability = durabilityIfWithoutTier;
        LegacyItemRegistry::registerItemFactory(factory);
        if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
    }
}