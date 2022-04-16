type List<T = any> = { [key: string]: T };

namespace Callback {
	const _add = Callback.addCallback;

	interface CallbackInfo<C = Function> {
		once: boolean;
		callback: C,
		priority: number;
	}

	const eventList: List<CallbackInfo[]> = {};
	function invoker(name: string): Function {
		return (...args: any[]) => {
			const curList = eventList[name];
			for (let i = 0; i < curList.length; i++) {
				const ev = curList[i];
				ev.callback(...args);
				if (ev.once)
					off(name, ev.callback);
			}
		}
	}

	function add(name: string, info: CallbackInfo): void {
		if (eventList[name]) {
			const newList = [];
			let notAdded = true;
			for (const eventInfo of eventList[name]) {
				if (notAdded && eventInfo.priority > info.priority) {
					newList.push(info);
					notAdded = false;
				}
				newList.push(eventInfo);
			}
			if (notAdded) newList.push(info);
			eventList[name] = newList;
		} else {
			eventList[name] = [info];
			//@ts-ignore
			_add(name, invoker(name), -1);
		}
	}


	export function on(name: string, func: Function, priority?: number): void;
	export function on(name: "CraftRecipePreProvided", func: CraftRecipePreProvidedFunction, priority?: number): void;
	export function on(name: "CraftRecipeProvidedFunction", func: CraftRecipeProvidedFunction, priority?: number): void;
	export function on(name: "VanillaWorkbenchCraft", func: VanillaWorkbenchCraftFunction, priority?: number): void;
	export function on(name: "VanillaWorkbenchPostCraft", func: VanillaWorkbenchCraftFunction, priority?: number): void;
	export function on(name: "VanillaWorkbenchRecipeSelected", func: VanillaWorkbenchRecipeSelectedFunction, priority?: number): void;
	export function on(name: "ContainerClosed", func: ContainerClosedFunction, priority?: number): void;
	export function on(name: "ContainerOpened", func: ContainerOpenedFunction, priority?: number): void;
	export function on(name: "CustomWindowOpened", func: CustomWindowOpenedFunction, priority?: number): void;
	export function on(name: "CustomWindowClosed", func: CustomWindowClosedFunction, priority?: number): void;
	export function on(name: "CoreConfigured", func: CoreConfiguredFunction, priority?: number): void;
	export function on(name: "LevelSelected", func: LevelSelectedFunction, priority?: number): void;
	export function on(name: "DimensionLoaded", func: DimensionLoadedFunction, priority?: number): void;
	export function on(name: "DestroyBlock", func: DestroyBlockFunction, priority?: number): void;
	export function on(name: "DestroyBlockStart", func: DestroyBlockFunction, priority?: number): void;
	export function on(name: "DestroyBlockContinue", func: DestroyBlockContinueFunction, priority?: number): void;
	export function on(name: "BuildBlock", func: BuildBlockFunction, priority?: number): void;
	export function on(name: "BlockChanged", func: BlockChangedFunction, priority?: number): void;
	export function on(name: "ItemUse", func: ItemUseFunction, priority?: number): void;
	export function on(name: "ItemUseLocalServer", func: ItemUseFunction, priority?: number): void;
	export function on(name: "Explosion", func: ExplosionFunction, priority?: number): void;
	export function on(name: "FoodEaten", func: FoodEatenFunction, priority?: number): void;
	export function on(name: "ExpAdd", func: ExpAddFunction, priority?: number): void;
	export function on(name: "ExpLevelAdd", func: ExpLevelAddFunction, priority?: number): void;
	export function on(name: "NativeCommand", func: NativeCommandFunction, priority?: number): void;
	export function on(name: "PlayerAttack", func: PlayerAttackFunction, priority?: number): void;
	export function on(name: "EntityAdded", func: EntityAddedFunction, priority?: number): void;
	export function on(name: "EntityRemoved", func: EntityRemovedFunction, priority?: number): void;
	export function on(name: "EntityDeath", func: EntityDeathFunction, priority?: number): void;
	export function on(name: "EntityHurt", func: EntityHurtFunction, priority?: number): void;
	export function on(name: "EntityInteract", func: EntityInteractFunction, priority?: number): void;
	export function on(name: "ProjectileHit", func: ProjectileHitFunction, priority?: number): void;
	export function on(name: "RedstoneSignal", func: RedstoneSignalFunction, priority?: number): void;
	export function on(name: "PopBlockResources", func: PopBlockResourcesFunction, priority?: number): void;
	export function on(name: "ItemIconOverride", func: ItemIconOverrideFunction, priority?: number): void;
	export function on(name: "ItemNameOverride", func: ItemNameOverrideFunction, priority?: number): void;
	export function on(name: "ItemUseNoTarget", func: ItemUseNoTargetFunction, priority?: number): void;
	export function on(name: "ItemUsingReleased", func: ItemUsingReleasedFunction, priority?: number): void;
	export function on(name: "ItemUsingComplete", func: ItemUsingCompleteFunction, priority?: number): void;
	export function on(name: "ItemDispensed", func: ItemDispensedFunction, priority?: number): void;
	export function on(name: "NativeGuiChanged", func: NativeGuiChangedFunction, priority?: number): void;
	export function on(name: "GenerateChunk", func: GenerateChunkFunction, priority?: number): void;
	/**
		 * @deprecated
		 */
	export function on(name: "GenerateChunkUnderground", func: GenerateChunkFunction, priority?: number): void;
	export function on(name: "GenerateNetherChunk", func: GenerateChunkFunction, priority?: number): void;
	export function on(name: "GenerateEndChunk", func: GenerateChunkFunction, priority?: number): void;
	export function on(name: "GenerateChunkUniversal", func: GenerateChunkFunction, priority?: number): void;
	export function on(name: "GenerateBiomeMap", func: GenerateChunkFunction, priority?: number): void;
	export function on(name: "ReadSaves", func: SavesFunction, priority?: number): void;
	export function on(name: "WriteSaves", func: SavesFunction, priority?: number): void;
	export function on(name: "CustomBlockTessellation", func: CustomBlockTessellationFunction, priority?: number): void;
	export function on(name: "ServerPlayerTick", func: ServerPlayerTickFunction, priority?: number): void;
	export function on(name: "CustomDimensionTransfer", func: CustomDimensionTransferFunction, priority?: number): void;
	export function on(name: "BlockEventEntityInside", func: Block.EntityInsideFunction, priority?: number): void;
	export function on(name: "BlockEventEntityStepOn", func: Block.EntityStepOnFunction, priority?: number): void;
	export function on(name: "BlockEventNeighbourChange", func: Block.NeighbourChangeFunction, priority?: number): void;
	export function on(name: "ConnectingToHost", func: ConnectingToHostFunction, priority?: number): void;
	export function on(name: "DimensionUnloaded", func: DimensionUnloadedFunction, priority?: number): void;
	export function on(name: "LevelPreLeft", func: { (): void }, priority?: number): void;
	export function on(name: "LevelLeft", func: { (): void }, priority?: number): void;
	export function on(name: "ItemUseLocal", func: ItemUseLocalFunction, priority?: number): void;
	export function on(name: "SystemKeyEventDispatched", func: SystemKeyEventDispatchedFunction, priority?: number): void;
	export function on(name: "NavigationBackPressed", func: { (): void }, priority?: number): void;
	export function on(name: "LevelCreated", func: { (): void }, priority?: number): void;
	export function on(name: "LevelDisplayed", func: { (): void }, priority?: number): void;
	export function on(name: "LevelPreLoaded", func: LevelLoadedFunction, priority?: number): void;
	export function on(name: "LevelLoaded", func: LevelLoadedFunction, priority?: number): void;
	export function on(name: "LocalLevelLoaded", func: { (): void }, priority?: number): void;
	export function on(name: "LocalTick", func: { (): void }, priority?: number): void;
	export function on(name: "AppSuspended", func: { (): void }, priority?: number): void;
	export function on(name: "EntityPickUpDrop", func: EntityPickUpDropFunction, priority?: number): void;
	export function on(name: "ServerPlayerLoaded", func: PlayerFunction, priority?: number): void;

