const BlocksModule = WRAP_JAVA("vsdum.kex.modules.BlocksModule");

Block.registerComparatorSignalFunctionForID = (id, func) => BlocksModule.registerComparatorSignalCallbackJS(id, func);
Block.registerComparatorSignalFunction = (id, func) => {
    const numericID = Block.getNumericId(id);
    if(numericID == -1) return;
    Block.registerComparatorSignalFunctionForID(numericID, func);
}