#include <stl/string>
#include <stl/vector>

#include <enums.hpp>

#ifndef KEX_ACTOR_HPP
#define KEX_ACTOR_HPP


#ifndef KEX_AABB_HPP
    class AABB;
#endif
class ActorEventCoordinator;
class ActorDamageSource;
#ifndef KEX_ACTORUNIQUEID_HPP
    class ActorUniqueID;
#endif
// class Attribute;
#ifndef KEX_BLOCK_HPP
    // class Block;
#endif
#ifndef KEX_BLOCKPOS_HPP
    class BlockPos;
#endif
class BlockActor {
    public:
    char filler1[72]; // 72
    BlockActorType type; // 76
};
class SignBlockActor {
    public:
    std::__ndk1::string& getMessage();
};
#ifndef KEX_BLOCKSOURCE_HPP
    class BlockSource {
        public:
        BlockActor* getBlockEntity(BlockPos const&);
    };
#endif
class Dimension;
#ifndef KEX_HASHEDSTRING_HPP
    class HashedString;
#endif
class ItemActor;
#ifndef KEX_ITEMSTACK_HPP
    class ItemStack;
#endif
// class ItemStackBase;
#ifndef KEX_LEVEL_HPP
    class Level;
#endif
// class LootTable;
#ifndef KEX_MOBEFFECT_HPP
    class MobEffect;
#endif
#ifndef KEX_MOBEFFECTINSTANCE_HPP
    class MobEffectInstance;
#endif
class MolangVariableMap;
#ifndef KEX_PLAYER_HPP
    class Player;
#endif
class Random;
class RenderParams;
class TickingArea;
// class VariantParameterList;
// #ifndef KEX_VEC2_HPP
//     class Vec2;
// #endif
#ifndef KEX_VEC3_HPP
    class Vec3;
#endif

