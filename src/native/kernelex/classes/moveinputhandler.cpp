#include <jni.h>
#include <innercore/vtable.h>
#include <commontypes.hpp>
#include <MoveInputHandler.hpp>


bool MoveInputHandler::isMovingBackward() const {
    return this->movingForward < 0.0f;
}
float MoveInputHandler::getMovingForward() const {
    return this->isMovingForward() ? this->movingForward : 0.0f;
}
float MoveInputHandler::getMovingBackward() const {
    return this->isMovingBackward() ? -(this->movingForward) : 0.0f;
}
float MoveInputHandler::getMovingLeft() const {
    return this->isMovingLeft() ? this->movingLeft : 0.0f;
}
float MoveInputHandler::getMovingRight() const {
    return this->isMovingRight() ? -(this->movingLeft) : 0.0f;
}


#define __EXPORT__(RET, NAME, ...) JNIEXPORT RET JNICALL Java_vsdum_kex_natives_MoveInputHandler_native##NAME (JNIEnv* env, jclass clazz, jlong ptr, ##__VA_ARGS__)


extern "C" {
    __EXPORT__(void, ClearInputState) {
        VTABLE_FIND_OFFSET(MoveInputHandler_clearInputState, _ZTV16MoveInputHandler, _ZN16MoveInputHandler15clearInputStateEv);
        VTABLE_CALL<void>(MoveInputHandler_clearInputState, (MoveInputHandler*) ptr);
    }
    __EXPORT__(jboolean, IsChangeHeight) {
        VTABLE_FIND_OFFSET(MoveInputHandler_isChangeHeight, _ZTV16MoveInputHandler, _ZNK16MoveInputHandler14isChangeHeightEv);
        return VTABLE_CALL<bool>(MoveInputHandler_isChangeHeight, (MoveInputHandler*) ptr);
    }
    __EXPORT__(jboolean, IsPlayerMoving) {
        VTABLE_FIND_OFFSET(MoveInputHandler_isPlayerMoving, _ZTV16MoveInputHandler, _ZNK16MoveInputHandler14isPlayerMovingEv);
        return VTABLE_CALL<bool>(MoveInputHandler_isPlayerMoving, (MoveInputHandler*) ptr);
    }
    __EXPORT__(jboolean, IsJumpDown) {
        return ((MoveInputHandler*) ptr)->isJumpDown();
    }
    __EXPORT__(jboolean, WantsMoveForward) {
        return ((MoveInputHandler*) ptr)->wantsMoveForward();
    }
    __EXPORT__(void, SetSneakPersistence, jboolean persistence) {
        ((MoveInputHandler*) ptr)->setSneakPersistence(persistence);
    }
    __EXPORT__(void, SetGazeDirection, jfloat x, jfloat y, jfloat z) {
        ((MoveInputHandler*) ptr)->setGazeDirection(Vec3(x, y, z));
    }
    __EXPORT__(jboolean, IsMovingForward) {
        return ((MoveInputHandler*) ptr)->isMovingForward();
    }
    __EXPORT__(jboolean, IsMovingBackward) {
        return ((MoveInputHandler*) ptr)->isMovingBackward();
    }
    __EXPORT__(jboolean, IsMovingLeft) {
        return ((MoveInputHandler*) ptr)->isMovingLeft();
    }
    __EXPORT__(jboolean, IsMovingRight) {
        return ((MoveInputHandler*) ptr)->isMovingRight();
    }
    __EXPORT__(jfloat, GetMovingForward) {
        return ((MoveInputHandler*) ptr)->getMovingForward();
    }
    __EXPORT__(jfloat, GetMovingBackward) {
        return ((MoveInputHandler*) ptr)->getMovingBackward();
    }
    __EXPORT__(jfloat, GetMovingLeft) {
        return ((MoveInputHandler*) ptr)->getMovingLeft();
    }
    __EXPORT__(jfloat, GetMovingRight) {
        return ((MoveInputHandler*) ptr)->getMovingRight();
    }
}


#undef __EXPORT__