package vsdum.kex.japi.internal.block.model;

import java.lang.reflect.Field;

import com.zhekasmirnov.innercore.api.NativeICRender.AND;
import com.zhekasmirnov.innercore.api.NativeICRender.RANDOM;

import android.support.annotation.Nullable;

public class WeightedRandomRenderCondition extends RANDOM {

    private final int weight;

    protected static native long nativeNew(int min, int max, int sum);

    public WeightedRandomRenderCondition(int min, int max, int sum, int weight)
    {
        super(min, max, sum);
        this.weight = weight;
        long newPtr = nativeNew(min, max, sum);
        try {
            Field pointerField = RANDOM.class.getSuperclass().getDeclaredField("ptr");
            pointerField.setAccessible(true);
            pointerField.set(this, newPtr);
        } catch(Throwable ex) { ex.printStackTrace(); }
    }

    @Override public RANDOM setAxisEnabled(int axis, boolean enabled)
    {
        throw new UnsupportedOperationException();
    }

    @Nullable public static Object mergeWithInnerCore(WeightedRandomRenderCondition weighted, Object innercore)
    throws Throwable
    {
        if(weighted != null && innercore != null)
            return AND.class.getConstructors()[0].newInstance(weighted, innercore);
        if(weighted != null) return weighted;
        if(innercore != null) return innercore;
        return null;
    }

    public final int getWeight()
    {
        return this.weight;
    }

}