class Actor {
    public:
    char filler[376]; // 376
    bool onGround; // 377 (+3?)
    static Actor* wrap(long long);
    // enum InitializationMethod: int {};
    // virtual bool hasComponent(HashedString const&) const;
    // virtual int getOnDeathExperience();
    // virtual Vec3* getInterpolatedRidingPosition(float) const;
    // virtual Vec2* getInterpolatedBodyRot(float) const;
    // virtual Vec2* getInterpolatedHeadRot(float) const;
    // virtual float getInterpolatedBodyYaw(float) const;
    // virtual float getYawSpeedInDegreesPerSecond() const;
    // virtual float getInterpolatedWalkAnimSpeed(float) const;
    // virtual void* getInterpolatedRidingOffset(float) const;
    // virtual bool isFireImmune() const;
    // virtual bool breaksFallingBlocks() const;
    // virtual bool blockedByShield(ActorDamageSource const&, Actor&);
    // virtual void teleportTo(Vec3 const&, bool, int, int, ActorUniqueID const&);
    // virtual void chorusFruitTeleport(Vec3&);
    // virtual void lerpTo(Vec3 const&, Vec2 const&, int);
    // virtual void lerpMotion(Vec3 const&);
    // virtual void normalTick();
    // virtual void baseTick();
    // virtual void rideTick();
    // virtual float getRidingHeight();
    // virtual void startRiding(Actor&);
    // virtual void addRider(Actor&);
    // virtual void flagRiderToRemove(Actor&);
    // virtual bool intersects(Vec3 const&, Vec3 const&) const;
    // virtual bool isFree(Vec3 const&, float) const;
    // virtual bool isFree(Vec3 const&);
    // virtual bool isInWall() const;
    // virtual bool isInvisible() const;
    // virtual bool canShowNameTag() const;
    // virtual bool canExistInPeaceful() const;
    // virtual void setNameTagVisible(bool);
    // virtual void* getNameTag() const;
    // virtual void* getNameTagAsHash() const;
    // virtual void* getFormattedNameTag() const;
    // virtual bool getAlwaysShowNameTag() const;
    // virtual void* getScoreTag() const;
    // virtual bool isInWater() const;
    // virtual bool hasEnteredWater() const;
    // virtual bool isImmersedInWater() const;
    // virtual bool isInWaterOrRain() const;
    // virtual bool isInLava() const;
    // virtual bool isUnderLiquid(MaterialType) const;
    // virtual bool isOverWater() const;
    // virtual void makeStuckInBlock(Vec3 const&);
    // virtual void* getCameraOffset() const;
    // virtual void* getShadowHeightOffs() const;
    // virtual float getShadowRadius() const;
    // virtual void* getHeadLookVector(float);
    // virtual bool canSeeInvisible() const;
    // virtual bool canSee(Actor const&) const;
    // virtual void canSee(Vec3 const&) const;
    // virtual bool isSkyLit(float);
    // virtual float getBrightness(float) const;
    // virtual void interactPreventDefault();
    // virtual void playerTouch(Player&);
    // virtual void onAboveBubbleColumn(bool); 
    // virtual bool isImmobile() const;
    // virtual bool isSilent() const;
    // virtual bool isPickable() const;
    // virtual bool isFishable() const;
    // virtual bool isSleeping() const;
    // virtual bool isShootable() const;
    // virtual void setSneaking(bool) const;
    // virtual bool isBlocking() const;
    // virtual bool isDamageBlocked(ActorDamageSource const&) const;
    // virtual bool isAlive() const;
    // virtual bool isOnFire() const;
    // virtual bool isOnHotBlock() const;
    // virtual bool isCreativeModeAllowed() const;
    // virtual bool isSurfaceMob() const;
    // virtual bool isTargetable() const;
    // virtual bool isLocalPlayer() const;
    // virtual bool isPlayer() const;
    // virtual bool canAttack(Actor*, bool) const;
    // virtual void setTarget(Actor*);
    // virtual void findAttackTarget();
    // virtual bool isValidTarget(Actor*) const;
    // virtual void attack(Actor&);
    // virtual void performRangedAttack(Actor&, float);
    // virtual void adjustDamageAmount(int&) const;
    // virtual int getEquipmentCount() const;
    // virtual void setOwner(ActorUniqueID);
    // virtual void setSitting(bool);
    // virtual void onTame();
    // virtual void onFailedTame();
    // virtual int getInventorySize();
    // virtual int getEquipSlots() const;
    // virtual int getChestSlots() const;
    // virtual void setStanding(bool);
    // virtual bool canPowerJump() const;
    // virtual void setCanPowerJump(bool);
    // virtual bool isJumping() const;
    // virtual bool isEnchanted() const;
    // virtual void rideJumped();
    // virtual void rideLanded(Vec3 const&, Vec3 const&);
    // virtual bool shouldRender() const;
    // virtual bool isInvulnerableTo(ActorDamageSource const&) const;
    // virtual void* getBlockDamageCause(Block const&) const;
    // virtual void actuallyHurt(int, ActorDamageSource const&, bool);
    // virtual void animateHurt();
    // virtual void doFireHurt(int);
    // virtual void onLightningHit();
    // virtual void onBounceStarted(BlockPos const&, Block const&);
    // virtual void feed(int);
    // virtual void handleEntityEvent(ActorEvent, int);
    // virtual float getPickRadius() const;
    // virtual HashedString& getActorRendererId() const;
    // virtual void despawn();
    // virtual void killed(Actor&);
    // virtual void awardKillSource(Actor&, int);
    // virtual void setArmor(ArmorSlot, ItemStack const&);
    // virtual ItemStack* getArmor(ArmorSlot) const;
    // virtual MaterialType getArmorMaterialTypeInSlot(ArmorSlot) const;
    // virtual ArmorTextureType getArmorMaterialTextureTypeInSlot(ArmorSlot) const;
    // virtual void* getArmorColorInSlot(ArmorSlot, int) const;
    // virtual ItemStack* getEquippedSlot(EquipmentSlot) const;
    // virtual void setEquippedSlot(EquipmentSlot, ItemStack const&);
    // virtual ItemStack* getCarriedItem() const;
    // virtual void setCarriedItem(ItemStack const&);
    // virtual void setOffhandSlot(ItemStack const&);
    // virtual ItemStack* getEquippedTotem() const;
    // virtual void consumeTotem();
    // virtual void setOnFire(int);
    // virtual ActorType getEntityTypeId() const;
    // virtual AABB& getHandleWaterAABB() const;
    // virtual void handleInsidePortal(BlockPos const&);
    // virtual int getPortalCooldown() const;
    // virtual int getPortalWaitTime() const;
    // virtual int getDimensionId() const;
    // virtual bool canChangeDimensions() const;
    // virtual Player* getControllingPlayer() const;
    // virtual void checkFallDamage(float, bool);
    // virtual void causeFallDamage(float);
    // virtual void handleFallDistanceOnServer(float, bool);
    // virtual bool canAddRider(Actor&) const;
    // virtual bool canPickupItem(ItemStack const&) const;
    // virtual bool canBePulledIntoVehicle() const;
    // virtual bool inCaravan() const;
    // virtual bool isLeashableType() const;
    // virtual void tickLeash();
    // virtual void stopRiding(bool, bool, bool);
    // virtual void startSwimming();
    // virtual void stopSwimming();
    // virtual void* getCommandPermissionLevel() const;
    // virtual void* getMutableAttribute(Attribute const&);
    // virtual void* getAttribute(Attribute const&) const;
    // virtual int getDeathTime() const;
    // virtual void heal(int);
    // virtual bool isInvertedHealAndHarm() const;
    // virtual bool canBeAffected(int) const;
    // virtual bool canBeAffected(MobEffectInstance const&) const;
    // virtual bool canBeAffectedByArrow(MobEffectInstance const&) const;
    // virtual void openContainerComponent(Player&);
    // virtual void swing();
    // virtual void useItem(ItemStackBase&, ItemUseMethod, bool);
    // virtual bool hasOutputSignal(unsigned char) const;
    // virtual int getOutputSignal() const;
    // virtual void* getMapDecorationRotation() const;
    // virtual float getRiderYRotation(Actor const&) const;
    // virtual float getYHeadRot() const;
    // virtual bool isWorldBuilder() const;
    // virtual bool isCreative() const;
    // virtual bool isAdventure() const;
    // virtual void add(ItemStack&);
    // virtual void drop(ItemStack const&, bool);
    // virtual bool canDestroyBlock(Block const&) const;
    // virtual void setAuxValue(int);
    // virtual void setSize(float, float);
    // virtual int getLifeSpan() const;
    // virtual void wobble();
    // virtual bool wasHurt();
    // virtual void startSpinAttack();
    // virtual void stopSpinAttack();
    // virtual void setDamageNearbyMobs(bool);
    // virtual int getDeletionDelayTimeSeconds() const;
    // virtual void kill();
    // virtual void die(ActorDamageSource const&);
    // virtual bool shouldTick() const;
    // virtual void updateEntitySpecificMolangVariables(RenderParams&);
    // virtual bool shouldTryMakeStepSound();
    // virtual void* getNextStep(float);
    // virtual bool canMakeStepSound() const;
    // virtual bool outOfWorld();
    // virtual void markHurt();
    // virtual void pushOutOfBlocks(Vec3 const&);
    // virtual void doWaterSplashEffect();
    // virtual void spawnTrailBubbles();
    // virtual LootTable* getLootTable();
    // virtual LootTable* getDefaultLootTable();
    bool isBreakingObstruction() const;
    void setDancing(bool);
    void healEffects(int);
    PaletteColor getColor() const;
    bool isInClouds() const;
    bool hasUniqueID() const;
    int getHurtDir() const;
    void setEnchanted(bool);
    int getMarkVariant() const;
    bool hasDimension() const;
    bool wasLastHitByPlayer();
    void* _getBlockWhenClimbing() const;
    bool hasSaddle() const;
    bool isDelayedAttacking() const;
    bool canBeginOrContinueClimbingLadder() const;
    int getStructuralIntegrity() const;
    Level* getLevel() const;
    void setCameraDistance(float);
    float distanceSqrToBlockPosCenter(BlockPos const&) const;
    void _setHeightOffset(float);
    bool hasTags() const;
    void setDoorOpener(bool);
    void setColor2(PaletteColor);
    bool hasType(ActorType) const;
    void removeEffectNoUpdate(int);
    bool isInSnow() const;
    bool canMate(Actor const&) const;
    MobEffectInstance* getEffect(MobEffect const&) const;
    bool hasTickingArea() const;
    bool getIsOnScreen() const;
    bool isOverScaffolding() const;
    bool shouldOrphan(BlockSource&);
    void setTradingPlayer(Player*);
    bool isPredictedMovementEnabled() const;
    //addDefinitionGroup
    bool isInRain() const;
    void setWASDControlled(bool);
    bool hasPriorityAmmunition() const;
    void* getHurtColor() const;
    bool hasRuntimeID() const;
    int getVariant() const;
    bool isRiding(Actor*) const;
    bool getStatusFlag(ActorFlags) const;
    bool isChested() const;
    bool isStackable() const;
    bool isRider(Actor const&) const;
    void setResting(bool);
    float getHealth() const;
    int getControllingSeat();
    bool isInsidePortal() const;
    bool hasTeleported() const;
    void moveRelative(float, float, float, float);
    bool isRider(ActorUniqueID const&) const;
    void* getCurrentSwimAmount() const;
    BlockSource* getRegion() const;
    bool isTame() const;
    float getMaxHealth() const;
    void* getPersistingTradeOffer() const;
    bool isLeashed() const;
    void setMoving(bool);
    bool hasTotemEquipped() const;
    void removeAllRiders(bool, bool);
    int getActiveEffectCount() const;
    void setAutonomous(bool);
    bool isPersistent() const;
    void removeEntity();
    void setCollidableMob(bool);
    void* getActorIdentifier() const;
    bool hasFishingHook() const;
    bool getChainedDamageEffects() const;
    bool isPacified() const;
    float distanceTo(Actor const&) const;
    bool canCurrentlySwim() const;
    bool hasFamily(HashedString const&) const;
    void setChainedDamageEffects(bool);
    bool hasPlayerRider() const;
    bool hasAttributeBuff(AttributeBuffType) const;
    bool isClientSide() const;
    bool isControlledByLocalInstance() const;
    void setColor(PaletteColor);
    bool isClimbing() const;
    bool hasEffect(MobEffect const&) const;
    void* getInterpolatedPosition(float) const;
    void setSkinID(int);
    bool hasAnyVisibleEffects() const;
    float getSpeedInMetersPerSecond() const;
    void setStrengthMax(int);
    bool getDamageNearbyMobs() const;
    void setLayingDown(bool);
    void removeEffect(int);
    void setClimbing(bool);
    void setTempted(bool);
    bool isOrphan() const;
    void dropTowards(ItemStack const&, Vec3);
    bool isTrading() const;
    bool inDownwardFlowingLiquid() const;
    int getJumpDuration() const;
    bool isScared() const;
    Random* getRandom() const;
    MolangVariableMap* getMolangVariables() const;
    RenderParams* getRenderParams() const;
    bool isSitting() const;
    bool isBaby() const;
    bool isIgnited() const;
    void setLimitedLife(int);
    void setStrength(int);
    void setInvisible(bool);
    void setFishingHookID(ActorUniqueID);
    void setLeashHolder(ActorUniqueID);
    bool isType(ActorType) const;
    bool isInWorld() const;
    bool isInLove() const;
    void* getLocator(HashedString const&);
    Player* getTradingPlayer() const;
    bool isDoorBreaker() const;
    bool isAutonomous() const;
    bool isWASDControlled();
    void setScared(bool);
    bool hasAnyEffects() const;
    void setAABB(AABB const&);
    bool isRiding() const;
    bool isDoorOpener() const;
    bool isSafeToSleepNear() const;
    TickingArea* getTickingArea();
    void setBlockTarget(BlockPos const&);
    bool hasPersistingTrade() const;
    bool canClimb() const;
    float distanceTo(Vec3 const&) const;
    bool getTempted() const;
    void setBreakingObstruction(bool);
    Actor* getRide() const;
    int getStrength() const;
    bool isAngry() const;
    bool isSwimmer() const;
    bool canOpenContainer(Player&) const;
    bool isPowered() const;
    bool isSheared() const;
    void setCollidableMobNear(bool);
    bool getCollidableMobNear();
    void setDoorBreaker(bool);
    PaletteColor getColor2() const;
    bool isWalker() const;
    bool isCharged() const;
    //removeTag
    bool canFly() const;
    bool isInPrecipitation() const;
    void setCanClimb(bool);
    void removeAllEffects();
    bool isOutOfControl() const;
    void setIsOnScreen(bool);
    bool isSneaking() const;
    Actor* getTarget() const;
    void setStunned(bool);
    void setVariant(int);
    short getTotalAirSupply() const;
    bool hasLevel() const;
    void setMarkVariant(int);
    bool isInThunderstorm() const;
    bool isBribed() const;
    void pickUpItem(ItemActor&, int);
    Actor* getOwner() const;
    bool getCanPickupItems() const;
    bool isStanding() const;
    void setSwimmer(bool);
    ActorUniqueID* getUniqueID() const;
    int getStrengthMax() const;
    bool isLayingDown() const;
    void setPowered(bool);
    void setStructuralIntegrity(int);
    void setControllingSeat(int);
    void setHurtDir(int);
    Dimension* getDimension() const;
    Actor* getLeashHolder() const;
    bool isDancing() const;
    void setInLove(Actor*);
    void setCharged(bool);
    void setShakeTime(int);
    bool isInScaffolding() const;
    void consumeItem(ItemActor&, int);
    bool hasCategory(ActorCategory) const;
    bool isInsideBorderBlock(float) const;
    void* getSwimAmount(float) const;
    void setCanFly(bool);
    int getSkinID() const;
    std::__ndk1::vector<MobEffectInstance>& getAllEffects() const;
    bool hasRider() const;
    void setJumpDuration(int);
    bool isSwimming() const;
    short getAirSupply() const;
    float getCameraDistance();
    void addEffect(MobEffectInstance const&);
    bool isMoving() const;
    float getVerticalSpeedInMetersPerSecond() const;
    bool isTrusting() const;
    void setDelayedAttacking(bool);
    void setWalker(bool);
    int getShakeTime() const;
    float getRadius() const;
    bool isResting() const;
    void setSaddle(bool);
    void hurt(ActorDamageSource const&, int, bool, bool);
    template<typename Component> Component* tryGetComponent();
};


class ActorClassTree {
    public:
    static bool hasCategory(ActorCategory const&, ActorCategory);
    static bool isTypeInstanceOf(ActorType, ActorType);
    static void* getEntityTypeIdLegacy(ActorType);
    static bool isMobLegacy(ActorType);
    static bool isOfType(ActorType, ActorType);
    static bool isInstanceOf(Actor const&, ActorType);
    static bool isMob(ActorType);
    static bool isHangingEntity(Actor const&);
};


#endif //KEX_ACTOR_HPP