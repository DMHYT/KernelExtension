#include <mod.h>

#include <Dimension.hpp>
#include <TickingAreasManager.hpp>

#ifndef KEX_MODULES_CHUNKS_HPP
#define KEX_MODULES_CHUNKS_HPP


class KEXChunksModule : public Module {
    public:
    static TickingAreaAddResult addArea(TickingAreasManager*, Dimension&, const stl::string&, const Bounds&, bool);
    KEXChunksModule(Module* parent): Module(parent, "kex.chunks") {}
    virtual void initialize();
};


#endif //KEX_MODULES_CHUNKS_HPP