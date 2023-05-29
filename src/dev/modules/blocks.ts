const BlocksModule = WRAP_JAVA("vsdum.kex.modules.BlocksModule");


Block.registerComparatorSignalFunctionForID = (id, func, isCallbackForced?) => BlocksModule.registerComparatorSignalCallbackJS(id, func, isCallbackForced ?? false);
Block.registerComparatorSignalFunction = (id, func, isCallbackForced?) => {
    const numericID = Block.getNumericId(id);
    if(numericID == -1) return;
    Block.registerComparatorSignalFunctionForID(numericID, func, isCallbackForced);
}

Block.registerEntityStepOnFunctionForID = (id, func) => {
    BlocksModule.registerOnStepOnCallback(id, (world, pos, state, entity) => func(pos, state, entity.getUniqueID()));
    return true;
}
Block.registerEntityStepOnFunction = (id, func) => {
    const numericID = Block.getNumericId(id);
    if(numericID == -1) return;
    return Block.registerEntityStepOnFunctionForID(numericID, func);
}

Block.registerEntityStepOffFunctionForID = (id, func) => BlocksModule.registerOnStepOffCallback(id, (world, pos, state, entity) => func(pos, state, entity.getUniqueID()));
Block.registerEntityStepOffFunction = (id, func) => {
    const numericID = Block.getNumericId(id);
    if(numericID == -1) return;
    Block.registerEntityStepOffFunctionForID(numericID, func);
}

Block.getLightLevel = (id: number, data?: number) => BlocksModule.getLightEmission(id, data ?? 0);
Block.setLightLevel = (id: number, data: number, lightLevel?: number) => typeof lightLevel === "number" ? BlocksModule.setLightEmission(id, data, lightLevel) : BlocksModule.setLightEmission(id, 0, data);