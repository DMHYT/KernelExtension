#include <stl/string>
#include <stl/memory>
#include <stl.h>

#include <static_symbol.h>

#ifndef KEX_BIOME_HPP
#define KEX_BIOME_HPP


#ifndef KEX_LEVELCHUNK_HPP
    class LevelChunk;
#endif


class Biome {
    public:
    void** vtable; // 4
    stl::string nameID; // 16
    char filler1[80]; // 96
    int id; // 100
    char filler2[60]; // 160
    float getDefaultBiomeTemperature() const;
    float getDownfall() const;
    bool isHumid() const;
    bool isSnowCovered() const;
};

class VanillaBiomes {
    public:
    static Biome* mSky;
};

class FixedBiomeSource {
    public:
    char filler[8];
    FixedBiomeSource(const Biome&);
};

class FlatWorldGenerator {
    public:
    char filler[68]; // 68
    const Biome* biome; // 72
};

class OverworldGenerator {
    public:
    class OverridableBiomeSourceHelper {
        public:
        void*** cachedBiomeSource; // 4
        void** fixedBiomeSource; // 8
        void* biomeSource; // 12
        OverridableBiomeSourceHelper(const OverworldGenerator&);
        inline ~OverridableBiomeSourceHelper() {
            STATIC_SYMBOL(destruct, "_ZN18OverworldGenerator28OverridableBiomeSourceHelperD2Ev", (OverridableBiomeSourceHelper*), void)
            destruct(this);
        }
    };
};

template<typename T>
class Layer {
    public:
    char filler[24];
};

typedef stl::shared_ptr<Layer<Biome*> const> LayerPtr;

class NetherGenerator {
    public:
    char filler[476]; // 476
    LayerPtr layer1; // 484
    LayerPtr layer2; // 492
};

class VanillaOverworldBiomeSource {
    public:
    char filler[20];
    VanillaOverworldBiomeSource(LayerPtr, LayerPtr);
    inline ~VanillaOverworldBiomeSource() {
        STATIC_SYMBOL(destruct, "_ZN27VanillaOverworldBiomeSourceD2Ev", (VanillaOverworldBiomeSource*), void)
        destruct(this);
    }
};

class BiomeRegistry {
    public:
    bool isRegistrationFinished() const;
    void forEachBiome(stl::function<void(Biome&)>) const;
};


#endif //KEX_BIOME_HPP