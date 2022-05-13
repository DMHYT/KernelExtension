#include <stl/string>

#ifndef KEX_ITEM_HPP
#define KEX_ITEM_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
class ActorInfoRegistry;
class AtlasItemManager;
class BaseGameVersion;
#ifndef KEX_BLOCK_HPP
    class Block;
#endif
#ifndef KEX_BLOCKLEGACY_HPP
    class BlockLegacy;
#endif
#ifndef KEX_BLOCKPOS_HPP
    class BlockPos;
#endif
class BlockSource;
class CompoundTag;
class Container;
enum CreativeItemCategory: int {};
class CreativeItemRegistry;
class HashedString;
class IDataInput;
class IDataOutput;
enum ItemAcquisitionMethod: int {};
class ItemDescriptor;
#ifndef KEX_ITEMINSTANCE_HPP
    class ItemInstance;
#endif
#ifndef KEX_ITEMSTACK_HPP
    class ItemStack;
#endif
#ifndef KEX_ITEMSTACKBASE_HPP
    class ItemStackBase;
#endif
#ifndef CPPTL_JSON_H_INCLUDED
    namespace Json {
        class Value;
    }
#endif
#ifndef KEX_LEVEL_HPP
    class Level;
#endif
class LevelData;
namespace mce { class Color; }
#ifndef KEX_MOB_HPP
    class Mob;
#endif
#ifndef KEX_PLAYER_HPP
    class Player;
#endif
class ReadOnlyBinaryStream;
class RenderParams;
class TextureAtlasItem;
class TextureUVCoordinateSet;
enum UseAnimation : int {};
#ifndef KEX_VEC3_HPP
    class Vec3;
#endif

