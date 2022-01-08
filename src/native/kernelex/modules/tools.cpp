#include <cstring>
#include <string>
#include <jni.h>
#include <hook.h>
#include <symbol.h>
#include <innercore_callbacks.h>
#include <innercore/block_registry.h>
#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <innercore/legacy_item_registry.h>
#include <innercore/vtable.h>
#include <Actor.hpp>
#include <ActorUniqueID.hpp>
#include <Block.hpp>
#include <BlockLegacy.hpp>
#include <GameMode.hpp>
#include <Item.hpp>
#include <ItemStackBase.hpp>
#include <items/HatchetItem.hpp>
#include <items/HoeItem.hpp>
#include <items/PickaxeItem.hpp>
#include <items/ShovelItem.hpp>
#include <items/WeaponItem.hpp>
#include <Level.hpp>
#include <Mob.hpp>
#include <Player.hpp>
#include <SurvivalMode.hpp>
#include <commontypes.hpp>
#include <static_symbol.hpp>
#include "tools.hpp"


LastDestroyedBlock KEXToolsModule::lastDestroyed;
std::unordered_map<std::string, std::vector<int>> KEXToolsModule::materializedBlocks;
std::unordered_map<int, BlockDataInterface> KEXToolsModule::blockData;
std::unordered_map<int, int> KEXToolsModule::toolsToBrokenIds;

void KEXToolsModule::putNeededBlocksByMaterialName(std::string const& materialName, DiggerItem* item) {
    auto found = materializedBlocks.find(materialName);
    if(found != materializedBlocks.end()) {
        std::vector<int> blocks = found->second;
        for(int blockId : blocks) {
            int dynamicId = IdConversion::staticToDynamic(blockId, IdConversion::BLOCK);
            BlockLegacy* block = BlockRegistry::getBlockById(dynamicId);
            if(block != nullptr) {
                item->blocks.push_back(block);
            }
        }
    }
}

char* KEXToolsModule::getBlockMaterialName(int id) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        return found->second.materialName;
    } else {
        blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, BlockDataInterface()));
        return nullptr;
    }
}

int KEXToolsModule::getBlockDestroyLevel(int id) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        return found->second.destroyLevel;
    } else {
        blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, BlockDataInterface()));
        return 0;
    }
}

bool KEXToolsModule::getBlockIsNative(int id) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        return found->second.isNative;
    } else {
        blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, BlockDataInterface()));
        return false;
    }
}

void KEXToolsModule::setBlockMaterialName(int id, char* materialName) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        found->second.materialName = materialName;
    } else {
        BlockDataInterface iface;
        iface.materialName = materialName;
        blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, iface));
    }
}

void KEXToolsModule::setBlockDestroyLevel(int id, int destroyLevel) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        found->second.destroyLevel = destroyLevel;
    } else {
        BlockDataInterface iface;
        iface.destroyLevel = destroyLevel;
        blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, iface));
    }
}

void KEXToolsModule::setBlockIsNative(int id, bool isNative) {
    auto found = blockData.find(id);
    if(found != blockData.end()) {
        found->second.isNative = isNative;
    } else {
        BlockDataInterface iface;
        iface.isNative = isNative;
        blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, iface));
    }
}

bool KEXToolsModule::patchedCanDestroySpecial(DiggerItem* _this, Block const& block) {
    int blockLevel = KEXToolsModule::getBlockDestroyLevel(IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK));
    return _this->hasBlock(block) && _this->tier->getLevel() >= blockLevel;
}

void KEXToolsModule::patchDiggersVtables() {
    void** vtable_digger = (void**) SYMBOL("mcpe", "_ZTV10DiggerItem") + 2;
    void** vtable_pickaxe = (void**) SYMBOL("mcpe", "_ZTV11PickaxeItem") + 2;
    vtable_digger[getVtableOffset("_ZTV10DiggerItem", "_ZNK10DiggerItem17canDestroySpecialERK5Block")] = ADDRESS(patchedCanDestroySpecial);
    vtable_pickaxe[getVtableOffset("_ZTV11PickaxeItem", "_ZNK11PickaxeItem17canDestroySpecialERK5Block")] = ADDRESS(patchedCanDestroySpecial);
}

