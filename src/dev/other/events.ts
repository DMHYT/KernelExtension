const ModCallbacks = WRAP_JAVA("vsdum.kex.common.ModCallbacks");

ModCallbacks.specifyModDir(`${__dir__}/`);
Callback.addCallback("LevelDisplayed", () => ModCallbacks.onLevelDisplayed());
Callback.addCallback("LevelLeft", () => ModCallbacks.onLevelLeft());
Callback.addCallback("NativeGuiChanged", screenName => ModCallbacks.onNativeGuiChanged(screenName));
Callback.addCallback("LocalTick", () => ModCallbacks.onLocalTick());
Callback.addCallback("ItemIconOverride", item => ModCallbacks.onIconOverride(item.id));
Callback.addCallback("ModsLoaded", () => ModCallbacks.onModsLoaded());

const BlockEvents = WRAP_JAVA("vsdum.kex.japi.blocks.BlockEvents");
Callback.addCallback("ItemUse", (coords, item, block, ie, player) => {
    if(!Game.isActionPrevented()) {
        BlockEvents.onUse(block.id, block.data, Entity.getDimension(player), coords.x, coords.y, coords.z, player, coords.side, coords.vec.x, coords.vec.y, coords.vec.z);
    }
});
(() => {
    const temp = Block.getBlockDropViaItem;
    Block.getBlockDropViaItem = (block, item, coords, region) => {
        const result = temp(block, item, coords, region) ?? [];
        const iter = BlockEvents.getDrops(block.id, block.data, region.getDimension(), item.id, item.count, item.data, item.extra ?? null, coords.x, coords.y, coords.z)
            .iterator();
        while(iter.hasNext()) {
            const stack = iter.next();
            result.push([ stack.id, stack.count, stack.data, stack.extra ]);
        }
        return result;
    }
})();
Callback.addCallback("BlockEventEntityInside", (coords, block, entity) => BlockEvents.entityInside(block.id, block.data, Entity.getDimension(entity), coords.x, coords.y, coords.z, entity));
Callback.addCallback("BlockEventEntityStepOn", (coords, block, entity) => BlockEvents.stepOn(Entity.getDimension(entity), coords.x, coords.y, coords.z, block.id, block.data, entity));
Callback.addCallback("BlockEventNeighbourChange", (coords, block, changedCoords, region) => BlockEvents.neighborChanged(block.id, block.data, region.getDimension(), coords.x, coords.y, coords.z, changedCoords.x, changedCoords.y, changedCoords.z));
(() => {
    const temp = Block.getPlaceFunc;
    Block.getPlaceFunc = blockID => {
        return (coords, item, block, player, region) => {
            BlockEvents.onPlace(coords.x, coords.y, coords.z, item.id, item.count, item.data, item.extra ?? null, block.id, block.data, player, region.getDimension(), blockID);
            const func = temp(blockID);
            if(typeof func !== "undefined") {
                return func(coords, item, block, player, region);
            }
        }
    }
})();
Callback.addCallback("PopBlockResources", (coords, block, r, i, region) => BlockEvents.popResources(coords.x, coords.y, coords.z, region.getDimension(), block.id, block.data));