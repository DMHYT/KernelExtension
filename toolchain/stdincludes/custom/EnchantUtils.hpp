#include <enums.hpp>

#ifndef KEX_ENCHANTUTILS_HPP
#define KEX_ENCHANTUTILS_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
class ActorDamageSource;
class BlockSource;
class Enchant {
    public:
    enum Type: unsigned char {};
};
class EnchantmentInstance;
#ifndef KEX_ITEM_HPP
    class Item;
#endif
#ifndef KEX_HASHEDSTRING_HPP
    class HashedString;
#endif
class ItemEnchants;
#ifndef KEX_ITEMSTACKBASE_HPP
    class ItemStackBase;
#endif
#ifndef KEX_ITEMINSTANCE_HPP
    class ItemInstance;
#endif
#ifndef KEX_ITEMSTACK_HPP
    class ItemStack;
#endif
#ifndef KEX_MOB_HPP
    class Mob;
#endif
class Random;
#ifndef KEX_VEC3_HPP
    class Vec3;
#endif

class EnchantUtils {
    public:
    static void* getEnchantCosts(const ItemStackBase&, int);
    static bool canEnchant(const ItemStackBase&, int);
    static int getEnchantLevel(Enchant::Type, const ItemStackBase&);
    static void* getLegalEnchants(const Item*);
    static void applyEnchant(ItemStackBase&, const ItemEnchants&, bool);
    static bool isCurse(Enchant::Type);
    static bool hasEnchant(Enchant::Type, const ItemStackBase&);
    static void randomlyEnchant(ItemStack&);
    static void applyEnchant(ItemStackBase&, Enchant::Type, int, bool);
    static void randomlyEnchant(ItemInstance&, int, int, bool);
    static int getBestEnchantLevel(Enchant::Type, const Mob&, EquipmentFilter);
    static void removeEnchants(ItemStack&);
    static void* getBookCasePositions(BlockSource&, const Vec3&);
    static void combineEnchantedItems(const ItemStack&, const ItemStack&, ItemStack&, bool);
    static void* generateRandomEnchantedBook(int, int);
    static int /*?*/ getLootableRandomEnchantIndex(Random&);
    static void* generateRandomEnchantedItem(const Item&, int, int);
    static void doPostDamageEffects(Actor&, Actor&);
    static int getTotalProtectionLevels(Enchant::Type, const Mob&);
    static int getBookcaseCount(BlockSource&, const Vec3&);
    static void* _convertBookCheck(ItemStackBase&);
    static float getDamageReduction(const ActorDamageSource&, const Mob&);
    static bool canEnchant(const ItemStackBase&, const EnchantmentInstance&, bool);
    static void* getRandomDamagedItemWithMending(const Mob&);
    static bool hasCurse(const ItemStackBase&);
    static void doPostHurtEffects(Mob&, Mob&);
    static void determineActivation(Enchant::Type);
    static bool isCompatibleWith(Enchant::Type, Enchant::Type);
    static int getEnchantmentId(const HashedString&);
    static void* selectEnchantments(const Item*, int, int, bool);
    static void* getRandomItemWith(Enchant::Type, const Mob&, EquipmentFilter);
    static int getMeleeDamageBonus(const Actor&, Actor&);
    static void randomlyEnchant(ItemStack&, int, int, bool);
    static void* getRandomName();
    static void determineCompatibility(Enchant::Type);
    static void* getEnchantNameAndLevel(Enchant::Type, int);
    static void applyEnchant(ItemStackBase&, const EnchantmentInstance&, bool);
    static void* getAvailableEnchantmentResults(const Item*, int, bool);
    static void* generateEnchantedBook(const ItemEnchants&);
    static void* getEquipmentSet(const Mob&, EquipmentFilter);
    static void* getEnchantingTablePositions(BlockSource&, const Vec3&);
    static void* generateRandomEnchantedBook();
    static void* generateEnchantedBook(const EnchantmentInstance&);
    static void randomlyEnchant(ItemInstance&);
};


#endif //KEX_ENCHANTUTILS_HPP