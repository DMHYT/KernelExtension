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
#ifndef KEX_LEVEL_HPP
    class Level;
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
    inline PendingArea(const PendingArea& other) {
        STATIC_SYMBOL(constructCopyC2, "_ZN11PendingAreaC2ERKS_", (PendingArea*, const PendingArea*), void);
        constructCopyC2(this, &other);
    }
    PendingArea& operator=(PendingArea&&);
    static inline PendingArea* constructArea(const stl::string& name, const Bounds& bounds, bool circle) {
        STATIC_SYMBOL(generateUUID, "_ZN6Crypto6Random12generateUUIDEv", (), mce::UUID);
        STATIC_SYMBOL(constructArea, "_ZN11PendingAreaC2EN3mce4UUIDERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERK6Boundsb", (PendingArea*, const stl::string*, mce::UUID, const stl::string*, const Bounds*, bool), void);
        auto uuid = generateUUID();
        PendingArea* result = (PendingArea*) operator new(96);
        constructArea(result, &name, uuid, &name, &bounds, circle);
        return result;
    }
};

class ITickingArea;
class TickingAreaDescription { public: char filler[44]; };

class TickingAreaListBase {
    public:
    void add(stl::unique_ptr<ITickingArea>);
    bool hasTickingAreaNamed(const stl::string&) const;
    stl::vector<stl::shared_ptr<ITickingArea>> findAreasNamed(const stl::string&) const;
    stl::vector<stl::shared_ptr<ITickingArea>> findAreasContaining(const BlockPos&);
    stl::vector<TickingAreaDescription> removeAreas(const stl::vector<stl::shared_ptr<ITickingArea>>&);
    stl::vector<TickingAreaDescription> removeAllAreas();
};

class TickingAreaList : public TickingAreaListBase { public: };

class TickingAreasManager {
    public:
    TickingAreaAddResult addArea(Dimension&, const stl::string&, const BlockPos&, const BlockPos&);
    TickingAreaAddResult addArea(Dimension&, const stl::string&, const BlockPos&, int);
    void removePendingAreaByPosition(Dimension&, const BlockPos&);
    void removePendingAreaByName(Dimension&, const stl::string&);
    unsigned int countPendingAreas(const Dimension&) const;
    unsigned int countStandaloneTickingAreas() const;
    void removeAllPendingAreas(Dimension&);
    bool hasActiveAreas() const;
    void update(Level&);
    bool _hasPendingTickingAreaNamed(const stl::string&, const stl::vector<PendingArea>&) const;
    stl::string _findUsableDefaultName(const TickingAreaList&, const stl::vector<PendingArea>&) const;
    void _savePendingArea(LevelStorage&, AutomaticID<Dimension, int>, const PendingArea&);
    inline stl::vector<PendingArea>& getPendingAreasForDimension(AutomaticID<Dimension, int> dimensionId) const {
        STATIC_SYMBOL(getAreasVector, "_ZNSt6__ndk113unordered_mapI11AutomaticIDI9DimensioniENS_6vectorI11PendingAreaNS_9allocatorIS5_EEEENS_4hashIS3_EENS_8equal_toIS3_EENS6_INS_4pairIKS3_S8_EEEEEixEOS3_", (void*, const AutomaticID<Dimension, int>&), stl::vector<PendingArea>&);
        auto& areasVector = getAreasVector( (void*) ((char*) this + 4), dimensionId );
        return areasVector;
    }
};


#endif //KEX_TICKINGAREASMANAGER_HPP