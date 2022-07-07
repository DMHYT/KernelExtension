#include <stl/string>
#include <stl/vector>
#include <stl.h>

#include <static_symbol.h>

#include <commontypes.hpp>

#ifndef KEX_TICKINGAREASMANAGER_HPP
#define KEX_TICKINGAREASMANAGER_HPP


#ifndef KEX_ACTORUNIQUEID_HPP
    class ActorUniqueID;
#endif
#ifndef KEX_BLOCKPOS_HPP
    class BlockPos;
#endif
#ifndef KEX_BOUNDS_HPP
    class Bounds;
#endif
#ifndef KEX_DIMENSION_HPP
    class Dimension;
#endif
class LevelStorage;
#ifndef KEX_MCEUUID_HPP
    namespace mce {
        class UUID {
            public: char filler[16];
        };
    }
#endif

enum TickingAreaAddResult {
    MORE_THAN_100_CHUNKS = 0,
    MORE_THAN_10_AREAS = 1,
    NAME_ALREADY_EXISTS = 2,
    SUCCESS = 3
};

class PendingArea {
    public:
    char filler[96];
    PendingArea(mce::UUID, ActorUniqueID, const Bounds&, float);
    PendingArea(mce::UUID, ActorUniqueID, const Bounds&);
    PendingArea(mce::UUID, const stl::string&, const Bounds&, bool);
    inline PendingArea(const PendingArea& other) {
        STATIC_SYMBOL(constructCopyC2, "_ZN11PendingAreaC2ERKS_", (PendingArea*, const PendingArea*), void);
        constructCopyC2(this, &other);
    }
    PendingArea& operator=(PendingArea&&);
    static PendingArea createTickingArea(mce::UUID, const stl::string&, const Bounds&, bool);
};

class TickingAreaListBase {
    public:
    bool hasTickingAreaNamed(const stl::string&) const;
};

class TickingAreaList : public TickingAreaListBase { public: };

class TickingAreasManager {
    public:
    void addArea(Dimension&, const stl::string&, const BlockPos&, const BlockPos&);
    void addArea(Dimension&, const stl::string&, const BlockPos&, int);
    void removePendingAreaByPosition(Dimension&, const BlockPos&);
    void removePendingAreaByName(Dimension&, const stl::string&);
    unsigned int countPendingAreas(const Dimension&) const;
    unsigned int countStandalonePendingAreas() const;
    void removeAllPendingAreas(Dimension&);
    bool hasActiveAreas() const;
    bool _hasPendingTickingAreaNamed(const stl::string&, const stl::vector<PendingArea>&) const;
    stl::string _findUsableDefaultName(const TickingAreaList&, const stl::vector<PendingArea>&) const;
    void _savePendingArea(LevelStorage&, AutomaticID<Dimension, int>, const PendingArea&);
};


#endif //KEX_TICKINGAREASMANAGER_HPP