// 0 - nothing, 1 - prevent item from breaking, 2 - replace the item with brokenId
unsigned char KEXToolsModule::modifiedItemStackHurtAndBreak(ItemStackBase* stack, int damageValue) {
    int id = IdConversion::dynamicToStatic(stack->getId(), stack->isBlock() ? IdConversion::BLOCK : IdConversion::ITEM);
    auto found = KEXToolsModule::toolsToBrokenIds.find(id);
    int brokenId;
    if(found != KEXToolsModule::toolsToBrokenIds.end()) brokenId = found->second;
    else brokenId = 0;
    JNIEnv* env;
    bool replace = true;
    ATTACH_JAVA(env, JNI_VERSION_1_4) {
        jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
        jmethodID onBrokeMethod = env->GetStaticMethodID(moduleClass, "onBroke", "(J)Z");
        replace = !( env->CallStaticBooleanMethod(moduleClass, onBrokeMethod, ((jlong) stack)) );
    }
    if(!replace) return 1;
    else {
        if(brokenId == 0) return 0;
        else return 2;
    } 
}

void KEXToolsModule::initialize() {
    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");
    patchDiggersVtables();
    HookManager::addCallback(SYMBOL("mcpe", "_ZN10DiggerItem9setBlocksERKNSt6__ndk16vectorIPK5BlockNS0_9allocatorIS4_EEEE"), LAMBDA((DiggerItem* item), {
        HatchetItem* axe = dynamic_cast<HatchetItem*>(item);
        if(axe != nullptr) {
            putNeededBlocksByMaterialName(std::string("wood"), (DiggerItem*) item);
        } else {
            PickaxeItem* pickaxe = dynamic_cast<PickaxeItem*>(item);
            if(pickaxe != nullptr) {
                putNeededBlocksByMaterialName(std::string("stone"), (DiggerItem*) item);
            } else {
                ShovelItem* shovel = dynamic_cast<ShovelItem*>(item);
                if(shovel != nullptr) {
                    putNeededBlocksByMaterialName(std::string("dirt"), (DiggerItem*) item);
                }
            }
        }
    }, ), HookManager::RETURN | HookManager::LISTENER);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN13ItemStackBase12hurtAndBreakEiP5Actor"), LAMBDA((HookManager::CallbackController* controller, ItemStackBase* stack, int damageValue, Actor* actor), {
        unsigned char result = modifiedItemStackHurtAndBreak(stack, damageValue);
        if(result == 1) {
            controller->replace();
            return false;
        } else if(result == 2) {
            auto found = toolsToBrokenIds.find(IdConversion::dynamicToStatic(stack->getId(), IdConversion::ITEM));
            controller->replace();
            *stack = ItemStackBase(*ItemRegistry::getItemById(IdConversion::staticToDynamic(found->second, IdConversion::ITEM)), 1, 0);
            return true;
        }
    }, ), HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT);
    HookManager::addCallback(SYMBOL("mcpe", "_ZN12SurvivalMode17startDestroyBlockERK8BlockPoshRb"), LAMBDA((SurvivalMode* mode, BlockPos const& pos, unsigned char side, bool& someBoolRef), {
        if(mode->player->getLevel()->isClientSide()) {
            lastDestroyed.x = pos.x;
            lastDestroyed.y = pos.y;
            lastDestroyed.z = pos.z;
            lastDestroyed.side = side;
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
    // the hook of SurvivalMode::startDestroyBlock is the main one,
    // and the hook of GameMode::destroyBlock is made to look how they will behave,
    // when the player will be in creative mode, because I'm not sure that
    // startDestroyBlock is called in creative mode
    HookManager::addCallback(SYMBOL("mcpe", "_ZN8GameMode12destroyBlockERK8BlockPosh"), LAMBDA((GameMode* mode, BlockPos const& pos, unsigned char side), {
        if(mode->player->getLevel()->isClientSide()) {
            lastDestroyed.x = pos.x;
            lastDestroyed.y = pos.y;
            lastDestroyed.z = pos.z;
            lastDestroyed.side = side;
        }
    }, ), HookManager::CALL | HookManager::LISTENER);
}


void ToolFactory::setTier(Item::Tier* itemTier) { tier = itemTier; }
void SwordFactory::registerItem() { if(id != 0) ItemRegistry::registerItemFixed<WeaponItem>(new SwordProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier); }
SwordFactory* SwordProvider::getFactory() { return factory; }
void AxeFactory::registerItem() { if(id != 0) ItemRegistry::registerItemFixed<HatchetItem>(new AxeProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier); }
AxeFactory* AxeProvider::getFactory() { return factory; }
void PickaxeFactory::registerItem() { if(id != 0) ItemRegistry::registerItemFixed<PickaxeItem>(new PickaxeProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier); }
PickaxeFactory* PickaxeProvider::getFactory() { return factory; }
void ShovelFactory::registerItem() { if(id != 0) ItemRegistry::registerItemFixed<ShovelItem>(new ShovelProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier); }
ShovelFactory* ShovelProvider::getFactory() { return factory; }
void HoeFactory::registerItem() { if(id != 0) ItemRegistry::registerItemFixed<HoeItem>(new HoeProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, *tier); }
HoeFactory* HoeProvider::getFactory() { return factory; }


CustomWeaponItem::CustomWeaponItem(std::__ndk1::string const& nameId, int id, int baseAttackDamage, Item::Tier const& tier)
: WeaponItem(nameId, id, tier) {
    attackDamage = baseAttackDamage + tier.getAttackDamageBonus();
}
float CustomWeaponItem::getDestroySpeed(ItemStackBase const& stack, Block const& block) const {
    STATIC_SYMBOL(WeaponItem_getDestroySpeed, "_ZNK10WeaponItem15getDestroySpeedERK13ItemStackBaseRK5Block", (WeaponItem*, ItemStackBase const&, Block const&));
    void* output = WeaponItem_getDestroySpeed((WeaponItem*) this, stack, block);
    float super = *(float*)&output;
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_4) {
        jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
        jmethodID calcMethod = env->GetStaticMethodID(moduleClass, "calcDestroyTime", "(JIIIIIBFFFF)F");
        super = env->CallStaticFloatMethod(moduleClass, calcMethod, ((jlong) &stack), IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK), block.data, KEXToolsModule::lastDestroyed.x, KEXToolsModule::lastDestroyed.y, KEXToolsModule::lastDestroyed.z, (jbyte) KEXToolsModule::lastDestroyed.side, block.legacy->destroyTime, 1.0f, 1.0f, block.legacy->destroyTime) / block.legacy->destroyTime;
    }
    return super;
}
bool CustomWeaponItem::hurtActor(ItemStack& stack, Actor& actor, Mob& mob) const {
    bool result = true;
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_4) {
        jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
        jmethodID modifyEnchantMethod = env->GetStaticMethodID(moduleClass, "modifyEnchant", "(JIIIIII)V");
        env->CallStaticVoidMethod(moduleClass, modifyEnchantMethod, ((jlong) &stack), 0, 0, 0, 0, 0, 0);
        jmethodID onAttackMethod = env->GetStaticMethodID(moduleClass, "onAttack", "(JJJ)Z");
        bool output = env->CallStaticBooleanMethod(moduleClass, onAttackMethod, ((jlong) &stack), actor.getUniqueID()->id, mob.getUniqueID()->id);
        if(!output) {
            STATIC_SYMBOL(WeaponItem_hurtActor, "_ZNK10WeaponItem9hurtActorER9ItemStackR5ActorR3Mob", (WeaponItem*, ItemStack&, Actor&, Mob&));
            result = WeaponItem_hurtActor((WeaponItem*) this, stack, actor, mob);
        } else {
            result = false;
        }
    }
    return result;
}
bool CustomWeaponItem::mineBlock(ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) const {
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_4) {
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
        jmethodID modifyEnchantMethod = env->GetStaticMethodID(moduleClass, "modifyEnchant", "(JIIIIII)V");
        env->CallStaticVoidMethod(moduleClass, modifyEnchantMethod, ((jlong) &stack), x, y, z, KEXToolsModule::lastDestroyed.side, staticId, block.data);
        jmethodID onMineBlockMethod = env->GetStaticMethodID(moduleClass, "onMineBlock", "(JIIIIII)V");
        env->CallStaticVoidMethod(moduleClass, onMineBlockMethod, ((jlong) &stack), x, y, z, KEXToolsModule::lastDestroyed.side, staticId, block.data);
        jmethodID onDestroyMethod = env->GetStaticMethodID(moduleClass, "onDestroy", "(JIIIIIIJ)Z");
        bool output = env->CallStaticBooleanMethod(moduleClass, onDestroyMethod, ((jlong) &stack), x, y, z, KEXToolsModule::lastDestroyed.side, staticId, block.data, actor->getUniqueID()->id);
        if(!output) {
            STATIC_SYMBOL(Item_mineBlock, "_ZNK4Item9mineBlockER9ItemStackRK5BlockiiiP5Actor", (Item*, ItemStack&, Block const&, int, int, int, Actor*));
            Item_mineBlock((Item*) this, stack, block, x, y, z, actor);
        }
    }
    return true;
}


