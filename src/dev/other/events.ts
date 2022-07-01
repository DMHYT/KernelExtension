const ModCallbacks = WRAP_JAVA("vsdum.kex.common.ModCallbacks");

Callback.addCallback("LevelDisplayed", () => ModCallbacks.onLevelDisplayed());
Callback.addCallback("NativeGuiChanged", screenName => ModCallbacks.onNativeGuiChanged(screenName));
Callback.addCallback("LocalTick", () => ModCallbacks.onLocalTick());
Callback.addCallback("ItemIconOverride", item => ModCallbacks.onIconOverride(item.id));