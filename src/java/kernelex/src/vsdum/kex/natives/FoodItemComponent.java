package vsdum.kex.natives;

import java.util.ArrayList;
import java.util.List;

import com.zhekasmirnov.apparatus.api.common.Vector3;

import android.support.annotation.Nullable;

public class FoodItemComponent {
    
    protected static native int nativeGetItem(long ptr);
    protected static native int nativeGetNutrition(long ptr);
    protected static native float nativeGetSaturationModifier(long ptr);
    @Nullable protected static native String nativeGetUsingConvertsTo(long ptr);
    protected static native int nativeGetOnUseAction(long ptr);
    protected static native float[] nativeGetOnUseRange(long ptr);
    @Nullable protected static native String nativeGetCooldownType(long ptr);
    protected static native int nativeGetCooldownTime(long ptr);
    protected static native boolean nativeCanAlwaysEat(long ptr);
    protected static native int nativeGetEffectsCount(long ptr);
    protected static native int[] nativeGetRemoveEffects(long ptr);
    @Nullable protected static native String nativeEffectGetDescriptionId(long ptr, int index);
    protected static native int nativeEffectGetId(long ptr, int index);
    protected static native int nativeEffectGetDuration(long ptr, int index);
    protected static native int nativeEffectGetAmplifier(long ptr, int index);
    protected static native float nativeEffectGetChance(long ptr, int index);

    private final int id;
    private final int nutrition;
    private final float saturationModifier;
    private final float saturation;
    @Nullable private final String usingConvertsTo;
    private final int onUseAction;
    private final Vector3 onUseRange;
    @Nullable private final String cooldownType;
    private final int cooldownTime;
    private final boolean _canAlwaysEat;
    private final List<Effect> effects = new ArrayList<>();
    private final List<Integer> removeEffects = new ArrayList<>();

    public FoodItemComponent(long ptr)
    {
        this.id = nativeGetItem(ptr);
        this.nutrition = nativeGetNutrition(ptr);
        this.saturationModifier = nativeGetSaturationModifier(ptr) * 2.0f;
        this.saturation = this.nutrition * this.saturationModifier;
        this.usingConvertsTo = nativeGetUsingConvertsTo(ptr);
        this.onUseAction = nativeGetOnUseAction(ptr);
        float[] range = nativeGetOnUseRange(ptr);
        this.onUseRange = new Vector3(range[0], range[1], range[2]);
        this.cooldownType = nativeGetCooldownType(ptr);
        this.cooldownTime = nativeGetCooldownTime(ptr);
        this._canAlwaysEat = nativeCanAlwaysEat(ptr);
        for(int i = 0; i < nativeGetEffectsCount(ptr); ++i) this.effects.add(new Effect(ptr, i));
        int[] reff = nativeGetRemoveEffects(ptr);
        for(int i = 0; i < reff.length; ++i) this.removeEffects.add(reff[i]);
    }

    public final int getItem()
    {
        return this.id;
    }

    public final int getNutrition()
    {
        return this.nutrition;
    }

    public final float getSaturationModifier()
    {
        return this.saturationModifier;
    }

    public final float getSaturation()
    {
        return this.saturation;
    }

    @Nullable public final String getUsingConvertsTo()
    {
        return this.usingConvertsTo;
    }

    public final int getOnUseAction()
    {
        return this.onUseAction;
    }

    public final Vector3 getOnUseRange()
    {
        return this.onUseRange;
    }

    @Nullable public final String getCooldownType()
    {
        return this.cooldownType;
    }

    public final int getCooldownTime()
    {
        return this.cooldownTime;
    }

    public final boolean canAlwaysEat()
    {
        return this._canAlwaysEat;
    }

    public final List<Effect> getEffects()
    {
        return this.effects;
    }

    public final List<Integer> getRemoveEffects()
    {
        return this.removeEffects;
    }

    public static final class Effect {

        @Nullable private final String descriptionId;
        private final int id;
        @Nullable private final MobEffect effect;
        private final int duration;
        private final int amplifier;
        private final float chance;

        public Effect(long ptr, int index)
        {
            this.descriptionId = nativeEffectGetDescriptionId(ptr, index);
            this.id = nativeEffectGetId(ptr, index);
            this.effect = MobEffect.getById(id);
            this.duration = nativeEffectGetDuration(ptr, index);
            this.amplifier = nativeEffectGetAmplifier(ptr, index);
            this.chance = nativeEffectGetChance(ptr, index);
        }

        @Nullable public final String getDescriptionId()
        {
            return this.descriptionId;
        }

        public final int getId()
        {
            return this.id;
        }

        @Nullable public final MobEffect getEffect()
        {
            return this.effect;
        }

        public final int getDuration()
        {
            return this.duration;
        }

        public final int getAmplifier()
        {
            return this.amplifier;
        }

        public final float getChance()
        {
            return this.chance;
        }

    }

}
