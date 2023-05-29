#include <hook.h>
#include <symbol.h>
#include <logger.h>

#include <innercore/id_conversion_map.h>

#include <commontypes.hpp>

#include "../../../utils/java_utils.hpp"
#include "tooltip.hpp"


std::unordered_map<long long, std::string> KEXItemsTooltipModule::tooltipCache;
std::unordered_map<int, bool> KEXItemsTooltipModule::isCallbackForced;
unsigned short KEXItemsTooltipModule::currentCalls = 0;
long long KEXItemsTooltipModule::lastTimestamp = 0ll;


void KEXItemsTooltipModule::append(int id, int damageValue, const ItemStackBase* stack, Level* level, stl::string& textRef) {
    if(lastTimestamp == 0ll) lastTimestamp = getTimeMilliseconds();
    long long current = getTimeMilliseconds();
    long long idDataLong = ((unsigned long long) id << 32) | (unsigned long long) damageValue;
    if(current < lastTimestamp + 1000ll) {
        lastTimestamp = current;
        currentCalls = 0;
    }
    if(!isCachePresent(idDataLong)) {
        JNIEnv* env = KEXJavaUtils::attach();
        jstring output = KEXJavaBridge::ItemsModule::appendFormattedHovertext((jlong) stack, (jlong) level, textRef.c_str());
        const char* cOutput = env->GetStringUTFChars(output, 0);
        tooltipCache.emplace(idDataLong, cOutput);
        env->ReleaseStringUTFChars(output, cOutput);
        env->DeleteLocalRef(output);
    } else {
        auto& cache = tooltipCache.at(idDataLong);
        unsigned short limit = isTooltipCallbackForced(id) ? 20 : 5;
        if(currentCalls < limit) {
            JNIEnv* env = KEXJavaUtils::attach();
            jstring output = KEXJavaBridge::ItemsModule::appendFormattedHovertext((jlong) stack, (jlong) level, textRef.c_str());
            const char* cOutput = env->GetStringUTFChars(output, 0);
            cache = cOutput;
            env->ReleaseStringUTFChars(output, cOutput);
            env->DeleteLocalRef(output);
            currentCalls++;
        }
    }
    textRef = tooltipCache.at(idDataLong).c_str();
}


void KEXItemsTooltipModule::initialize() {

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZNK4Item24appendFormattedHovertextERK13ItemStackBaseR5LevelRNSt6__ndk112basic_stringIcNS5_11char_traitsIcEENS5_9allocatorIcEEEEb"),
        LAMBDA((Item* item, const ItemStackBase& stack, Level& level, stl::string& text, bool b), {
            append(IdConversion::dynamicToStatic(stack.getId(), IdConversion::ITEM), stack.getAuxValue(), &stack, &level, text);
        }, ),
        HookManager::RETURN | HookManager::LISTENER
    );

}


extern "C" JNIEXPORT void JNICALL Java_vsdum_kex_modules_ItemsModule_nativeSetTooltipCallbackForced
(JNIEnv*, jclass, jint id) {
    if(KEXItemsTooltipModule::isCallbackForced.find(id) == KEXItemsTooltipModule::isCallbackForced.end()) {
        KEXItemsTooltipModule::isCallbackForced.emplace(id, true);
    }
}