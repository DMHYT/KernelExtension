const AddonUtils = WRAP_JAVA("vsdum.kex.util.AddonUtils");

// @ts-ignore
Callback.addCallback("LevelDisplayed", () => AddonUtils.onLevelDisplayed());