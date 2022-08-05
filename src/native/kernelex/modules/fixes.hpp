#include <string>
#include <unordered_map>

#include <mod.h>

#ifndef KEX_MODULES_FIXES_HPP
#define KEX_MODULES_FIXES_HPP


class KEXFixesModule : public Module {
    public:
    static std::unordered_map<std::string, unsigned int> blockSoundTypes;
    static std::unordered_map<std::string, unsigned int> levelSoundEventNameToType;
    static std::unordered_map<unsigned int, std::string> levelSoundEventTypeToName;
    static unsigned int nextBlockSoundType;
    static unsigned int nextLevelSoundEventType;
    KEXFixesModule(Module* parent): Module(parent, "kex.fixes") {}
    virtual void initialize();
};


#endif //KEX_MODULES_FIXES_HPP