	export function on(name: "ServerPlayerLeft", func: PlayerFunction, priority?: number): void;
	export function on(name: "GenerateCustomDimensionChunk", func: GenerateCustomDimensionChunkFunction, priority?: number): void;
	export function on(name: string, callback: Function, priority: number = 10): void {
		add(name, {
			callback, priority,
			once: false
		});
	}

	export function once(name: string, func: Function, priority?: number): void;
	export function once(name: "CraftRecipePreProvided", func: CraftRecipePreProvidedFunction, priority?: number): void;
	export function once(name: "CraftRecipeProvidedFunction", func: CraftRecipeProvidedFunction, priority?: number): void;
	export function once(name: "VanillaWorkbenchCraft", func: VanillaWorkbenchCraftFunction, priority?: number): void;
	export function once(name: "VanillaWorkbenchPostCraft", func: VanillaWorkbenchCraftFunction, priority?: number): void;
	export function once(name: "VanillaWorkbenchRecipeSelected", func: VanillaWorkbenchRecipeSelectedFunction, priority?: number): void;
	export function once(name: "ContainerClosed", func: ContainerClosedFunction, priority?: number): void;
	export function once(name: "ContainerOpened", func: ContainerOpenedFunction, priority?: number): void;
	export function once(name: "CustomWindowOpened", func: CustomWindowOpenedFunction, priority?: number): void;
	export function once(name: "CustomWindowClosed", func: CustomWindowClosedFunction, priority?: number): void;
	export function once(name: "CoreConfigured", func: CoreConfiguredFunction, priority?: number): void;
	export function once(name: "LevelSelected", func: LevelSelectedFunction, priority?: number): void;
	export function once(name: "DimensionLoaded", func: DimensionLoadedFunction, priority?: number): void;
	export function once(name: "DestroyBlock", func: DestroyBlockFunction, priority?: number): void;
	export function once(name: "DestroyBlockStart", func: DestroyBlockFunction, priority?: number): void;
	export function once(name: "DestroyBlockContinue", func: DestroyBlockContinueFunction, priority?: number): void;
	export function once(name: "BuildBlock", func: BuildBlockFunction, priority?: number): void;
	export function once(name: "BlockChanged", func: BlockChangedFunction, priority?: number): void;
	export function once(name: "ItemUse", func: ItemUseFunction, priority?: number): void;
	export function once(name: "ItemUseLocalServer", func: ItemUseFunction, priority?: number): void;
	export function once(name: "Explosion", func: ExplosionFunction, priority?: number): void;
	export function once(name: "FoodEaten", func: FoodEatenFunction, priority?: number): void;
	export function once(name: "ExpAdd", func: ExpAddFunction, priority?: number): void;
	export function once(name: "ExpLevelAdd", func: ExpLevelAddFunction, priority?: number): void;
	export function once(name: "NativeCommand", func: NativeCommandFunction, priority?: number): void;
	export function once(name: "PlayerAttack", func: PlayerAttackFunction, priority?: number): void;
	export function once(name: "EntityAdded", func: EntityAddedFunction, priority?: number): void;
	export function once(name: "EntityRemoved", func: EntityRemovedFunction, priority?: number): void;
	export function once(name: "EntityDeath", func: EntityDeathFunction, priority?: number): void;
	export function once(name: "EntityHurt", func: EntityHurtFunction, priority?: number): void;
	export function once(name: "EntityInteract", func: EntityInteractFunction, priority?: number): void;
	export function once(name: "ProjectileHit", func: ProjectileHitFunction, priority?: number): void;
	export function once(name: "RedstoneSignal", func: RedstoneSignalFunction, priority?: number): void;
	export function once(name: "PopBlockResources", func: PopBlockResourcesFunction, priority?: number): void;
	export function once(name: "ItemIconOverride", func: ItemIconOverrideFunction, priority?: number): void;
	export function once(name: "ItemNameOverride", func: ItemNameOverrideFunction, priority?: number): void;
	export function once(name: "ItemUseNoTarget", func: ItemUseNoTargetFunction, priority?: number): void;
	export function once(name: "ItemUsingReleased", func: ItemUsingReleasedFunction, priority?: number): void;
	export function once(name: "ItemUsingComplete", func: ItemUsingCompleteFunction, priority?: number): void;
	export function once(name: "ItemDispensed", func: ItemDispensedFunction, priority?: number): void;
	export function once(name: "NativeGuiChanged", func: NativeGuiChangedFunction, priority?: number): void;
	export function once(name: "GenerateChunk", func: GenerateChunkFunction, priority?: number): void;
	/**
		 * @deprecated
		 */
	export function once(name: "GenerateChunkUnderground", func: GenerateChunkFunction, priority?: number): void;
	export function once(name: "GenerateNetherChunk", func: GenerateChunkFunction, priority?: number): void;
	export function once(name: "GenerateEndChunk", func: GenerateChunkFunction, priority?: number): void;
	export function once(name: "GenerateChunkUniversal", func: GenerateChunkFunction, priority?: number): void;
	export function once(name: "GenerateBiomeMap", func: GenerateChunkFunction, priority?: number): void;
	export function once(name: "ReadSaves", func: SavesFunction, priority?: number): void;
	export function once(name: "WriteSaves", func: SavesFunction, priority?: number): void;
	export function once(name: "CustomBlockTessellation", func: CustomBlockTessellationFunction, priority?: number): void;
	export function once(name: "ServerPlayerTick", func: ServerPlayerTickFunction, priority?: number): void;
	export function once(name: "CustomDimensionTransfer", func: CustomDimensionTransferFunction, priority?: number): void;
	export function once(name: "BlockEventEntityInside", func: Block.EntityInsideFunction, priority?: number): void;
	export function once(name: "BlockEventEntityStepOn", func: Block.EntityStepOnFunction, priority?: number): void;
	export function once(name: "BlockEventNeighbourChange", func: Block.NeighbourChangeFunction, priority?: number): void;
	export function once(name: "ConnectingToHost", func: ConnectingToHostFunction, priority?: number): void;
	export function once(name: "DimensionUnloaded", func: DimensionUnloadedFunction, priority?: number): void;
	export function once(name: "LevelPreLeft", func: { (): void }, priority?: number): void;
	export function once(name: "LevelLeft", func: { (): void }, priority?: number): void;
	export function once(name: "ItemUseLocal", func: ItemUseLocalFunction, priority?: number): void;
	export function once(name: "SystemKeyEventDispatched", func: SystemKeyEventDispatchedFunction, priority?: number): void;
	export function once(name: "NavigationBackPressed", func: { (): void }, priority?: number): void;
	export function once(name: "LevelCreated", func: { (): void }, priority?: number): void;
	export function once(name: "LevelDisplayed", func: { (): void }, priority?: number): void;
	export function once(name: "LevelPreLoaded", func: LevelLoadedFunction, priority?: number): void;
	export function once(name: "LevelLoaded", func: LevelLoadedFunction, priority?: number): void;
	export function once(name: "LocalLevelLoaded", func: { (): void }, priority?: number): void;
	export function once(name: "LocalTick", func: { (): void }, priority?: number): void;
	export function once(name: "AppSuspended", func: { (): void }, priority?: number): void;
	export function once(name: "EntityPickUpDrop", func: EntityPickUpDropFunction, priority?: number): void;
	export function once(name: "ServerPlayerLoaded", func: PlayerFunction, priority?: number): void;

