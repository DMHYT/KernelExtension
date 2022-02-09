#ifndef KEX_ENCHANTUTILS_HPP
#define KEX_ENCHANTUTILS_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
class ActorDamageSource;
class BlockSource;
class Enchant {
    public:
    enum Type: int {};
};
class EnchantmentInstance;
enum EquipmentFilter: int {};
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
    static void* getEnchantCosts(ItemStackBase const&, int);
    static bool canEnchant(ItemStackBase const&, int);
    static int getEnchantLevel(Enchant::Type, ItemStackBase const&);
    static void* getLegalEnchants(Item const*);
    static void applyEnchant(ItemStackBase&, ItemEnchants const&, bool);
    static bool isCurse(Enchant::Type);
    static bool hasEnchant(Enchant::Type, ItemStackBase const&);
    static void randomlyEnchant(ItemStack&);
    static void applyEnchant(ItemStackBase&, Enchant::Type, int, bool);
    static void randomlyEnchant(ItemInstance&, int, int, bool);
    static int getBestEnchantLevel(Enchant::Type, Mob const&, EquipmentFilter);
    static void removeEnchants(ItemStack&);
    static void* getBookCasePositions(BlockSource&, Vec3 const&);
    static void combineEnchantedItems(ItemStack const&, ItemStack const&, ItemStack&, bool);
    static void* generateRandomEnchantedBook(int, int);
    static int /*?*/ getLootableRandomEnchantIndex(Random&);
    static void* generateRandomEnchantedItem(Item const&, int, int);
    static void doPostDamageEffects(Actor&, Actor&);
    static int getTotalProtectionLevels(Enchant::Type, Mob const&);
    static int getBookcaseCount(BlockSource&, Vec3 const&);
    static void* _convertBookCheck(ItemStackBase&);
    static float getDamageReduction(ActorDamageSource const&, Mob const&);
    static bool canEnchant(ItemStackBase const&, EnchantmentInstance const&, bool);
    static void* getRandomDamagedItemWithMending(Mob const&);
    static bool hasCurse(ItemStackBase const&);
    static void doPostHurtEffects(Mob&, Mob&);
    static void determineActivation(Enchant::Type);
    static bool isCompatibleWith(Enchant::Type, Enchant::Type);
    static int getEnchantmentId(HashedString const&);
    static void* selectEnchantments(Item const*, int, int, bool);
    static void* getRandomItemWith(Enchant::Type, Mob const&, EquipmentFilter);
    static int getMeleeDamageBonus(Actor const&, Actor&);
    static void randomlyEnchant(ItemStack&, int, int, bool);
    static void* getRandomName();
    static void determineCompatibility(Enchant::Type);
    static void* getEnchantNameAndLevel(Enchant::Type, int);
    static void applyEnchant(ItemStackBase&, EnchantmentInstance const&, bool);
    static void* getAvailableEnchantmentResults(Item const*, int, bool);
    static void* generateEnchantedBook(ItemEnchants const&);
    static void* getEquipmentSet(Mob const&, EquipmentFilter);
    static void* getEnchantingTablePositions(BlockSource&, Vec3 const&);
    static void* generateRandomEnchantedBook();
    static void* generateEnchantedBook(EnchantmentInstance const&);
    static void randomlyEnchant(ItemInstance&);
};


#endif //KEX_ENCHANTUTILS_HPP