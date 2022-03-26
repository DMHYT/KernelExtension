#include <Player.hpp>

#ifndef KEX_SERVERPLAYER_HPP
#define KEX_SERVERPLAYER_HPP


class ServerPlayer : public Player {
    public:
    // virtual void initializeComponents(Actor::InitializationMethod, VariantParameterList const&);
    // virtual void _serverInitItemStackIds();
    // virtual void normalTick();
    // virtual bool isValidTarget(Actor*) const;
    // virtual void handleEntityEvent(ActorEvent, int);
    // virtual void setArmor(ArmorSlot, ItemStack const&);
    // virtual void setOffhandSlot(ItemStack const&);
    // virtual void load(CompoundTag const&, DataLoadHelper&);
    // virtual bool canChangeDimensions() const;
    // virtual void changeDimension(AutomaticID<Dimension, int>, bool);
    // virtual void* getControllingPlayer() const;
    // virtual void checkFallDamage(float, bool);
    // virtual void handleFallDistanceOnServer(float, bool);
    // virtual void onEffectAdded(MobEffectInstance&);
    // virtual void onEffectUpdated(MobEffectInstance const&);
    // virtual void onEffectRemoved(MobEffectInstance&);
    // virtual void die(ActorDamageSource const&);
    // virtual void knockback(Actor*, int, float, float, float, float, float);
    // virtual void aiStep();
    // virtual void hurtArmor(ActorDamageSource const&, int);
    // virtual void setDamagedArmor(ArmorSlot, ItemStack const&);
    // virtual void sendArmorDamage(std::__ndk1::bitset<4u> const&);
    // virtual void sendArmor(std::__ndk1::bitset<4u> const&);
    // virtual void clearVanishEnchantedItemsOnDeath();
    // virtual void sendInventory(bool);
    // virtual void prepareRegion(ChunkSource&);
    // virtual void destroyRegion();
    // virtual void suspendRegion();
    // virtual void resendAllChunks();
    // virtual void changeDimensionWithCredits(AutomaticID<Dimension, int>);
    // virtual void tickWorld(Tick const&);
    // virtual void frameUpdate(FrameUpdateContextBase&);
    // virtual void checkMovementStats(Vec3 const&);
    // virtual void setPermissions(CommandPermissionLevel);
    // virtual void openPortfolio();
    // virtual void openTrading(ActorUniqueID const&, bool);
    // virtual void openNpcInteractScreen(Actor&);
    // virtual void openInventory();
    // virtual void displayTextObjectMessage(TextObjectRoot const&);
    // virtual void displayTextObjectWhisperMessage(ResolvedTextObject const&, std::__ndk1::string const&, std::__ndk1::string const&);
    // virtual void displayWhisperMessage(std::__ndk1::string const&, std::__ndk1::string const&, std::__ndk1::string const&, std::__ndk1::string const&);
    // virtual void stopSleepInBed(bool, bool);
    // virtual bool isHostingPlayer() const;
    // virtual bool isLoading() const;
    // virtual bool isPlayerInitialized() const;
    // virtual void setPlayerGameType(GameType);
    // virtual bool isEntityRelevant(Actor const&);
    // virtual bool isTeacher() const;
    // virtual void onSuspension();
    // virtual void onLinkedSlotsChanged();
    // virtual void* sendInventoryTransaction(InventoryTransaction const&) const;
    // virtual void* sendComplexInventoryTransaction(std::__ndk1::unique_ptr<ComplexInventoryTransaction>) const;
    // virtual void* sendNetworkPacket(Packet&) const;
    // virtual PlayerEventCoordinator* getPlayerEventCoordinator() const;
    // virtual MoveInputHandler* getMoveInputHandler();
    // virtual InputMode getInputMode();
    // virtual int getPlayMode();
    // virtual void reportMovementTelemetry(MovementEventType);
    void handleActorPickRequestOnServer(Actor const&, bool);
    void* getItemStackNetManagerServer();
    InventoryMenu* getInventoryMenu();
    void _updateNearbyActors();
    void _nextContainerCounter();
    void disconnect();
    void setLocalPlayerAsInitialized();
    int _getViewDistanceDeterminismBufferRadius() const;
    int _getReadOnlyChunkCount();
    void* findClientChunkRadius(unsigned int) const;
    void updateChunkPublisherView(Vec3 const&, float);
    void postLoad(bool);
    void checkCheating(Vec3 const&);
    void sendMobEffectPackets();
    ServerMoveInputHandler* getServerMoveInputHandler();
    void setClientChunkRadius(unsigned int);
    void initContainerManager();
    void setPacketObserver(PacketObserver*);
    void _scanForNearbyActors();
    ServerPlayerEventCoordinator* _getServerPlayerEventCoordinator();
    void triggerRespawnFromCompletingTheEnd();
    void recoverR5LostInventoryAndXP();
    void selectItem(ItemStack const&);
    void setPlayMode(ClientPlayMode const&);
    void* getItemStackNetManagerServer() const;
    void initiateContainerClose();
    void doDeleteContainerManager(bool);
    void _removeNearbyEntities();
    void setPlayerInput(float, float, bool, bool);
    void openUnmanagedContainer();
    void setTeacher();
    void setLostDataTag(std::__ndk1::unique_ptr<CompoundTag>);
    void setInputMode(InputMode const&);
};


#endif //KEX_SERVERPLAYER_HPP