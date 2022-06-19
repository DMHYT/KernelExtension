#include <stl/string>
#include <stl.h>

#include <enums.hpp>

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
class CreativeItemRegistry;
#ifndef KEX_HASHEDSTRING_HPP
    class HashedString;
#endif
class IDataInput;
class IDataOutput;
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
    // virtual int getMaxUseDuration(const ItemStack*) const;
    // virtual bool isMusicDisk() const;
    // virtual void* executeEvent(ItemStackBase&, const stl::string&, RenderParams&) const;
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
    // virtual bool canDestroySpecial(const Block&) const;
    // virtual void* getLevelDataForAuxValue(int) const;
    // virtual bool isStackedByData() const;
    // virtual int getMaxDamage() const;
    // virtual int getAttackDamage() const;
    // virtual bool isHandEquipped() const;
    // virtual bool isGlint(const ItemStackBase&) const;
    // virtual bool isPattern() const;
    // virtual int /*?*/ getPatternIndex() const;
    // virtual bool showsDurabilityInCreative() const;
    // virtual bool isWearableThroughLootTable(const CompoundTag*) const;
    // virtual bool canDestroyInCreative() const;
    // virtual bool isDestructive(int) const;
    // virtual bool isLiquidClipItem(int) const;
    // virtual bool shouldInteractionWithBlockBypassLiquid(const Block&) const;
    // virtual bool requiresInteract() const;
    // virtual void* appendFormattedHovertext(const ItemStackBase&, Level&, stl::string&, bool) const;
    // virtual bool isValidRepairItem(const ItemStackBase&, const ItemStackBase&) const;
    // virtual void* getEnchantSlot() const;
    // virtual int getEnchantValue() const;
    // virtual int getArmorValue() const;
    // virtual bool isComplex() const;
    // virtual bool isValidAuxValue(int) const;
    // virtual float /*?*/ getDamageChance(int) const;
    // virtual bool uniqueAuxValues() const;
    // virtual bool isActorPlacerItem() const;
    // virtual bool isMultiColorTinted(const ItemStack&) const;
    // virtual mce::Color* getColor(const CompoundTag*, const ItemDescriptor&) const;
    // virtual bool hasCustomColor(const ItemStackBase&) const;
    // virtual bool hasCustomColor(const CompoundTag*) const;
    // virtual void* clearColor(ItemStackBase&) const;
    // virtual void* clearColor(CompoundTag*) const;
    // virtual void setColor(ItemStackBase&, const mce::Color&) const;
    // virtual mce::Color* getBaseColor(const ItemStack&) const;
    // virtual mce::Color* getSecondaryColor(const ItemStack&) const;
    // virtual void* getActorIdentifier(const ItemStack&) const;
    // virtual void* saveAdditionalData(const ItemStackBase&, CompoundTag&) const;
    // virtual void* readAdditionalData(ItemStackBase&, const CompoundTag&) const;
    // virtual void* buildIdAux(short, const CompoundTag*) const;
    // virtual ItemDescriptor* buildDescriptor(short, const CompoundTag*) const;
    // virtual void* use(ItemStack&, Player&) const;
    // virtual void* dispense(BlockSource&, Container&, int, const Vec3&, unsigned char) const;
    // virtual void* useTimeDepleted(ItemStack&, Level*, Player*) const;
    // virtual void* releaseUsing(ItemStack&, Player*, int) const;
    // virtual float /*?*/ getDestroySpeed(const ItemStackBase&, const Block&) const;
    // virtual bool hurtActor(ItemStack&, Actor&, Mob&) const;
    // virtual void* hitActor(ItemStack&, Actor&, Mob&) const;
    // virtual void* hitBlock(ItemStack&, const Block&, const BlockPos&, Mob&) const;
    // virtual bool mineBlock(ItemStack&, const Block&, int, int, int, Actor*) const;
    // virtual void* buildDescriptionName(const ItemStackBase&) const;
    // virtual void* buildDescriptionId(const ItemDescriptor&, const CompoundTag*) const;
    // virtual void* buildEffectDescriptionName(const ItemStackBase&) const;
    // virtual void* buildCategoryDescriptionName() const;
    // virtual void* readUserData(ItemStackBase&, IDataInput&, ReadOnlyBinaryStream&) const;
    // virtual void* writeUserData(const ItemStackBase&, IDataOutput&) const;
    // virtual unsigned char getMaxStackSize(const ItemDescriptor&) const;
    // virtual void* inventoryTick(ItemStack&, Level&, Actor&, int, bool) const;
    // virtual void* refreshedInContainer(const ItemStackBase&, Level&) const;
    // virtual void* getCooldownType() const;
    // virtual int getCooldownTime() const;
    // virtual void* fixupCommon(ItemStackBase&) const;
    // virtual void* fixupCommon(ItemStackBase&, Level&) const;
    // virtual short getDamageValue(const CompoundTag*) const;
    // virtual void setDamageValue(ItemStackBase&, short) const;
    // virtual void* getInHandUpdateType(const Player&, const ItemInstance&, const ItemInstance&, bool, bool) const;
    // virtual void* getInHandUpdateType(const Player&, const ItemStack&, const ItemStack&, bool, bool) const;
    // virtual bool validFishInteraction(int) const;
    // virtual bool isSameItem(const ItemStackBase&, const ItemStackBase&) const;
    // virtual void initClient(Json::Value&, Json::Value&);
    // virtual void* getInteractText(const Player&) const;
    // virtual void* getAnimationFrameFor(Mob*, bool, const ItemStack*, bool) const;
    // virtual bool isEmissive(int) const;
    // virtual int getLightEmission(int) const;
    // virtual const stl::string& getIcon(const ItemStackBase&, int, bool) const;
    // virtual int getIconYOffset() const;
    // virtual void setIcon(const stl::string&, int);
    // virtual void setIcon(const TextureUVCoordinateSet&);
    // virtual void setIconAtlas(const stl::string&, int);
    // virtual bool canBeCharged() const;
    // virtual void* playSoundIncrementally(const ItemInstance&, Mob&) const;
    // virtual float getFurnaceBurnIntervalMultipler(const ItemStackBase&) const;
    // virtual float getFurnaceXPmultiplier(const ItemStackBase&) const;
    // virtual void* getAuxValuesDescription() const;
    // virtual void* _checkUseOnPermissions(Actor&, ItemStackBase&, unsigned const char&, const BlockPos&) const;
    // virtual void* _calculatePlacePos(ItemStackBase&, Actor&, unsigned char&, BlockPos&) const;
    // virtual void* _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;
    Item(const stl::string&, short);
    void setIsMirroredArt(bool);
    void resetId(short);
    void* getCommandName() const;
    int getFrameCount() const;
    void setCreativeGroup(const stl::string&);
    void reloadIcon();
    HashedString& getFullNameHash() const;
    bool allowOffhand() const;
    void beginCreativeGroup(const stl::string&, const ItemInstance&);
    void addCreativeItem(const ItemInstance&);
    void _addLooseCreativeItemsClient();
    const stl::string& getDescriptionId() const;
    void addCreativeItem(Item*, short);
    void* fixupOnLoad(ItemStackBase&) const;
    bool isAnimatedInToolbar() const;
    void startCreativeItemDefinitions(bool, CreativeItemRegistry*);
    void* getRenderingScaleAdjustment() const;
    TextureUVCoordinateSet* getIconTextureUVSet(const TextureAtlasItem&, int, int);
    void* useOn(ItemStack&, Actor&, int, int, int, unsigned char, float, float, float) const;
    void* getRenderingRotAdjustment() const;
    void addOnResetBAIcallback(stl::function<void()> const&);
    bool usesRenderingAdjustment() const;
    bool isNameTag() const;
    bool canUseSeed(Actor&, BlockPos, unsigned char) const;
    bool isFlyEnabled(const ItemInstance&);
    void* getIconTexture() const;
    short toBlockId(short);
    void* fixupOnLoad(ItemStackBase&, Level&) const;
    void* getTextureItem(const stl::string&);
    TextureUVCoordinateSet* getTextureUVCoordinateSet(const stl::string&, int);
    void setDescriptionId(const stl::string&);
    const stl::string& getCreativeGroup() const;
    void setCategory(CreativeItemCategory);
    float /*?*/ destroySpeedBonus(const ItemStackBase&) const;
    void* executeOnResetBAIcallbacks() const;
    void setMinRequiredBaseGameVersion(const BaseGameVersion&);
    void addLooseCreativeItems(bool, const BaseGameVersion&);
    void setFurnaceBurnIntervalMultiplier(float);
    bool shouldDespawn() const;
    void* _tryCorrectAnyAuxValue(ItemStackBase&) const;
    void beginCreativeGroup(const stl::string&, const Block*, const CompoundTag*);
    bool isElytra(const ItemDescriptor&);
    void* getSeed() const;
    bool isExplodable() const;
    UseAnimation getUseAnimation() const;
    bool hasTag(unsigned long const long&) const;
    void alterAvailableCreativeItem(ActorInfoRegistry*, LevelData&);
    CreativeItemCategory getCreativeCategory() const;
    BlockLegacy* getLegacyBlock() const;
    bool isSeed() const;
    bool isElytraBroken(int);
    bool isMirroredArt() const;
    void* getRenderingPosAdjustment() const;
    HashedString& getRawNameHash() const;
    const stl::string& getRawNameId() const;
    BaseGameVersion* getRequiredBaseGameVersion() const;
    void setFurnaceXPmultiplier(float);
    void _addLooseCreativeItemsServer(const BaseGameVersion&);
    void endCreativeGroup();
    void ignoresPermissions() const;
    char* getFullItemName() const;
    void setAllowOffhand(bool);
    void endCreativeItemDefinitions(bool);
    bool isFireResistant() const;
    bool _textMatch(const stl::string&, const stl::string&, bool);
    const stl::string& getSerializedName() const;
    const stl::string& getNamespace() const;
    void addTag(const HashedString&);
    void setAtlasItemManager(stl::shared_ptr<AtlasItemManager>);
    void beginCreativeGroup(const stl::string&, Item*, short, const CompoundTag*);
    void addCreativeItem(const ItemStack&);
    int getId() const;
    void* updateCustomBlockEntityTag(BlockSource&, ItemStackBase&, const BlockPos&) const;
    void addCreativeItem(const Block&);
    bool hasTag(const HashedString&) const;
    bool isElytra() const;
    void* getRendererId() const;
    void beginCreativeGroup(const stl::string&, short, short, const CompoundTag*);
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