	export function once(name: "ServerPlayerLeft", func: PlayerFunction, priority?: number): void;
	export function once(name: "GenerateCustomDimensionChunk", func: GenerateCustomDimensionChunkFunction, priority?: number): void;

	export function once(name: string, callback: Function, priority: number = 10): void {
		add(name, {
			callback, priority,
			once: true
		});
	}

	export function off(name: string, func: Function): void;
	export function off(name: "CraftRecipePreProvided", func: CraftRecipePreProvidedFunction): void;
	export function off(name: "CraftRecipeProvidedFunction", func: CraftRecipeProvidedFunction): void;
	export function off(name: "VanillaWorkbenchCraft", func: VanillaWorkbenchCraftFunction): void;
	export function off(name: "VanillaWorkbenchPostCraft", func: VanillaWorkbenchCraftFunction): void;
	export function off(name: "VanillaWorkbenchRecipeSelected", func: VanillaWorkbenchRecipeSelectedFunction): void;
	export function off(name: "ContainerClosed", func: ContainerClosedFunction): void;
	export function off(name: "ContainerOpened", func: ContainerOpenedFunction): void;
	export function off(name: "CustomWindowOpened", func: CustomWindowOpenedFunction): void;
	export function off(name: "CustomWindowClosed", func: CustomWindowClosedFunction): void;
	export function off(name: "CoreConfigured", func: CoreConfiguredFunction): void;
	export function off(name: "LevelSelected", func: LevelSelectedFunction): void;
	export function off(name: "DimensionLoaded", func: DimensionLoadedFunction): void;
	export function off(name: "DestroyBlock", func: DestroyBlockFunction): void;
	export function off(name: "DestroyBlockStart", func: DestroyBlockFunction): void;
	export function off(name: "DestroyBlockContinue", func: DestroyBlockContinueFunction): void;
	export function off(name: "BuildBlock", func: BuildBlockFunction): void;
	export function off(name: "BlockChanged", func: BlockChangedFunction): void;
	export function off(name: "ItemUse", func: ItemUseFunction): void;
	export function off(name: "ItemUseLocalServer", func: ItemUseFunction): void;
	export function off(name: "Explosion", func: ExplosionFunction): void;
	export function off(name: "FoodEaten", func: FoodEatenFunction): void;
	export function off(name: "ExpAdd", func: ExpAddFunction): void;
	export function off(name: "ExpLevelAdd", func: ExpLevelAddFunction): void;
	export function off(name: "NativeCommand", func: NativeCommandFunction): void;
	export function off(name: "PlayerAttack", func: PlayerAttackFunction): void;
	export function off(name: "EntityAdded", func: EntityAddedFunction): void;
	export function off(name: "EntityRemoved", func: EntityRemovedFunction): void;
	export function off(name: "EntityDeath", func: EntityDeathFunction): void;
	export function off(name: "EntityHurt", func: EntityHurtFunction): void;
	export function off(name: "EntityInteract", func: EntityInteractFunction): void;
	export function off(name: "ProjectileHit", func: ProjectileHitFunction): void;
	export function off(name: "RedstoneSignal", func: RedstoneSignalFunction): void;
	export function off(name: "PopBlockResources", func: PopBlockResourcesFunction): void;
	export function off(name: "ItemIconOverride", func: ItemIconOverrideFunction): void;
	export function off(name: "ItemNameOverride", func: ItemNameOverrideFunction): void;
	export function off(name: "ItemUseNoTarget", func: ItemUseNoTargetFunction): void;
	export function off(name: "ItemUsingReleased", func: ItemUsingReleasedFunction): void;
	export function off(name: "ItemUsingComplete", func: ItemUsingCompleteFunction): void;
	export function off(name: "ItemDispensed", func: ItemDispensedFunction): void;
	export function off(name: "NativeGuiChanged", func: NativeGuiChangedFunction): void;
	export function off(name: "GenerateChunk", func: GenerateChunkFunction): void;
	/**
		 * @deprecated
		 */
	export function off(name: "GenerateChunkUnderground", func: GenerateChunkFunction): void;
	export function off(name: "GenerateNetherChunk", func: GenerateChunkFunction): void;
	export function off(name: "GenerateEndChunk", func: GenerateChunkFunction): void;
	export function off(name: "GenerateChunkUniversal", func: GenerateChunkFunction): void;
	export function off(name: "GenerateBiomeMap", func: GenerateChunkFunction): void;
	export function off(name: "ReadSaves", func: SavesFunction): void;
	export function off(name: "WriteSaves", func: SavesFunction): void;
	export function off(name: "CustomBlockTessellation", func: CustomBlockTessellationFunction): void;
	export function off(name: "ServerPlayerTick", func: ServerPlayerTickFunction): void;
	export function off(name: "CustomDimensionTransfer", func: CustomDimensionTransferFunction): void;
	export function off(name: "BlockEventEntityInside", func: Block.EntityInsideFunction): void;
	export function off(name: "BlockEventEntityStepOn", func: Block.EntityStepOnFunction): void;
	export function off(name: "BlockEventNeighbourChange", func: Block.NeighbourChangeFunction): void;
	export function off(name: "ConnectingToHost", func: ConnectingToHostFunction): void;
	export function off(name: "DimensionUnloaded", func: DimensionUnloadedFunction): void;
	export function off(name: "LevelPreLeft", func: { (): void }): void;
	export function off(name: "LevelLeft", func: { (): void }): void;
	export function off(name: "ItemUseLocal", func: ItemUseLocalFunction): void;
	export function off(name: "SystemKeyEventDispatched", func: SystemKeyEventDispatchedFunction): void;
	export function off(name: "NavigationBackPressed", func: { (): void }): void;
	export function off(name: "LevelCreated", func: { (): void }): void;
	export function off(name: "LevelDisplayed", func: { (): void }): void;
	export function off(name: "LevelPreLoaded", func: LevelLoadedFunction): void;
	export function off(name: "LevelLoaded", func: LevelLoadedFunction): void;
	export function off(name: "LocalLevelLoaded", func: { (): void }): void;
	export function off(name: "LocalTick", func: { (): void }): void;
	export function off(name: "AppSuspended", func: { (): void }): void;
	export function off(name: "EntityPickUpDrop", func: EntityPickUpDropFunction): void;
	export function off(name: "ServerPlayerLoaded", func: PlayerFunction): void;

	export function off(name: "ServerPlayerLeft", func: PlayerFunction): void;
	export function off(name: "GenerateCustomDimensionChunk", func: GenerateCustomDimensionChunkFunction): void;

	export function off(name: string, callback: Function): void {
		eventList[name] = eventList[name].filter(event => event.callback != callback);
	}

	//@ts-ignore
	addCallback = on;
}
