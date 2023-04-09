#include "module.hpp"


std::unordered_map<int, unsigned long long> KEXBlocksModule::LightEmission::lightData;


unsigned char KEXBlocksModule::LightEmission::get(int id, int data) {
    if(lightData.find(id) == lightData.end()) return 0;
    return (unsigned char) ( (lightData.at(id) >> data * 4) & 0xf );
}

void KEXBlocksModule::LightEmission::set(int id, int data, unsigned char lightLevel) {
    lightLevel = lightLevel < 0 ? 0 : lightLevel > 15 ? 15 : lightLevel;
    if(lightData.find(id) == lightData.end()) lightData.emplace(id, 0ll);
    auto& packed = lightData.at(id);
    packed &= ~((unsigned long long) 0xf << data * 4);
    packed |= ((unsigned long long) lightLevel << data * 4);
}