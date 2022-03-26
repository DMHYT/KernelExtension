#include <Player.hpp>

#ifndef KEX_LOCALPLAYER_HPP
#define KEX_LOCALPLAYER_HPP


class LocalPlayer : public Player {
    public:
    class RegionListener;
    // virtual void initializeComponents(Actor::InitializationMethod, VariantParameterList const&);
    // virtual void setPos(Vec3 const&);
    // virtual void move(Vec3 const&);
    // virtual void teleportTo(Vec3 const&, bool, int, int, ActorUniqueID const&);
    // virtual void normalTick();
    // virtual void startRiding(Actor&);
    // virtual void setSneaking(bool);
    // virtual bool isLocalPlayer() const;
    // virtual void actuallyHurt(int, ActorDamageSource const&, bool);
    // virtual void handleEntityEvent(ActorEvent, int);
    // virtual void setArmor(ArmorSlot, ItemStack const&);
    // virtual void setOffhandSlot(ItemStack const&);
    // virtual void handleInsidePortal(BlockPos const&);
    // virtual void changeDimension(AutomaticID<Dimension, int>, bool);
    // virtual void changeDimension(ChangeDimensionPacket const&);
    // virtual void* getControllingPlayer() const;
    // virtual void checkFallDamage(float, bool);
    // virtual void causeFallDamage(float);
    // virtual void playSynchronizedSound(LevelSoundEvent, Vec3 const&, Block const&, bool);
    // virtual void playSynchronizedSound(LevelSoundEvent, Vec3 const&, int, bool);
    // virtual void stopRiding(bool, bool, bool);
    // virtual void onEffectRemoved(MobEffectInstance&);
    // virtual void swing();
    // virtual void startSpinAttack();
    // virtual void stopSpinAttack();
    // virtual void die(ActorDamageSource const&);
    // virtual void* createMovementProxy();
    // virtual void _hurt(ActorDamageSource const&, int, bool, bool);
    // virtual void readAdditionalSaveData(CompoundTag const&, DataLoadHelper&);
    // virtual void addAdditionalSaveData(CompoundTag&);
    // virtual void _doAutoAttackOnTouch(Actor&);
    // virtual void setSprinting(bool);
    // virtual void travel(float, float, float);
    // virtual void applyFinalFriction(float, bool);
    // virtual void aiStep();
    // virtual void setItemSlot(EquipmentSlot, ItemStack const&);
    // virtual void jumpFromGround();
    // virtual void updateAi();
    // virtual bool _allowAscendingScaffolding() const;
    // virtual void prepareRegion(ChunkSource&);
    // virtual void destroyRegion();
    // virtual void suspendRegion();
    // virtual void _fireDimensionChanged();
    // virtual void tickWorld(Tick const&);
    // virtual void frameUpdate(FrameUpdateContextBase&);
    // virtual void* getTickingOffsets() const;
    // virtual void checkMovementStats(Vec3 const&);
    // virtual void* getCurrentStructureFeature() const;
    // virtual bool isAutoJumpEnabled() const;
    // virtual void respawn();
    // virtual void resetRot();
    // virtual void resetPos(bool);
    // virtual bool isInTrialMode();
    // virtual void openPortfolio();
    // virtual void openBook(int, bool, int, BlockActor*);
    // virtual void openTrading(ActorUniqueID const&, bool);
    // virtual void openChalkboard(ChalkboardBlockActor&, bool);
    // virtual void openNpcInteractScreen(Actor&);
    // virtual void openInventory();
    // virtual void displayClientMessage(std::__ndk1::string const&);
    // virtual void displayTextObjectMessage(TextObjectRoot const&);
    // virtual void displayWhisperMessage(std::__ndk1::string const&, std::__ndk1::string const&, std::__ndk1::string const&, std::__ndk1::string const&);
    // virtual void startSleepInBed(BlockPos const&);
    // virtual void stopSleepInBed(bool, bool);
    // virtual bool canStartSleepInBed();
    // virtual void openSign(BlockPos const&);
    // virtual void playEmote(std::__ndk1::string const&);
    // virtual bool isHostingPlayer() const;
    // virtual bool isLoading() const;
    // virtual bool stopLoading();
    // virtual void setPlayerGameType(GameType);
    // virtual void _crit(Actor&);
    // virtual void* getEventing() const;
    // virtual void* getUserId() const;
    // virtual void addExperience(int);
    // virtual void addLevels(int);
    // virtual void deleteContainerManager();
    // virtual bool isEntityRelevant(Actor const&);
    // virtual bool isTeacher() const;
    // virtual void* sendInventoryTransaction(InventoryTransaction const&) const;
    // virtual void sendComplexInventoryTransaction(std::__ndk1::unique_ptr<ComplexInventoryTransaction>) const;
    // virtual void sendNetworkPacket(Packet&) const;
    // virtual PlayerEventCoordinator* getPlayerEventCoordinator();
    // virtual MoveInputHandler& getMoveInputHandler();
    // virtual InputMode getInputMode();
    // virtual int getPlayMode() const;
    bool hasBossRegistered(ActorUniqueID) const;
    void* getItemStackNetManagerClient() const;
    void registerFramewiseActionOrStop();
    float getOPortalEffectTime() const;
    float getPreloadingProgress();
    void setOPortalEffectTime(float);
    NetworkChunkSubscriber* getNetworkChunkSubscriber();
    void setAutoJumpEnabled(bool);
    void stopPaddling(Side);
    void setTeacher();
    unsigned int getViewBlockRadius() const;
    void setEmotePlayedEndedEarly(bool);
    void _computeBowOverride(Vec3&);
    /*unsigned?*/ int getPickRange() const;
    void removeRegionListener(RegionListener*);
    void clearMovementState();
    void setPortalEffectTime(float);
    void chat(std::__ndk1::string const&);
    void setInventoryOptions(InventoryOptions const&);
    void* _getClientPlayerEventCoordinator();
    void localPlayerTurn(Vec2 const&);
    void* getLookBob() const;
    void _modifyDeltaByHMDPosition(Vec3&, float);
    bool isAbleToRespawn() const;
    void pickBlock(HitResult const&, bool);
    void* getItemStackNetManagerClient();
    float getPortalEffectTime() const;
    void* getOldLookBob() const;
    void frameUpdate(FrameUpdateContext&);
    void localPlayerRenderFrequencyMove(float);
    void _postJumpFrameOfReferenceAdjustCheck(bool);
    bool _shouldRotateWithCamera() const;
    void closeScreen();
    void setClientRespawnPotentialPosition(Vec3 const&);
    Vec3* getClientRespawnPotentialPosition();
    void setJumpRidingScale(float);
    void sendInput();
    NetworkChunkSubscriber* getNetworkChunkSubscriber() const;
    void displayItemActivation(ItemStack const&);
    void _RotationVec2Modulus(Vec2&);
    void sendPosition();
    void setPlayerGameTypeWithoutServerNotification(GameType);
    void _calculateFlight(float, float, float);
    void markUIAnimationComponentDirty();
    void* getLoadingState() const;
    ClientInstance* getClientInstance() const;
    void _applyTurnDelta(Vec2 const&);
    void requestChunkRadius(unsigned int);
    void updateAfterCamera(Camera const&);
    bool isFlying() const;
    void _fillChunksNeededForLoadOffsets();
    float getFieldOfViewModifier();
    void openCodeScreen();
    ItemStack* getActivatedItem() const;
    void handleArmorDamage(ArmorSlot, short);
    InventoryMenu* getInventoryMenu();
    void updateBeforeCamera(Camera const&, float);
    void initializeItemStackNetManager(bool);
    void resetLastHmdAngle();
    float getJumpRidingScale();
    void setLeavingLevel(bool);
    void sendEmotes();
    void startPaddling(Side);
    void setAllEmoteTelemetryData(std::__ndk1::string const&, int);
    InventoryOptions* getInventoryOptions() const;
    bool _hasLoadedEnoughChunksToView() const;
    void addRegionListener(RegionListener*);
    void fireEventPersonaEmotePlayed();
    void hurtTo(int);
    bool isLocalSplitscreenWith(ActorUniqueID const&) const;
    int getItemActivationOffsetX() const;
    int getItemActivationOffsetY() const;
    void setClientRespawnState(PlayerRespawnState const&);
    void* _getCrashDumpLogCategory();
    int getItemActivationTicks() const;
};


#endif //KEX_LOCALPLAYER_HPP