#include <ActorUniqueID.hpp>
#include <Dimension.hpp>

#include "../../utils/java_utils.hpp"
#include "module.hpp"


KEXTileEntityModule::TileEntity::TileEntity(int type, const BlockPos& pos)
: BlockActor((BlockActorType) type, pos, "") {
    KEXJavaBridge::TileEntityEvents::construct((jlong) this);
}

void KEXTileEntityModule::TileEntity::load(Level& level, const CompoundTag& tag, DataLoadHelper& helper) {
    BlockActor::load(level, tag, helper);
    KEXJavaBridge::TileEntityEvents::load((jlong) this, (jlong) &tag);
}

bool KEXTileEntityModule::TileEntity::save(CompoundTag& tag) const {
    if(!BlockActor::save(tag)) return false;
    KEXJavaBridge::TileEntityEvents::save((jlong) this, (jlong) &tag);
}

void KEXTileEntityModule::TileEntity::tick(BlockSource& world) {
    if(this->life == 0) {
        KEXJavaBridge::TileEntityEvents::reportTileSideAndDimension((jlong) this, world.getLevel()->isClientSide(), world.getDimension()->getDimensionId().id);
    }
    BlockActor::tick(world);
    KEXJavaBridge::TileEntityEvents::tick((jlong) this);
}

bool KEXTileEntityModule::TileEntity::isFinished() {
    return KEXJavaBridge::TileEntityEvents::isFinished((jlong) this);
}

void KEXTileEntityModule::TileEntity::onChanged(BlockSource& world) {
    KEXJavaBridge::TileEntityEvents::onChanged((jlong) this);
}

bool KEXTileEntityModule::TileEntity::isMovable(BlockSource& world) {
    return KEXJavaBridge::TileEntityEvents::isMovable((jlong) this);
}

void KEXTileEntityModule::TileEntity::onPlace(BlockSource& world) {
    KEXJavaBridge::TileEntityEvents::onPlace((jlong) this);
}

void KEXTileEntityModule::TileEntity::onMove() {
    KEXJavaBridge::TileEntityEvents::onMove((jlong) this);
}

void KEXTileEntityModule::TileEntity::onRemoved(BlockSource& world) {
    KEXJavaBridge::TileEntityEvents::onRemoved((jlong) this);
}

void KEXTileEntityModule::TileEntity::triggerEvent(int id, int type) {
    BlockActor::triggerEvent(id, type);
    KEXJavaBridge::TileEntityEvents::triggerEvent((jlong) this, id, type);
}

void KEXTileEntityModule::TileEntity::onNeighborChanged(BlockSource& world, const BlockPos& changed) {
    KEXJavaBridge::TileEntityEvents::onNeighborChanged((jlong) this, changed.x, changed.y, changed.z);
}

const stl::string& KEXTileEntityModule::TileEntity::getCustomName() const {
    JNIEnv* env = KEXJavaUtils::attach();
    jstring jResult = KEXJavaBridge::TileEntityEvents::getCustomName((jlong) this);
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
    jstring jResult = KEXJavaBridge::TileEntityEvents::getName((jlong) this);
    if(jResult == nullptr) return "";
    const char* cResult = env->GetStringUTFChars(jResult, 0);
    stl::string result(cResult);
    env->ReleaseStringUTFChars(jResult, cResult);
    env->DeleteLocalRef(jResult);
    return result;
}

void KEXTileEntityModule::TileEntity::setCustomName(const stl::string& customName) {
    KEXJavaBridge::TileEntityEvents::setCustomName((jlong) this, customName.c_str());
}

void KEXTileEntityModule::TileEntity::onChunkLoaded(LevelChunk& levelChunk) {
    KEXJavaBridge::TileEntityEvents::onChunkLoaded((jlong) this);
}

void KEXTileEntityModule::TileEntity::onChunkUnloaded(LevelChunk& levelChunk) {
    KEXJavaBridge::TileEntityEvents::onChunkUnloaded((jlong) this);
}

bool KEXTileEntityModule::TileEntity::onUse(Player& player, unsigned char side, const Vec3& vec) const {
    return KEXJavaBridge::TileEntityEvents::onUse((jlong) this, player.getUniqueID()->id, (char) side, vec.x, vec.y, vec.z);
}