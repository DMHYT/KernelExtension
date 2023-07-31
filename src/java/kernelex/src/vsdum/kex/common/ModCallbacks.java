package vsdum.kex.common;

import vsdum.kex.KernelExtension;
import vsdum.kex.japi.blocks.BlockRegistry;
import vsdum.kex.japi.config.ConfigManager;
import vsdum.kex.japi.internal.ResourceManager;
import vsdum.kex.japi.internal.block.model.BlockModelManager;
import vsdum.kex.modules.LootModule;
import vsdum.kex.modules.misc.SmithingTableRecipes;
import vsdum.kex.modules.tileentity.TileEntityData;
import vsdum.kex.natives.I18n;
import vsdum.kex.util.AddonUtils;
import vsdum.kex.util.ItemAnimHelper;
import vsdum.kex.util.LangInjector;

public class ModCallbacks {

    private static String modDir = "";

    public static void specifyModDir(String dir)
    {
        modDir = dir;
        I18n.addLangDir(modDir + "data/lang/");
    }
    
    public static void onLevelDisplayed()
    {
        BlockModelManager.onLevelDisplayed();
        LootModule.onLevelDisplayed();
        SmithingTableRecipes.printRecipesCount();
    }

    public static void onLevelSelected()
    {
        ConfigManager.onLevelSelected();
    }

    public static void onLevelLeft()
    {
        TileEntityData.onLevelLeft();
        ConfigManager.onLevelLeft();
    }

    public static void onNativeGuiChanged(String screenName)
    {
        if(screenName.equals("sign_screen"))
        {
            KernelExtension.onSignOpen();
        }
    }

    public static void onLocalTick()
    {
        ItemAnimHelper.onLocalTick();
    }

    public static void onIconOverride(int id)
    {
        ItemAnimHelper.onIconOverride(id);
    }

    public static void onModsLoaded()
    {
        AddonUtils.onModsLoaded();
        LangInjector.run(modDir + "data/lang/");
        ResourceManager.onModsLoaded();
        BlockRegistry.onModsLoaded();
        I18n.onModsLoaded();
        ConfigManager.init();
    }

}
