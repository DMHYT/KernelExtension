package vsdum.kex.natives;

import vsdum.kex.common.INativeInterface;

public class MoveInputHandler implements INativeInterface {

    protected static native void nativeClearInputState(long ptr);
    protected static native boolean nativeIsChangeHeight(long ptr);
    protected static native boolean nativeIsPlayerMoving(long ptr);
    protected static native boolean nativeIsJumpDown(long ptr);
    protected static native boolean nativeWantsMoveForward(long ptr);
    protected static native void nativeSetSneakPersistence(long ptr, boolean persistence);
    protected static native void nativeSetGazeDirection(long ptr, float x, float y, float z);
    protected static native boolean nativeIsMovingForward(long ptr);
    protected static native boolean nativeIsMovingBackward(long ptr);
    protected static native boolean nativeIsMovingLeft(long ptr);
    protected static native boolean nativeIsMovingRight(long ptr);
    protected static native float nativeGetMovingForward(long ptr);
    protected static native float nativeGetMovingBackward(long ptr);
    protected static native float nativeGetMovingLeft(long ptr);
    protected static native float nativeGetMovingRight(long ptr);
    
    protected final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    public MoveInputHandler(long ptr)
    {
        this.pointer = ptr;
    }

    public void clearInputState()
    {
        nativeClearInputState(this.pointer);
    }

    public boolean isChangeHeight()
    {
        return nativeIsChangeHeight(this.pointer);
    }

    public boolean isPlayerMoving()
    {
        return nativeIsPlayerMoving(this.pointer);
    }

    public boolean isJumpDown()
    {
        return nativeIsJumpDown(this.pointer);
    }

    public boolean wantsMoveForward()
    {
        return nativeWantsMoveForward(this.pointer);
    }

    public void setSneakPersistence(boolean persistence)
    {
        nativeSetSneakPersistence(this.pointer, persistence);
    }

    public void setGazeDirection(float x, float y, float z)
    {
        nativeSetGazeDirection(this.pointer, x, y, z);
    }

    public boolean isMovingForward()
    {
        return nativeIsMovingForward(this.pointer);
    }

    public boolean isMovingBackward()
    {
        return nativeIsMovingBackward(this.pointer);
    }

    public boolean isMovingLeft()
    {
        return nativeIsMovingLeft(this.pointer);
    }

    public boolean isMovingRight()
    {
        return nativeIsMovingRight(this.pointer);
    }

    public float getMovingForward()
    {
        return nativeGetMovingForward(this.pointer);
    }

    public float getMovingBackward()
    {
        return nativeGetMovingBackward(this.pointer);
    }

    public float getMovingLeft()
    {
        return nativeGetMovingLeft(this.pointer);
    }

    public float getMovingRight()
    {
        return nativeGetMovingRight(this.pointer);
    }

}
