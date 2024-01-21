#include <mod.h>

#include <Biome.hpp>

#ifndef KEX_MODULES_BIOMES_HPP
#define KEX_MODULES_BIOMES_HPP


class KEXBiomesModule : public Module {
    public:
    static void onBiomesInitialized(const BiomeRegistry& registry);
    KEXBiomesModule(Module* parent): Module(parent, "kex.biomes") {}
    virtual void initialize();
};


#endif //KEX_MODULES_BIOMES_HPP