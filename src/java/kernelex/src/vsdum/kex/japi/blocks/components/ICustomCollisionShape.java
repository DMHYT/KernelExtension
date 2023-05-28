package vsdum.kex.japi.blocks.components;

import com.zhekasmirnov.innercore.api.NativeICRender.CollisionShape;

import android.support.annotation.Nullable;

public interface ICustomCollisionShape {

    public default boolean hasCollision()
    {
        return true;
    }

    public default boolean hasCollision(int meta)
    {
        return this.hasCollision();
    }

    @Nullable public default CollisionShape getCollisionShape()
    {
        return null;
    }

    @Nullable public default CollisionShape getCollisionShape(int meta)
    {
        return this.getCollisionShape();
    }

}
