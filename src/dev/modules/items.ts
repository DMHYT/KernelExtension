interface FoodParamsDescription {
    stack?: number,
    isTech?: boolean,
    food?: number,
    nutrition?: number,
    saturation_modifier?: "poor" | "low" | "normal" | "good" | "max" | "supernatural" | string,
    is_meat?: boolean,
    can_always_eat?: boolean,
    cooldown_time?: number,
    cooldown_type?: "chorusfruit" | "none",
    on_use_range?: [ number, number, number ],
    on_use_action?: "chorus_teleport" | "suspicious_stew_effect" | "none",
    using_converts_to?: string,
    effects?: {
        name?: Lowercase<keyof typeof EPotionEffect>,
        duration?: number,
        amplifier?: number,
        chance?: number
    }[]
}

namespace Item {
    // @ts-ignore
    export function createFoodItem(nameID: string, name: string, texture: TextureData, params: FoodParamsDescription): NativeItem {
        const commonParamsObj: { stack?: number, isTech?: boolean } = { stack: 64 };
        if(typeof params.stack === "number" && params.stack > 0) {
            commonParamsObj.stack = params.stack;
            delete params.stack;
        }
        if(typeof params.isTech === "boolean") {
            commonParamsObj.isTech = params.isTech;
            delete params.isTech;
        }
        const result = createItem(nameID, name, texture, commonParamsObj);
        if(typeof params.food === "number") {
            params.nutrition = Math.max(params.food, 1);
            delete params.food;
        }
        params.nutrition ??= 1;
        params.saturation_modifier ??= "normal";
        let isMeat: boolean = false;
        if(typeof params.is_meat === "boolean") {
            isMeat = params.is_meat;
            delete params.is_meat;
        }
        result.setUseAnimation(1);
        result.setMaxUseDuration(32);
        result.setProperties(JSON.stringify({
            use_animation: "eat",
            use_duration: 32,
            food: {
                nutrition: params.nutrition,
                saturation_modifier: params.saturation_modifier,
                is_meat: isMeat
            },
            components: { "minecraft:food": params }
        }));
        return result;
    }
}


const ItemsModule = WRAP_JAVA("vsdum.kex.modules.ItemsModule");


enum ESaturationModifier {
    POOR = 0.2,
    LOW = 0.6,
    NORMAL = 1.2,
    GOOD = 1.6,
    MAX = 2.0,
    SUPERNATURAL = 2.4
}