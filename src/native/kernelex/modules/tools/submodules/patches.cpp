#include <static_symbol.h>

#include <innercore/id_conversion_map.h>

#include <EnchantUtils.hpp>
#include <I18n.hpp>

#include "../../../utils/java_utils.hpp"
#include "../tooltypes/custom.hpp"
#include "../tooltypes/shears.hpp"
#include "../module.hpp"


void KEXToolsModule::CustomToolPatches::appendFormattedHovertext(Item* _this, const ItemStackBase& stack, Level& level, stl::string& text, bool someBool) {
    STATIC_SYMBOL(Item_appendFormattedHovertext, "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb", (Item*, const ItemStackBase&, Level&, stl::string&, bool), void);
    Item_appendFormattedHovertext(_this, stack, level, text, someBool);
    text.append("\n\n§9+");
    int staticId = IdConversion::dynamicToStatic(_this->id, IdConversion::ITEM);
    CustomToolFactory* factory = (CustomToolFactory*) LegacyItemRegistry::findFactoryById(staticId);
    if(factory != nullptr) {
        int damage = factory->baseAttackDamage;
        ItemInstanceExtra* extra = new ItemInstanceExtra((ItemStack*) &stack);
        damage += KEXJavaBridge::CustomToolEvents::getAttackDamageBonus(staticId, 1, stack.getDamageValue(), (jlong) extra, factory->tier->getAttackDamageBonus(), 0, 0);
        delete extra;
        damage += (int)((float) EnchantUtils::getEnchantLevel((Enchant::Type) 9, stack) * 1.25);
        text.append(stl::to_string(damage));
        text.append(" ");
        text.append(I18n::get("attribute.name.generic.attackDamage"));
        text.append("§r");
    }
}


float KEXToolsModule::CustomToolPatches::_shearsTieredGetDestroySpeed(ShearsItem* shears, const ItemStackBase& stack, const Block& block) {
    STATIC_SYMBOL(ShearsItem_getDestroySpeed, "_ZNK10ShearsItem15getDestroySpeedERK13ItemStackBaseRK5Block", (ShearsItem*, const ItemStackBase&, const Block&), float);
    float result = ShearsItem_getDestroySpeed(shears, stack, block);
    int staticId = IdConversion::dynamicToStatic(shears->id, IdConversion::ITEM);
    ShearsFactory* factory = (ShearsFactory*) LegacyItemRegistry::findFactoryById(staticId);
    if(factory != nullptr) {
        result /= VanillaItemTiers::IRON.getSpeed();
        result *= factory->tier->getSpeed();
    }
    return result;
}