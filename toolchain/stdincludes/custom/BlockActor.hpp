#include <stl/map>
#include <stl.h>

#include <enums.hpp>

#include <BlockSource.hpp>
#include <Level.hpp>
#include <LevelChunk.hpp>
#include <CompoundTag.hpp>
#include <Player.hpp>

#ifndef KEX_BLOCKACTOR_HPP
#define KEX_BLOCKACTOR_HPP


class BlockActorDataPacket {
    public:
    char filler[24]; // 24
    BlockPos pos; // 36
    CompoundTag tag; // 96
    BlockActorDataPacket(const BlockPos&, CompoundTag);
};
#ifndef KEX_CONTAINER_HPP
    class Container;
#endif
class DataLoadHelper;
class PistonBlockActor;
class UIProfanityContext;

class BlockActor {
    public:
    char filler1[68]; // 72
    BlockActorType type; // 76
    char filler2[4]; // 80
    stl::string customName; // 92
    char filler3[164]; // 256
    /*0*/ virtual ~BlockActor();
    /*1*/ virtual void load(Level&, const CompoundTag&, DataLoadHelper&);
    /*2*/ virtual bool save(CompoundTag&) const;
    /*3*/ virtual bool saveItemInstanceData(CompoundTag&);
    /*4*/ virtual void saveBlockData(CompoundTag&, BlockSource&) const;
    /*5*/ virtual void loadBlockData(const CompoundTag&, BlockSource&, DataLoadHelper&);
    /*6*/ virtual void onCustomTagLoadDone(BlockSource&);
    /*7*/ virtual void tick(BlockSource&);
    /*8*/ virtual bool isFinished();
    /*9*/ virtual void onChanged(BlockSource&);
    /*10*/ virtual bool isMovable(BlockSource&);
    /*11*/ virtual bool isCustomNameSaved();
    /*12*/ virtual void onPlace(BlockSource&);
    /*13*/ virtual void onMove();
    /*14*/ virtual void onRemoved(BlockSource&);
    /*15*/ virtual void triggerEvent(int, int);
    /*16*/ virtual void clearCache();
    /*17*/ virtual void onNeighborChanged(BlockSource&, const BlockPos&);
    /*18*/ virtual float getShadowRadius(BlockSource&) const;
    /*19*/ virtual bool hasAlphaLayer() const;
    /*20*/ virtual BlockActor* getCrackEntity(BlockSource&, const BlockPos&);
    /*21*/ virtual void getDebugText(stl::vector<stl::string>&, const BlockPos&);
    /*22*/ virtual const stl::string& getCustomName() const;
    /*23*/ virtual const stl::string& getFilteredCustomName(const UIProfanityContext&);
    /*24*/ virtual stl::string getName() const;
    /*25*/ virtual void setCustomName(const stl::string&);
    /*26*/ virtual stl::string getImmersiveReaderText(BlockSource&);
    /*27*/ virtual int getRepairCost() const;
    /*28*/ virtual PistonBlockActor* getOwningPiston(BlockSource&);
    /*29*/ virtual Container* getContainer();
    /*30*/ virtual Container* getContainer() const;
    /*31*/ virtual float getDeletionDelayTimeSeconds() const;
    /*32*/ virtual void onChunkLoaded(LevelChunk&);
    /*33*/ virtual void onChunkUnloaded(LevelChunk&);
    /*34*/ virtual stl::unique_ptr<BlockActorDataPacket> _getUpdatePacket(BlockSource&);
    /*35*/ virtual void _onUpdatePacket(const CompoundTag&, BlockSource&);
    /*36*/ virtual bool _playerCanUpdate(const Player&) const;
    BlockActor(BlockActorType, const BlockPos&, const stl::string&);
    int getType() const;
    Block* getBlock() const;
    bool isType(BlockActorType) const;
    void shutdown();
    void setCustomNameSaved(bool);
    void stopDestroy();
    void onUpdatePacket(const CompoundTag&, BlockSource&, const Player*);
    void setBB(AABB);
    bool canRenderCustomName() const;
    float distanceToSqr(const Vec3&);
    void _resetAABB();
    bool isClientSideOnly() const;
    void setMovable(bool);
    bool isInWorld() const;
    const BlockPos& getPosition() const;
    const AABB& getAABB() const;
    stl::string getDisplayName() const;
    void assignBlockIfNotAssigned(BlockSource&);
    stl::unique_ptr<BlockActorDataPacket> getServerUpdatePacket(BlockSource&);
    stl::unique_ptr<BlockActorDataPacket> getClientUpdatePacket(BlockSource&);
    void setChanged();
    void moveTo(BlockPos const&);
    void setClientSideOnly(bool);
    static bool isType(BlockActor&, BlockActorType);
    static stl::shared_ptr<BlockActor> loadStatic(Level&, const CompoundTag&, DataLoadHelper&);
    static stl::map<int, stl::string> mClassIdMap;
    static stl::map<stl::string, int> mIdClassMap;
};


#endif //KEX_BLOCKACTOR_HPP