class Item {
    public:
    char filler1[84]; // 88
    short maxStack; // 90
    short id; // 92
    char filler2[84]; // 176
    int maxDamage; // 180
    int maxUseDuration; // 184
    char filler3[116]; // 300
    virtual void initServer(Json::Value&);
    // virtual void tearDown();
    // virtual int getMaxUseDuration(ItemStack const*) const;
    // virtual bool isMusicDisk() const;
    // virtual void* executeEvent(ItemStackBase&, std::__ndk1::string const&, RenderParams&) const;
    // virtual bool isComponentBased() const;
    // virtual bool isArmor() const;
    // virtual bool isBlockPlanterItem() const;
    // virtual bool isBucket() const;
    // virtual bool isCamera() const;
    // virtual bool isDamageable() const;
    // virtual bool isDyeable() const;
    // virtual bool isDye() const;
    // virtual void* getItemColor() const;
    // virtual bool isFertilizer() const;
    // virtual bool isFood() const;
    // virtual bool isThrowable() const;
    // virtual bool isUseable() const;
    // virtual void* getCamera() const;
    // virtual void* getFood() const;
    // virtual void* getFuel() const;
    // virtual void setMaxStackSize(unsigned char);
    // virtual void setStackedByData(bool);
    // virtual void setMaxDamage(int);
    // virtual void setHandEquipped();
    // virtual void setUseAnimation(UseAnimation);
    // virtual void setMaxUseDuration(int);
    void setRequiresWorldBuilder(bool);
    void setExplodable(bool);
    void setFireResistant(bool);
    // virtual void setIsGlint(bool);
    void setShouldDespawn(bool);
    // virtual void* getBlockShape() const;
    // virtual bool canBeDepleted() const;
    // virtual bool canDestroySpecial(Block const&) const;
    // virtual void* getLevelDataForAuxValue(int) const;
    // virtual bool isStackedByData() const;
    // virtual int getMaxDamage() const;
    // virtual int getAttackDamage() const;
    // virtual bool isHandEquipped() const;
    // virtual bool isGlint(ItemStackBase const&) const;
    // virtual bool isPattern() const;
    // virtual int /*?*/ getPatternIndex() const;
    // virtual bool showsDurabilityInCreative() const;
    // virtual bool isWearableThroughLootTable(CompoundTag const*) const;
    // virtual bool canDestroyInCreative() const;
    // virtual bool isDestructive(int) const;
    // virtual bool isLiquidClipItem(int) const;
    // virtual bool shouldInteractionWithBlockBypassLiquid(Block const&) const;
    // virtual bool requiresInteract() const;
    // virtual void* appendFormattedHovertext(ItemStackBase const&, Level&, std::__ndk1::string&, bool) const;
    // virtual bool isValidRepairItem(ItemStackBase const&, ItemStackBase const&) const;
    // virtual void* getEnchantSlot() const;
    // virtual int getEnchantValue() const;
    // virtual int getArmorValue() const;
    // virtual bool isComplex() const;
    // virtual bool isValidAuxValue(int) const;
    // virtual float /*?*/ getDamageChance(int) const;
    // virtual bool uniqueAuxValues() const;
    // virtual bool isActorPlacerItem() const;
    // virtual bool isMultiColorTinted(ItemStack const&) const;
    // virtual mce::Color* getColor(CompoundTag const*, ItemDescriptor const&) const;
    // virtual bool hasCustomColor(ItemStackBase const&) const;
    // virtual bool hasCustomColor(CompoundTag const*) const;
    // virtual void* clearColor(ItemStackBase&) const;
    // virtual void* clearColor(CompoundTag*) const;
    // virtual void setColor(ItemStackBase&, mce::Color const&) const;
    // virtual mce::Color* getBaseColor(ItemStack const&) const;
    // virtual mce::Color* getSecondaryColor(ItemStack const&) const;
    // virtual void* getActorIdentifier(ItemStack const&) const;
    // virtual void* saveAdditionalData(ItemStackBase const&, CompoundTag&) const;
    // virtual void* readAdditionalData(ItemStackBase&, CompoundTag const&) const;
    // virtual void* buildIdAux(short, CompoundTag const*) const;
    // virtual ItemDescriptor* buildDescriptor(short, CompoundTag const*) const;
    // virtual void* use(ItemStack&, Player&) const;
    // virtual void* dispense(BlockSource&, Container&, int, Vec3 const&, unsigned char) const;
    // virtual void* useTimeDepleted(ItemStack&, Level*, Player*) const;
    // virtual void* releaseUsing(ItemStack&, Player*, int) const;
    // virtual float /*?*/ getDestroySpeed(ItemStackBase const&, Block const&) const;
    // virtual bool hurtActor(ItemStack&, Actor&, Mob&) const;
    // virtual void* hitActor(ItemStack&, Actor&, Mob&) const;
    // virtual void* hitBlock(ItemStack&, Block const&, BlockPos const&, Mob&) const;
    // virtual bool mineBlock(ItemStack&, Block const&, int, int, int, Actor*) const;
    // virtual void* buildDescriptionName(ItemStackBase const&) const;
    // virtual void* buildDescriptionId(ItemDescriptor const&, CompoundTag const*) const;
    // virtual void* buildEffectDescriptionName(ItemStackBase const&) const;
    // virtual void* buildCategoryDescriptionName() const;
    // virtual void* readUserData(ItemStackBase&, IDataInput&, ReadOnlyBinaryStream&) const;
    // virtual void* writeUserData(ItemStackBase const&, IDataOutput&) const;
    // virtual unsigned char getMaxStackSize(ItemDescriptor const&) const;
    // virtual void* inventoryTick(ItemStack&, Level&, Actor&, int, bool) const;
    // virtual void* refreshedInContainer(ItemStackBase const&, Level&) const;
    // virtual void* getCooldownType() const;
    // virtual int getCooldownTime() const;
    // virtual void* fixupCommon(ItemStackBase&) const;
    // virtual void* fixupCommon(ItemStackBase&, Level&) const;
    // virtual short getDamageValue(CompoundTag const*) const;
    // virtual void setDamageValue(ItemStackBase&, short) const;
    // virtual void* getInHandUpdateType(Player const&, ItemInstance const&, ItemInstance const&, bool, bool) const;
    // virtual void* getInHandUpdateType(Player const&, ItemStack const&, ItemStack const&, bool, bool) const;
    // virtual bool validFishInteraction(int) const;
    // virtual bool isSameItem(ItemStackBase const&, ItemStackBase const&) const;
    // virtual void initClient(Json::Value&, Json::Value&);
    // virtual void* getInteractText(Player const&) const;
    // virtual void* getAnimationFrameFor(Mob*, bool, ItemStack const*, bool) const;
    // virtual bool isEmissive(int) const;
    // virtual int getLightEmission(int) const;
    // virtual std::__ndk1::string const& getIcon(ItemStackBase const&, int, bool) const;
    // virtual int getIconYOffset() const;
    // virtual void setIcon(std::__ndk1::string const&, int);
    // virtual void setIcon(TextureUVCoordinateSet const&);
    // virtual void setIconAtlas(std::__ndk1::string const&, int);
    // virtual bool canBeCharged() const;
    // virtual void* playSoundIncrementally(ItemInstance const&, Mob&) const;
    // virtual float getFurnaceBurnIntervalMultipler(ItemStackBase const&) const;
    // virtual float getFurnaceXPmultiplier(ItemStackBase const&) const;
    // virtual void* getAuxValuesDescription() const;
    // virtual void* _checkUseOnPermissions(Actor&, ItemStackBase&, unsigned char const&, BlockPos const&) const;
    // virtual void* _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const;
    // virtual void* _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
    Item(std::__ndk1::string const&, short);
    void setIsMirroredArt(bool);
    void resetId(short);
    void* getCommandName() const;
    int getFrameCount() const;
    void setCreativeGroup(std::__ndk1::string const&);
    void reloadIcon();
    HashedString& getFullNameHash() const;
    bool allowOffhand() const;
    void beginCreativeGroup(std::__ndk1::string const&, ItemInstance const&);
    void addCreativeItem(ItemInstance const&);
    void _addLooseCreativeItemsClient();
    std::__ndk1::string const& getDescriptionId() const;
    void addCreativeItem(Item*, short);
    void* fixupOnLoad(ItemStackBase&) const;
    bool isAnimatedInToolbar() const;
    void startCreativeItemDefinitions(bool, CreativeItemRegistry*);
    void* getRenderingScaleAdjustment() const;
    TextureUVCoordinateSet* getIconTextureUVSet(TextureAtlasItem const&, int, int);
    void* useOn(ItemStack&, Actor&, int, int, int, unsigned char, float, float, float) const;
    void* getRenderingRotAdjustment() const;
    void addOnResetBAIcallback(std::__ndk1::function<void()> const&);
    bool usesRenderingAdjustment() const;
    bool isNameTag() const;
    bool canUseSeed(Actor&, BlockPos, unsigned char) const;
    bool isFlyEnabled(ItemInstance const&);
    void* getIconTexture() const;
    short toBlockId(short);
    void* fixupOnLoad(ItemStackBase&, Level&) const;
    void* getTextureItem(std::__ndk1::string const&);
    TextureUVCoordinateSet* getTextureUVCoordinateSet(std::__ndk1::string const&, int);
    void setDescriptionId(std::__ndk1::string const&);
    std::__ndk1::string const& getCreativeGroup() const;
    void setCategory(CreativeItemCategory);
    float /*?*/ destroySpeedBonus(ItemStackBase const&) const;
    void* executeOnResetBAIcallbacks() const;
    void setMinRequiredBaseGameVersion(BaseGameVersion const&);
    void addLooseCreativeItems(bool, BaseGameVersion const&);
    void setFurnaceBurnIntervalMultiplier(float);
    bool shouldDespawn() const;
    void* _tryCorrectAnyAuxValue(ItemStackBase&) const;
    void beginCreativeGroup(std::__ndk1::string const&, Block const*, CompoundTag const*);
    bool isElytra(ItemDescriptor const&);
    void* getSeed() const;
    bool isExplodable() const;
    UseAnimation getUseAnimation() const;
    bool hasTag(unsigned long long const&) const;
    void alterAvailableCreativeItem(ActorInfoRegistry*, LevelData&);
    CreativeItemCategory getCreativeCategory() const;
    BlockLegacy* getLegacyBlock() const;
    bool isSeed() const;
    bool isElytraBroken(int);
    bool isMirroredArt() const;
    void* getRenderingPosAdjustment() const;
    HashedString& getRawNameHash() const;
    std::__ndk1::string const& getRawNameId() const;
    BaseGameVersion* getRequiredBaseGameVersion() const;
    void setFurnaceXPmultiplier(float);
    void _addLooseCreativeItemsServer(BaseGameVersion const&);
    void endCreativeGroup();
    void ignoresPermissions() const;
    char* getFullItemName() const;
    void setAllowOffhand(bool);
    void endCreativeItemDefinitions(bool);
    bool isFireResistant() const;
    bool _textMatch(std::__ndk1::string const&, std::__ndk1::string const&, bool);
    std::__ndk1::string const& getSerializedName() const;
    std::__ndk1::string const& getNamespace() const;
    void addTag(HashedString const&);
    void setAtlasItemManager(std::__ndk1::shared_ptr<AtlasItemManager>);
    void beginCreativeGroup(std::__ndk1::string const&, Item*, short, CompoundTag const*);
    void addCreativeItem(ItemStack const&);
    int getId() const;
    void* updateCustomBlockEntityTag(BlockSource&, ItemStackBase&, BlockPos const&) const;
    void addCreativeItem(Block const&);
    bool hasTag(HashedString const&) const;
    bool isElytra() const;
    void* getRendererId() const;
    void beginCreativeGroup(std::__ndk1::string const&, short, short, CompoundTag const*);
    void* _helpChangeInventoryItemInPlace(Actor&, ItemStack&, ItemStack&, ItemAcquisitionMethod) const;
    public:
    class Tier {
        public:
        char filler[20];
        Tier(int level, int uses, float speed, int attackDamageBonus, int enchantmentValue);
        int getUses() const;
        int getLevel() const;
        int getEnchantmentValue() const;
        int getAttackDamageBonus() const;
        float getSpeed() const;
    };
};

class VanillaItemTiers {
    public:
    static Item::Tier WOOD;
    static Item::Tier STONE;
    static Item::Tier IRON;
    static Item::Tier DIAMOND;
    static Item::Tier GOLD;
    static Item::Tier NETHERITE;
};


#endif //KEX_ITEM_HPP