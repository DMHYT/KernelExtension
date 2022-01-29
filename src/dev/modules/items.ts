interface FoodParamsDescription {
    stack?: number,
    isTech?: boolean,
    food?: number,
    nutrition?: number,
    saturation_modifier?: "poor" | "low" | "normal" | "good" | "max" | "supernatural",
    is_meat?: boolean,
    can_always_eat?: boolean,
    cooldown_time?: number,
    cooldown_type?: "chorusfruit" | "none",
    on_use_range?: [ number, number, number ],
    on_use_action?: "chorus_teleport" | "suspicious_stew_effect" | "none",
    using_converts_to?: string,
    effects?: {
        name?: Lowercase<keyof typeof EPotionEffect> | string,
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
        const result = createItem(nameID, name, texture, params);
        if(typeof params.food === "number" && params.food > 0) {
            params.nutrition = params.food;
            delete params.food;
        } else params.food = 1;
        result.setProperties(JSON.stringify(params));
        return result;
    }
}


const ItemsModule = WRAP_JAVA("vsdum.kex.modules.ItemsModule");