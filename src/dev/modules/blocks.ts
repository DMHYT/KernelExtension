const BlocksModule = WRAP_JAVA("vsdum.kex.modules.BlocksModule");


Block.registerComparatorSignalFunctionForID = (id, func, isCallbackForced?) => BlocksModule.registerComparatorSignalCallbackJS(id, func, isCallbackForced ?? false);
Block.registerComparatorSignalFunction = (id, func, isCallbackForced?) => {
    const numericID = Block.getNumericId(id);
    if(numericID == -1) return;
    Block.registerComparatorSignalFunctionForID(numericID, func, isCallbackForced);
}

Block.getLightLevel = (id: number, data?: number) => BlocksModule.getLightEmission(id, data ?? 0);
Block.setLightLevel = (id: number, data: number, lightLevel?: number) => typeof lightLevel === "number" ? BlocksModule.setLightEmission(id, data, lightLevel) : BlocksModule.setLightEmission(id, 0, data);