CustomDiggerItem::CustomDiggerItem(std::__ndk1::string const& nameId, int id, int baseAttackDamage, Item::Tier const& tier, std::vector<std::string> const& blockMaterials)
: DiggerItem(nameId, id, baseAttackDamage, tier, std::__ndk1::vector<Block const*>()) {
    for(std::string materialName : blockMaterials) {
        KEXToolsModule::putNeededBlocksByMaterialName(materialName, (DiggerItem*) this);
    }
}
float CustomDiggerItem::getDestroySpeed(ItemStackBase const& stack, Block const& block) const {
    STATIC_SYMBOL(DiggerItem_getDestroySpeed, "_ZNK10DiggerItem15getDestroySpeedERK13ItemStackBaseRK5Block", (DiggerItem*, ItemStackBase const&, Block const&));
    void* output = DiggerItem_getDestroySpeed((DiggerItem*) this, stack, block);
    float super = *(float*)&output;
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_4) {
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
        jmethodID modifyEnchantMethod = env->GetStaticMethodID(moduleClass, "modifyEnchant", "(JIIIBII)V");
        env->CallStaticVoidMethod(moduleClass, modifyEnchantMethod, ((jlong) &stack), KEXToolsModule::lastDestroyed.x, KEXToolsModule::lastDestroyed.y, KEXToolsModule::lastDestroyed.z, (jbyte) KEXToolsModule::lastDestroyed.side, staticId, block.data);
        jmethodID calcMethod = env->GetStaticMethodID(moduleClass, "calcDestroyTime", "(JIIIIIBFFFF)F");
        float materialDivider = tier->getSpeed();
        float efficiencyModifier = destroySpeedBonus(stack);
        super = env->CallStaticFloatMethod(moduleClass, calcMethod, ((jlong) &stack), staticId, block.data, KEXToolsModule::lastDestroyed.x, KEXToolsModule::lastDestroyed.y, KEXToolsModule::lastDestroyed.z, (jbyte) KEXToolsModule::lastDestroyed.side, block.legacy->destroyTime, materialDivider, efficiencyModifier, block.legacy->destroyTime / materialDivider / efficiencyModifier) / block.legacy->destroyTime;
    }
    return super;
}
bool CustomDiggerItem::hurtActor(ItemStack& stack, Actor& actor, Mob& mob) const {
    bool result = true;
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_4) {
        jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
        jmethodID modifyEnchantMethod = env->GetStaticMethodID(moduleClass, "modifyEnchant", "(JIIIIII)V");
        env->CallStaticVoidMethod(moduleClass, modifyEnchantMethod, ((jlong) &stack), 0, 0, 0, 0, 0, 0);
        jmethodID onAttackMethod = env->GetStaticMethodID(moduleClass, "onAttack", "(JJJ)Z");
        bool output = env->CallStaticBooleanMethod(moduleClass, onAttackMethod, ((jlong) &stack), actor.getUniqueID()->id, mob.getUniqueID()->id);
        if(!output) {
            STATIC_SYMBOL(Item_hurtActor, "_ZNK4Item9hurtActorER9ItemStackR5ActorR3Mob", (Item*, ItemStack&, Actor&, Mob&));
            result = Item_hurtActor((Item*) this, stack, actor, mob);
        } else {
            result = false;
        }
    }
    return result;
}
bool CustomDiggerItem::mineBlock(ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) const {
    JNIEnv* env;
    ATTACH_JAVA(env, JNI_VERSION_1_4) {
        int staticId = IdConversion::dynamicToStatic(block.legacy->id, IdConversion::BLOCK);
        jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
        jmethodID modifyEnchantMethod = env->GetStaticMethodID(moduleClass, "modifyEnchant", "(JIIIBII)V");
        env->CallStaticVoidMethod(moduleClass, modifyEnchantMethod, ((jlong) &stack), x, y, z, KEXToolsModule::lastDestroyed.side, staticId, block.data);
        jmethodID onMineBlockMethod = env->GetStaticMethodID(moduleClass, "onMineBlock", "(JIIIBII)V");
        env->CallStaticVoidMethod(moduleClass, onMineBlockMethod, ((jlong) &stack), x, y, z, KEXToolsModule::lastDestroyed.side, staticId, block.data);
        jmethodID onDestroyMethod = env->GetStaticMethodID(moduleClass, "onDestroy", "(JIIIBIIJ)Z");
        bool output = env->CallStaticBooleanMethod(moduleClass, onDestroyMethod, ((jlong) &stack), x, y, z, KEXToolsModule::lastDestroyed.side, staticId, block.data, actor->getUniqueID()->id);
        if(!output) {
            STATIC_SYMBOL(DiggerItem_mineBlock, "_ZNK10DiggerItem9mineBlockER9ItemStackRK5BlockiiiP5Actor", (Item*, ItemStack&, Block const&, int, int, int, Actor*));
            DiggerItem_mineBlock((Item*) this, stack, block, x, y, z, actor);
        }
    }
    return true;
}


