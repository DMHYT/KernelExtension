#ifndef KEX_MOVEINPUTHANDLER_HPP
#define KEX_MOVEINPUTHANDLER_HPP


#ifndef KEX_VEC3_HPP
    class Vec3;
#endif

class MoveInputHandler {
    public:
    char vtable[4]; // 4
    float movingLeft; // 8
    float movingForward; // 12
    // virtual void clearInputState();
    // virtual bool isChangeHeight() const;
    // virtual bool isPlayerMoving() const;
    // virtual Vec3 getGazeDirection() const;
    bool isMovingLeft() const;
    bool isJumpDown() const;
    bool isMovingRight() const;
    void setGazeDirection(Vec3 const&);
    bool wantsMoveForward() const;
    bool isMovingForward() const;
    void setSneakPersistence(bool);
    // --- Added by KernelExtension ---
    bool isMovingBackward() const;
    float getMovingForward() const;
    float getMovingBackward() const;
    float getMovingLeft() const;
    float getMovingRight() const;
};


#endif //KEX_MOVEINPUTHANDLER_HPP