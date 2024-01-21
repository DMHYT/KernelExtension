#include <commontypes.hpp>

#ifndef KEX_DIMENSION_HPP
#define KEX_DIMENSION_HPP


#ifndef KEX_LEVEL_HPP
    class Level;
#endif
#ifndef KEX_TICKINGAREASMANAGER_HPP
    class TickingAreaList;
#endif

class Dimension {
    public:
    TickingAreaList* getTickingAreas();
    TickingAreaList* getTickingAreasConst() const;
    AutomaticID<Dimension, int> getDimensionId() const;
    Level* getLevel() const;
    void* getWorldGenerator() const;
};


#endif //KEX_DIMENSION_HPP