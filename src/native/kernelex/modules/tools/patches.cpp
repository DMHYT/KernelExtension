#include <EnchantUtils.hpp>
#include <ItemStackBase.hpp>
#include <I18n.hpp>
#include <Level.hpp>
#include <Item.hpp>
#include <innercore/id_conversion_map.h>
#include <innercore/item_registry.h>
#include <static_symbol.hpp>
#include "../../utils/java_utils.hpp"
#include "classes.hpp"
#include "module.hpp"
#include "patches.hpp"


void CustomToolPatches::_appendFormattedHovertext(Item* _this, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool someBool) {
    STATIC_SYMBOL(Item_appendFormattedHovertext, "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb", (Item*, ItemStackBase const&, Level&, std::__ndk1::string&, bool));
    Item_appendFormattedHovertext(_this, stack, level, text, someBool);
    text.append("\n\n§9+");
    int staticId = IdConversion::dynamicToStatic(_this->id, IdConversion::ITEM);
    CustomToolFactory* factory = (CustomToolFactory*) LegacyItemRegistry::findFactoryById(staticId);
    if(factory != nullptr) {
        int damage = factory->baseAttackDamage;
        ItemInstanceExtra* extra = new ItemInstanceExtra((ItemStack*) &stack);
        damage += KEXJavaBridge::ToolsModule::getAttackDamageBonus(staticId, 1, stack.getDamageValue(), (jlong) extra, factory->tier->getAttackDamageBonus());
        delete extra;
        damage += (int)((float) EnchantUtils::getEnchantLevel((Enchant::Type) 9, stack) * 1.25);
        text.append(std::__ndk1::to_string(damage));
        text.append(" ");
        text.append(I18n::get("attribute.name.generic.attackDamage"));
        text.append("§r");
    }
}


float CustomToolPatches::Digger::getDestroySpeed(DiggerItem* _this, ItemStackBase const& stack, Block const& block) {
    return KEXToolsModule::lastDestroyedClient->getOrCalculateSpeed(stack, block, _this);
}
bool CustomToolPatches::Digger::hurtActor(DiggerItem* _this, ItemStack& stack, Actor& actor, Mob& mob) {
    return true;
}
bool CustomToolPatches::Digger::mineBlock__instance(DiggerItem* _this, ItemInstance& stack, Block const& block, int x, int y, int z, Actor* actor) {
    return true;
}
bool CustomToolPatches::Digger::mineBlock__stack(DiggerItem* _this, ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) {
    return true;
}
void CustomToolPatches::Digger::appendFormattedHovertext(DiggerItem* _this, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool someBool) {
    _appendFormattedHovertext((Item*) _this, stack, level, text, someBool);
}


float CustomToolPatches::Weapon::getDestroySpeed(WeaponItem* _this, ItemStackBase const& stack, Block const& block) {
    return KEXToolsModule::lastDestroyedClient->getOrCalculateSpeed(stack, block, _this);
}
bool CustomToolPatches::Weapon::hurtActor(WeaponItem* _this, ItemStack& stack, Actor& actor, Mob& mob) {
    return true;
}
bool CustomToolPatches::Weapon::mineBlock__instance(WeaponItem* _this, ItemInstance& stack, Block const& block, int x, int y, int z, Actor* actor) {
    return true;
}
bool CustomToolPatches::Weapon::mineBlock__stack(WeaponItem* _this, ItemStack& stack, Block const& block, int x, int y, int z, Actor* actor) {
    return true;
}
void CustomToolPatches::Weapon::appendFormattedHovertext(WeaponItem* _this, ItemStackBase const& stack, Level& level, std::__ndk1::string& text, bool someBool) {
    _appendFormattedHovertext((Item*) _this, stack, level, text, someBool);
}