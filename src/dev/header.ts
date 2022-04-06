const MAIN = WRAP_JAVA("vsdum.kex.KernelExtension");
const AddonUtils = WRAP_JAVA("vsdum.kex.util.AddonUtils");

// @ts-ignore
Callback.addCallback("LevelDisplayed", () => AddonUtils.onLevelDisplayed());

// @ts-ignore
Callback.addCallback("NativeGuiChanged", screen => screen === "sign_screen" && MAIN.onSignOpen());