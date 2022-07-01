package vsdum.kex.common;

import vsdum.kex.KernelExtension;
import vsdum.kex.modules.LootModule;
import vsdum.kex.modules.misc.SmithingTableRecipes;
import vsdum.kex.util.AddonUtils;
import vsdum.kex.util.ItemAnimHelper;

public class ModCallbacks {
    
    public static void onLevelDisplayed()
    {
        AddonUtils.onLevelDisplayed();
        LootModule.onLevelDisplayed();
        SmithingTableRecipes.printRecipesCount();
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

}
