#include <logger.h>
#include <hook.h>
#include <symbol.h>

#include <innercore/biomes.h>

#include "../utils/java_utils.hpp"
#include "biomes.hpp"


void KEXBiomesModule::onBiomesInitialized(const BiomeRegistry& registry) {
    int biomesCount = 0;
    registry.forEachBiome(stl::function<void(Biome&)>([&biomesCount] (Biome& biome) { ++biomesCount; }));
    Logger::debug("KEX-BiomesModule", "Verified %d biomes, caching...", biomesCount);
    JNIEnv* env = KEXJavaUtils::attach();
    jintArray id = env->NewIntArray(biomesCount);
    jobjectArray name = env->NewObjectArray(biomesCount, env->FindClass("java/lang/String"), NULL);
    jfloatArray temperature = env->NewFloatArray(biomesCount);
    jfloatArray downfall = env->NewFloatArray(biomesCount);
    jbooleanArray humid = env->NewBooleanArray(biomesCount);
    jbooleanArray snow = env->NewBooleanArray(biomesCount);
    jint idFill[biomesCount];
    jfloat temperatureFill[biomesCount];
    jfloat downfallFill[biomesCount];
    jboolean humidFill[biomesCount];
    jboolean snowFill[biomesCount];
    int i = 0;
    registry.forEachBiome(stl::function<void(Biome&)>([env, name, &idFill, &temperatureFill, &downfallFill, &humidFill, &snowFill, &i] (Biome& biome) {
        idFill[i] = CustomBiomeRegistry::toVirtualId(biome.id);
        env->SetObjectArrayElement(name, i, env->NewStringUTF(biome.nameID.c_str()));
        temperatureFill[i] = biome.getDefaultBiomeTemperature();
        downfallFill[i] = biome.getDownfall();
        humidFill[i] = biome.isHumid();
        snowFill[i] = biome.isSnowCovered();
        ++i;
    }));
    env->SetIntArrayRegion(id, 0, biomesCount, idFill);
    env->SetFloatArrayRegion(temperature, 0, biomesCount, temperatureFill);
    env->SetFloatArrayRegion(downfall, 0, biomesCount, downfallFill);
    env->SetBooleanArrayRegion(humid, 0, biomesCount, humidFill);
    env->SetBooleanArrayRegion(snow, 0, biomesCount, snowFill);
    KEXJavaBridge::BiomesModule::cacheBiomeInterfaces(id, name, temperature, downfall, humid, snow);
    env->DeleteLocalRef(id);
    env->DeleteLocalRef(name);
    env->DeleteLocalRef(temperature);
    env->DeleteLocalRef(downfall);
    env->DeleteLocalRef(humid);
    env->DeleteLocalRef(snow);
}


void KEXBiomesModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN13BiomeRegistry19initClientFromPacksER19ResourcePackManagerN3gsl8not_nullIN7Bedrock15NonOwnerPointerI21FogDefinitionRegistryEEEENS3_INS5_I10FogManagerEEEE"),
        LAMBDA((BiomeRegistry* registry), {
            onBiomesInitialized(*registry);
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

}