const ModCallbacks = WRAP_JAVA("vsdum.kex.common.ModCallbacks");

ModCallbacks.specifyModDir(`${__dir__}/`);
Callback.addCallback("LevelDisplayed", () => ModCallbacks.onLevelDisplayed());
Callback.addCallback("LevelSelected", () => ModCallbacks.onLevelSelected());
Callback.addCallback("LevelLeft", () => ModCallbacks.onLevelLeft());
Callback.addCallback("NativeGuiChanged", screenName => ModCallbacks.onNativeGuiChanged(screenName));
Callback.addCallback("LocalTick", () => ModCallbacks.onLocalTick());
Callback.addCallback("ItemIconOverride", item => ModCallbacks.onIconOverride(item.id));
Callback.addCallback("ModsLoaded", () => ModCallbacks.onModsLoaded());

const BlockEvents = WRAP_JAVA("vsdum.kex.japi.blocks.BlockEvents");
(() => {
    // @ts-ignore
    Block.__getBlockDropViaItem = Block.getBlockDropViaItem;
    Block.getBlockDropViaItem = (block, item, coords, region) => {
        // @ts-ignore
        const result = Block.__getBlockDropViaItem(block, item, coords, region) ?? [];
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
Callback.addCallback("BlockEventNeighbourChange", (coords, block, changedCoords, region) => BlockEvents.neighborChanged(block.id, block.data, region.getDimension(), coords.x, coords.y, coords.z, changedCoords.x, changedCoords.y, changedCoords.z));
(() => {
    // @ts-ignore
    Block.__getPlaceFunc = Block.getPlaceFunc;
    Block.getPlaceFunc = blockID => {
        // @ts-ignore
        const func = Block.__getPlaceFunc(blockID);
        return typeof func === "undefined" ? func :
        (coords, item, block, player, region) => {
            BlockEvents.onPlace(coords.x, coords.y, coords.z, item.id, item.count, item.data, item.extra ?? null, block.id, block.data, player, region.getDimension(), blockID);
            return func(coords, item, block, player, region);
        }
    }
})();
Callback.addCallback("PopBlockResources", (coords, block, r, i, region) => BlockEvents.popResources(coords.x, coords.y, coords.z, region.getDimension(), block.id, block.data));

const ItemEvents = WRAP_JAVA("vsdum.kex.japi.items.ItemEvents");
Callback.addCallback("ItemDispensed", (coords, item, region, slot) => ItemEvents.onDispense(coords.x, coords.y, coords.z, coords.side, coords.vec.x, coords.vec.y, coords.vec.z, item.id, item.count, item.data, item.extra ?? null, region.getDimension(), slot));
Callback.addCallback("ItemUsingReleased", (item, ticks, player) => ItemEvents.onReleaseUsing(item.id, item.count, item.data, item.extra ?? null, ticks, player));
Callback.addCallback("ItemIconOverride", (item, isModUI) => ItemEvents.getIcon(item.id, item.count, item.data, item.extra ?? null, isModUI));
Callback.addCallback("ItemUsingComplete", (item, player) => ItemEvents.onCompleteUsing(item.id, item.count, item.data, item.extra ?? null, player));
Callback.addCallback("ItemUseNoTarget", (item, player) => ItemEvents.onUseNoTarget(item.id, item.count, item.data, item.extra ?? null, player));
Callback.addCallback("ProjectileHit", (projectile, item, target) => ItemEvents.onProjectileHit(projectile, item.id, item.count, item.data, item.extra ?? null, target.x, target.y, target.z, target.entity, target.coords?.x ?? 0, target.coords?.y ?? 0, target.coords?.z ?? 0, target.coords?.side ?? 0));

Callback.addCallback("ItemUse", (coords, item, block, ie, player) => {
    if(!Game.isActionPrevented()) {
        BlockEvents.onUse(block.id, block.data, Entity.getDimension(player), coords.x, coords.y, coords.z, player, coords.side, coords.vec.x, coords.vec.y, coords.vec.z);
        ItemEvents.onUse(coords.x, coords.y, coords.z, coords.side, coords.vec.x, coords.vec.y, coords.vec.z, item.id, item.count, item.data, item.extra ?? null, block.id, block.data, player);
    }
});