void CustomToolFactory::registerItem() {
    if(id != 0) {
        if(isWeapon) {
            ItemRegistry::registerItemFixed<CustomWeaponItem>(new CustomToolProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, baseAttackDamage, *tier);
        } else {
            ItemRegistry::registerItemFixed<CustomDiggerItem>(new CustomToolProvider(this), IdConversion::staticToDynamic(id, IdConversion::ITEM), nameId, baseAttackDamage, *tier, blockMaterials);
        }
    }
}
void CustomToolFactory::setIsWeapon(bool iw) { isWeapon = iw; }
void CustomToolFactory::setBlockMaterials(std::vector<std::string> const& materials) {
    if(!isWeapon) for(std::string materialName : materials) {
        blockMaterials.push_back(materialName);
    }
}
void CustomToolFactory::setBaseAttackDamage(int damage) { baseAttackDamage = damage; }

CustomToolFactory* CustomToolProvider::getFactory() { return factory; }


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
        factory->setTier((Item::Tier*) tierPtr);
        factory->initParameters(id, std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
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
        factory->setTier((Item::Tier*) tierPtr);
        factory->initParameters(id, std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
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
        factory->setTier((Item::Tier*) tierPtr);
        factory->initParameters(id, std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
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
        factory->setTier((Item::Tier*) tierPtr);
        factory->initParameters(id, std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
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
        factory->setTier((Item::Tier*) tierPtr);
        factory->initParameters(id, std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
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
            return block->destroyTime;
        }
        return 0.0f;
    }
    JNIEXPORT jstring JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockMaterialName
    (JNIEnv* env, jclass, int id) {
        char* materialName = KEXToolsModule::getBlockMaterialName(id);
        if(materialName == nullptr) return NULL;
        return env->NewStringUTF(materialName);
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockDestroyLevel
    (JNIEnv*, jclass, int id) {
        return KEXToolsModule::getBlockDestroyLevel(id);
    }
    JNIEXPORT jboolean JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockIsNative
    (JNIEnv*, jclass, int id) {
        return KEXToolsModule::getBlockIsNative(id);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockMaterialName
    (JNIEnv* env, jclass, int id, jstring materialName) {
        const char* cMaterialName = env->GetStringUTFChars(materialName, 0);
        char* cMaterialNameNew;
        strcpy((char*) cMaterialName, (const char*) cMaterialNameNew);
        KEXToolsModule::setBlockMaterialName(id, cMaterialNameNew);
        env->ReleaseStringUTFChars(materialName, cMaterialName);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockDestroyLevel
    (JNIEnv*, jclass, int id, jint destroyLevel) {
        KEXToolsModule::setBlockDestroyLevel(id, destroyLevel);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockIsNative
    (JNIEnv*, jclass, int id, jboolean isNative) {
        KEXToolsModule::setBlockIsNative(id, isNative);
    }
    JNIEXPORT jobject JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetBlockData
    (JNIEnv* env, jclass, int id) {
        auto found = KEXToolsModule::blockData.find(id);
        if(found == KEXToolsModule::blockData.end()) {
            KEXToolsModule::blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, BlockDataInterface()));
            found = KEXToolsModule::blockData.find(id);
        }
        BlockDataInterface iface = found->second;
        jclass dataClass = env->FindClass("vsdum/kex/modules/ToolsModule$BlockData");
        return env->NewObject(dataClass, env->GetMethodID(dataClass, "<init>", "(Ljava/lang/String;IZ)V"), iface.materialName != nullptr ? env->NewStringUTF(iface.materialName) : NULL, iface.destroyLevel, iface.isNative);
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeSetBlockData
    (JNIEnv* env, jclass, int id, jstring materialName, jint destroyLevel, jboolean isNative) {
        const char* cMaterialName = env->GetStringUTFChars(materialName, 0);
        auto found = KEXToolsModule::blockData.find(id);
        if(found == KEXToolsModule::blockData.end()) {
            KEXToolsModule::blockData.insert(std::unordered_map<int, BlockDataInterface>::value_type(id, BlockDataInterface()));
            found = KEXToolsModule::blockData.find(id);
        }
        BlockDataInterface iface = found->second;
        strcpy((char*) cMaterialName, (const char*) iface.materialName);
        env->ReleaseStringUTFChars(materialName, cMaterialName);
        iface.destroyLevel = destroyLevel;
        iface.isNative = isNative;
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_getToolLevel
    (JNIEnv*, jclass, jint id) {
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(id);
        if(factory == nullptr) return 0;
        ToolFactory* toolFactory = dynamic_cast<ToolFactory*>(factory);
        if(toolFactory == nullptr) return 0;
        return toolFactory->tier->getLevel();
    }
    JNIEXPORT jint JNICALL Java_vsdum_kex_modules_ToolsModule_getToolLevelViaBlock
    (JNIEnv*, jclass, jint itemID, jint blockID) {
        auto find = KEXToolsModule::blockData.find(blockID);
        if(find == KEXToolsModule::blockData.end()) return 0;
        BlockDataInterface iface = find->second;
        LegacyItemRegistry::LegacyItemFactoryBase* factory = LegacyItemRegistry::findFactoryById(itemID);
        if(factory == nullptr) return 0;
        ToolFactory* toolFactory = dynamic_cast<ToolFactory*>(factory);
        if(toolFactory == nullptr) return 0;
        int toolLevel = toolFactory->tier->getLevel();
        return toolLevel >= iface.destroyLevel ? toolLevel : 0;
    }
    JNIEXPORT jfloat JNICALL Java_vsdum_kex_modules_ToolsModule_nativeGetDestroyTimeViaTool
    (JNIEnv* env, jclass, jint id, jint data, jlong stackptr, jint x, jint y, jint z, jint side) {
        ItemStackBase* stack = ((ItemStackBase*) stackptr);
        BlockLegacy* block = BlockRegistry::getBlockById(IdConversion::staticToDynamic(id, IdConversion::BLOCK));
        if(block != nullptr) {
            float baseDestroyTime = block->destroyTime;
            Item* item = stack->getItem();
            if(item != nullptr) {
                VTABLE_FIND_OFFSET(Item_getDestroySpeed, _ZTV4Item, _ZNK4Item15getDestroySpeedERK13ItemStackBaseRK5Block);
                float speed = VTABLE_CALL<float>(Item_getDestroySpeed, item, stack, *(BlockRegistry::getBlockStateForIdData(id, data)));
                float result = baseDestroyTime / speed;
                JNIEnv* env;
                ATTACH_JAVA(env, JNI_VERSION_1_4) {
                    jclass moduleClass = env->FindClass("vsdum/kex/modules/ToolsModule");
                    jmethodID calcMethod = env->GetStaticMethodID(moduleClass, "calcDestroyTime", "(JIIFFFF)F");
                    float materialDivider = 1.0f;
                    DiggerItem* digger = dynamic_cast<DiggerItem*>(item);
                    if(digger != nullptr) materialDivider = digger->tier->getSpeed();
                    float bonus = item->destroySpeedBonus(*stack);
                    result = env->CallStaticFloatMethod(moduleClass, calcMethod, stackptr, id, data, baseDestroyTime, materialDivider, bonus, baseDestroyTime / speed);
                }
            }
            return baseDestroyTime;
        }
        return 0.0f;
    }
    JNIEXPORT void JNICALL Java_vsdum_kex_modules_ToolsModule_nativeRegisterCustomTool
    (JNIEnv* env, jclass, jint id, jstring nameId, jstring name, jstring textureName, jint textureMeta, jlong tierPtr, jboolean isTech, jboolean isWeapon, jobjectArray blockMaterials, jint brokenId, jint baseAttackDamage) {
        const char* cNameId = env->GetStringUTFChars(nameId, 0);
        const char* cName = env->GetStringUTFChars(name, 0);
        const char* cTextureName = env->GetStringUTFChars(textureName, 0);
        CustomToolFactory* factory = new CustomToolFactory();
        factory->setTier((Item::Tier*) tierPtr);
        factory->setIsWeapon(isWeapon);
        factory->setBaseAttackDamage(baseAttackDamage);
        factory->initParameters(id, std::string(cNameId), std::string(cName), std::string(cTextureName), textureMeta);
        factory->props.stack = 1;
        if(brokenId != 0) KEXToolsModule::toolsToBrokenIds.insert(std::unordered_map<int, int>::value_type(id, brokenId));
        if(blockMaterials != NULL) {
            std::vector<std::string> materials;
            jsize l = env->GetArrayLength(blockMaterials);
            if(l > 0) {
                for(int i = 0; i < l; ++i) {
                    jobject el = env->GetObjectArrayElement(blockMaterials, i);
                    if(el != NULL) {
                        jstring sEl = (jstring) el;
                        const char* cEl = env->GetStringUTFChars(sEl, 0);
                        materials.push_back(std::string(cEl));
                        env->ReleaseStringUTFChars(sEl, cEl);
                    }
                }
                factory->setBlockMaterials(materials);
            }
        }
        LegacyItemRegistry::registerItemFactory(factory);
        if(!isTech) LegacyItemRegistry::addItemToCreative(id, 1, 0, nullptr);
        env->ReleaseStringUTFChars(nameId, cNameId);
        env->ReleaseStringUTFChars(name, cName);
        env->ReleaseStringUTFChars(textureName, cTextureName);
    }
}