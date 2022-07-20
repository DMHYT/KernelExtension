package vsdum.kex.natives;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.zhekasmirnov.apparatus.api.common.Vector3;
import com.zhekasmirnov.horizon.runtime.logger.Logger;

import android.support.annotation.Nullable;
import vsdum.kex.common.INativeInterface;

public class FoodItemComponent implements INativeInterface {
    
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
    protected static native int nativeEffectGetId(long ptr, int index);
    protected static native int nativeEffectGetDuration(long ptr, int index);
    protected static native int nativeEffectGetAmplifier(long ptr, int index);
    protected static native float nativeEffectGetChance(long ptr, int index);
    protected static native void nativeSetNutrition(long ptr, int nutrition);
    protected static native void nativeSetSaturationModifier(long ptr, float satMod);
    protected static native void nativeSetCanAlwaysEat(long ptr, boolean always);
    protected static native void nativeClearEffects(long ptr);
    protected static native void nativeAddEffect(long ptr, int id, int duration, int amplifier, float chance);

    private final long pointer;

    public final long getPointer()
    {
        return this.pointer;
    }

    private final int id;
    private int nutrition;
    private float saturationModifier;
    private float saturation;
    @Nullable private final String usingConvertsTo;
    private final int onUseAction;
    private final Vector3 onUseRange;
    @Nullable private final String cooldownType;
    private final int cooldownTime;
    private boolean _canAlwaysEat;
    private final List<Effect> effects = new ArrayList<>();
    private final List<Integer> removeEffects = new ArrayList<>();

    private final boolean mutable;

    public final boolean isMutable()
    {
        return this.mutable;
    }

    public FoodItemComponent(long ptr, boolean isMutable)
    {
        this.pointer = ptr;
        this.mutable = isMutable;
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

    public void setNutrition(int nutrition)
    {
        if(this.isMutable())
        {
            this.nutrition = nutrition;
            nativeSetNutrition(this.pointer, nutrition);
        } else Logger.warning("[KEX-FoodItemComponent] The following FoodItemComponent is immutable, setNutrition cannot be called!");
    }

    public void setSaturationModifier(float satMod)
    {
        if(this.isMutable())
        {
            this.saturationModifier = satMod;
            this.saturation = this.nutrition * this.saturationModifier;
            nativeSetSaturationModifier(this.pointer, this.saturationModifier / 2.0f);
        } else Logger.warning("[KEX-FoodItemComponent] The following FoodItemComponent is immutable, setSaturationModifier cannot be called!");
    }

    public void setCanAlwaysEat(boolean can)
    {
        if(this.isMutable())
        {
            this._canAlwaysEat = can;
            nativeSetCanAlwaysEat(this.pointer, can);
        } else Logger.warning("[KEX-FoodItemComponent] The following FoodItemComponent is immutable, setCanAlwaysEat cannot be called!");
    }

    public void clearEffects()
    {
        if(this.isMutable())
        {
            this.effects.clear();
            nativeClearEffects(this.pointer);
        } else Logger.warning("[KEX-FoodItemComponent] The following FoodItemComponent is immutable, clearEffects cannot be called!");
    }

    public void addEffect(MobEffectInstance effect, float chance)
    {
        if(this.isMutable())
        {
            this.effects.add(new Effect(effect.getId(), effect.getDuration(), effect.getAmplifier(), chance));
            nativeAddEffect(this.pointer, effect.getId(), effect.getDuration(), effect.getAmplifier(), chance);
        } else Logger.warning("[KEX-FoodItemComponent] The following FoodItemComponent is immutable, addEffect cannot be called!");
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
            this.id = nativeEffectGetId(ptr, index);
            this.effect = MobEffect.getById(id);
            this.descriptionId = this.effect == null ? null : this.effect.getDescriptionId();
            this.duration = nativeEffectGetDuration(ptr, index);
            this.amplifier = nativeEffectGetAmplifier(ptr, index);
            this.chance = nativeEffectGetChance(ptr, index);
        }

        public Effect(int id, int duration, int amplifier, float chance)
        {
            this.id = id;
            this.duration = duration;
            this.amplifier = amplifier;
            this.chance = chance;
            this.effect = MobEffect.getById(this.id);
            this.descriptionId = this.effect != null ? this.effect.getDescriptionId() : null;
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

    public static class Builder {

        private int _nutrition = 0;
        private float _saturationMod = 1.2f;
        private boolean _alwaysEat = false;
        private final Map<MobEffectInstance, Float> effects = new HashMap<>();

        public Builder() {}

        public Builder nutrition(int nutr)
        {
            this._nutrition = nutr;
            return this;
        }

        public Builder saturationMod(float sat)
        {
            this._saturationMod = sat;
            return this;
        }

        public Builder alwaysEat()
        {
            this._alwaysEat = true;
            return this;
        }

        public Builder effect(MobEffectInstance effect)
        {
            return this.effect(effect, 1.0f);
        }

        public Builder effect(MobEffectInstance effect, float chance)
        {
            this.effects.put(effect, chance);
            return this;
        }

        public int getNutrition()
        {
            return this._nutrition;
        }

        public float getSaturationMod()
        {
            return this._saturationMod;
        }

        public boolean getAlwaysEat()
        {
            return this._alwaysEat;
        }

        public Map<MobEffectInstance, Float> getEffects()
        {
            return this.effects;
        }

    }

}
