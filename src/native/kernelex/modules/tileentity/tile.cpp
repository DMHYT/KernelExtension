#include <ActorUniqueID.hpp>

#include "../../utils/java_utils.hpp"
#include "module.hpp"


KEXTileEntityModule::TileEntity::TileEntity(int type, const BlockPos& pos, int dimension)
: BlockActor((BlockActorType) type, pos, "") {
    KEXJavaBridge::TileEntityModule::construct((jlong) this, dimension);
}

void KEXTileEntityModule::TileEntity::load(Level& level, const CompoundTag& tag, DataLoadHelper& helper) {
    BlockActor::load(level, tag, helper);
    KEXJavaBridge::TileEntityModule::load((jlong) this, (jlong) &tag);
}

bool KEXTileEntityModule::TileEntity::save(CompoundTag& tag) const {
    if(!BlockActor::save(tag)) return false;
    KEXJavaBridge::TileEntityModule::save((jlong) this, (jlong) &tag);
}

void KEXTileEntityModule::TileEntity::tick(BlockSource& world) {
    BlockActor::tick(world);
    KEXJavaBridge::TileEntityModule::tick((jlong) this);
}

bool KEXTileEntityModule::TileEntity::isFinished() {
    return KEXJavaBridge::TileEntityModule::isFinished((jlong) this);
}

void KEXTileEntityModule::TileEntity::onChanged(BlockSource& world) {
    KEXJavaBridge::TileEntityModule::onChanged((jlong) this);
}

bool KEXTileEntityModule::TileEntity::isMovable(BlockSource& world) {
    return KEXJavaBridge::TileEntityModule::isMovable((jlong) this);
}

void KEXTileEntityModule::TileEntity::onPlace(BlockSource& world) {
    KEXJavaBridge::TileEntityModule::onPlace((jlong) this);
}

void KEXTileEntityModule::TileEntity::onMove() {
    KEXJavaBridge::TileEntityModule::onMove((jlong) this);
}

void KEXTileEntityModule::TileEntity::onRemoved(BlockSource& world) {
    KEXJavaBridge::TileEntityModule::onRemoved((jlong) this);
}

void KEXTileEntityModule::TileEntity::triggerEvent(int id, int type) {
    BlockActor::triggerEvent(id, type);
    KEXJavaBridge::TileEntityModule::triggerEvent((jlong) this, id, type);
}

void KEXTileEntityModule::TileEntity::onNeighborChanged(BlockSource& world, const BlockPos& changed) {
    KEXJavaBridge::TileEntityModule::onNeighborChanged((jlong) this, changed.x, changed.y, changed.z);
}

const stl::string& KEXTileEntityModule::TileEntity::getCustomName() const {
    JNIEnv* env = KEXJavaUtils::attach();
    jstring jResult = KEXJavaBridge::TileEntityModule::getCustomName((jlong) this);
    if(jResult != nullptr) {
        const char* cResult = env->GetStringUTFChars(jResult, 0);
        *(stl::string*) ((char*) this + 80) = cResult;
        env->ReleaseStringUTFChars(jResult, cResult);
        env->DeleteLocalRef(jResult);
    } else {
        *(stl::string*) ((char*) this + 80) = "";
    }
    return customName;
}

stl::string KEXTileEntityModule::TileEntity::getName() const {
    JNIEnv* env = KEXJavaUtils::attach();
    jstring jResult = KEXJavaBridge::TileEntityModule::getName((jlong) this);
    if(jResult == nullptr) return "";
    const char* cResult = env->GetStringUTFChars(jResult, 0);
    stl::string result(cResult);
    env->ReleaseStringUTFChars(jResult, cResult);
    env->DeleteLocalRef(jResult);
    return result;
}

void KEXTileEntityModule::TileEntity::setCustomName(const stl::string& customName) {
    KEXJavaBridge::TileEntityModule::setCustomName((jlong) this, customName.c_str());
}

void KEXTileEntityModule::TileEntity::onChunkLoaded(LevelChunk& levelChunk) {
    KEXJavaBridge::TileEntityModule::onChunkLoaded((jlong) this);
}

void KEXTileEntityModule::TileEntity::onChunkUnloaded(LevelChunk& levelChunk) {
    KEXJavaBridge::TileEntityModule::onChunkUnloaded((jlong) this);
}

bool KEXTileEntityModule::TileEntity::onUse(Player& player, unsigned char side, const Vec3& vec) const {
    return KEXJavaBridge::TileEntityModule::onUse((jlong) this, player.getUniqueID()->id, (char) side, vec.x, vec.y, vec.z);
}