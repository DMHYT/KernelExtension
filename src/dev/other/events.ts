const ModCallbacks = WRAP_JAVA("vsdum.kex.common.ModCallbacks");

ModCallbacks.specifyModDir(`${__dir__}/`);
Callback.addCallback("LevelDisplayed", () => ModCallbacks.onLevelDisplayed());
Callback.addCallback("LevelLeft", () => ModCallbacks.onLevelLeft());
Callback.addCallback("NativeGuiChanged", screenName => ModCallbacks.onNativeGuiChanged(screenName));
Callback.addCallback("LocalTick", () => ModCallbacks.onLocalTick());
Callback.addCallback("ItemIconOverride", item => ModCallbacks.onIconOverride(item.id));
Callback.addCallback("ModsLoaded", () => ModCallbacks.onModsLoaded());