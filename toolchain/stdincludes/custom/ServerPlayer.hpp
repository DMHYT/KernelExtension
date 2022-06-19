#include <Player.hpp>

#ifndef KEX_SERVERPLAYER_HPP
#define KEX_SERVERPLAYER_HPP


class ServerPlayer : public Player {
    public:
    // virtual void initializeComponents(Actor::InitializationMethod, const VariantParameterList&);
    // virtual void _serverInitItemStackIds();
    // virtual void normalTick();
    // virtual bool isValidTarget(Actor*) const;
    // virtual void handleEntityEvent(ActorEvent, int);
    // virtual void setArmor(ArmorSlot, const ItemStack&);
    // virtual void setOffhandSlot(const ItemStack&);
    // virtual void load(const CompoundTag&, DataLoadHelper&);
    // virtual bool canChangeDimensions() const;
    // virtual void changeDimension(AutomaticID<Dimension, int>, bool);
    // virtual void* getControllingPlayer() const;
    // virtual void checkFallDamage(float, bool);
    // virtual void handleFallDistanceOnServer(float, bool);
    // virtual void onEffectAdded(MobEffectInstance&);
    // virtual void onEffectUpdated(const MobEffectInstance&);
    // virtual void onEffectRemoved(MobEffectInstance&);
    // virtual void die(const ActorDamageSource&);
    // virtual void knockback(Actor*, int, float, float, float, float, float);
    // virtual void aiStep();
    // virtual void hurtArmor(const ActorDamageSource&, int);
    // virtual void setDamagedArmor(ArmorSlot, const ItemStack&);
    // virtual void sendArmorDamage(stl::bitset<4u> const&);
    // virtual void sendArmor(stl::bitset<4u> const&);
    // virtual void clearVanishEnchantedItemsOnDeath();
    // virtual void sendInventory(bool);
    // virtual void prepareRegion(ChunkSource&);
    // virtual void destroyRegion();
    // virtual void suspendRegion();
    // virtual void resendAllChunks();
    // virtual void changeDimensionWithCredits(AutomaticID<Dimension, int>);
    // virtual void tickWorld(const Tick&);
    // virtual void frameUpdate(FrameUpdateContextBase&);
    // virtual void checkMovementStats(const Vec3&);
    // virtual void setPermissions(CommandPermissionLevel);
    // virtual void openPortfolio();
    // virtual void openTrading(const ActorUniqueID&, bool);
    // virtual void openNpcInteractScreen(Actor&);
    // virtual void openInventory();
    // virtual void displayTextObjectMessage(const TextObjectRoot&);
    // virtual void displayTextObjectWhisperMessage(const ResolvedTextObject&, const stl::string&, const stl::string&);
    // virtual void displayWhisperMessage(const stl::string&, const stl::string&, const stl::string&, const stl::string&);
    // virtual void stopSleepInBed(bool, bool);
    // virtual bool isHostingPlayer() const;
    // virtual bool isLoading() const;
    // virtual bool isPlayerInitialized() const;
    // virtual void setPlayerGameType(GameType);
    // virtual bool isEntityRelevant(const Actor&);
    // virtual bool isTeacher() const;
    // virtual void onSuspension();
    // virtual void onLinkedSlotsChanged();
    // virtual void* sendInventoryTransaction(const InventoryTransaction&) const;
    // virtual void* sendComplexInventoryTransaction(stl::unique_ptr<ComplexInventoryTransaction>) const;
    // virtual void* sendNetworkPacket(Packet&) const;
    // virtual PlayerEventCoordinator* getPlayerEventCoordinator() const;
    // virtual MoveInputHandler* getMoveInputHandler();
    // virtual InputMode getInputMode();
    // virtual int getPlayMode();
    // virtual void reportMovementTelemetry(MovementEventType);
    void handleActorPickRequestOnServer(const Actor&, bool);
    void* getItemStackNetManagerServer();
    InventoryMenu* getInventoryMenu();
    void _updateNearbyActors();
    void _nextContainerCounter();
    void disconnect();
    void setLocalPlayerAsInitialized();
    int _getViewDistanceDeterminismBufferRadius() const;
    int _getReadOnlyChunkCount();
    void* findClientChunkRadius(unsigned int) const;
    void updateChunkPublisherView(const Vec3&, float);
    void postLoad(bool);
    void checkCheating(const Vec3&);
    void sendMobEffectPackets();
    ServerMoveInputHandler* getServerMoveInputHandler();
    void setClientChunkRadius(unsigned int);
    void initContainerManager();
    void setPacketObserver(PacketObserver*);
    void _scanForNearbyActors();
    ServerPlayerEventCoordinator* _getServerPlayerEventCoordinator();
    void triggerRespawnFromCompletingTheEnd();
    void recoverR5LostInventoryAndXP();
    void selectItem(const ItemStack&);
    void setPlayMode(const ClientPlayMode&);
    void* getItemStackNetManagerServer() const;
    void initiateContainerClose();
    void doDeleteContainerManager(bool);
    void _removeNearbyEntities();
    void setPlayerInput(float, float, bool, bool);
    void openUnmanagedContainer();
    void setTeacher();
    void setLostDataTag(stl::unique_ptr<CompoundTag>);
    void setInputMode(const InputMode&);
};


#endif //KEX_SERVERPLAYER_HPP