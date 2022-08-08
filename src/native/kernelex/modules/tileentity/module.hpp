#include <unordered_map>

#include <mod.h>

#include <BlockActor.hpp>

#ifndef KEX_MODULES_TILEENTITY_MODULE_HPP
#define KEX_MODULES_TILEENTITY_MODULE_HPP


class KEXTileEntityModule : public Module {
    public:
    class TileEntity : public BlockActor {
        public:
        virtual void load(Level&, const CompoundTag&, DataLoadHelper&);
        virtual bool save(CompoundTag&) const;
        virtual void tick(BlockSource&);
        virtual bool isFinished();
        virtual void onChanged(BlockSource&);
        virtual bool isMovable(BlockSource&);
        virtual void onPlace(BlockSource&);
        virtual void onMove();
        virtual void onRemoved(BlockSource&);
        virtual void triggerEvent(int, int);
        virtual void onNeighborChanged(BlockSource&, const BlockPos&);
        virtual float getShadowRadius(BlockSource&) const;
        virtual void getDebugText(stl::vector<stl::string>&, const BlockPos&);
        virtual const stl::string& getCustomName() const;
        virtual stl::string getName() const;
        virtual void setCustomName(const stl::string&);
        virtual void onChunkLoaded(LevelChunk&);
        virtual void onChunkUnloaded(LevelChunk&);
        TileEntity(int type, const BlockPos& pos);
    };
    static std::unordered_map<int, int> customTileEntityBlocks;
    KEXTileEntityModule(Module* parent): Module(parent, "kex.tileentity") {}
    virtual void initialize();
};


#endif //KEX_MODULES_TILEENTITY_MODULE_HPP