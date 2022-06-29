package vsdum.kex.modules.misc;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import com.zhekasmirnov.horizon.runtime.logger.Logger;

public class SmithingTableRecipes {
    
    private static native void nativeAddRecipe(int baseID, int additionID, int resultID);
    private static native void nativeRemoveRecipe(int baseID, int additionID);

    public static final class SmithingTableRecipe {

        public final int baseID;
        public final int additionID;
        public final int resultID;

        public SmithingTableRecipe(int baseID, int additionID, int resultID)
        {
            this.baseID = baseID;
            this.additionID = additionID;
            this.resultID = resultID;
        }

        @Override public boolean equals(Object other)
        {
            if(other == null) return false;
            if(other == this) return true;
            if(!(other instanceof SmithingTableRecipe)) return false;
            SmithingTableRecipe recipe = (SmithingTableRecipe) other;
            return this.baseID == recipe.baseID && this.additionID == recipe.additionID && this.resultID == recipe.resultID;
        }

    }

    private static final Map<Integer, Set<SmithingTableRecipe>> recipesByResult = new HashMap<>();
    private static final Map<Integer, Set<SmithingTableRecipe>> recipesByBase = new HashMap<>();
    private static final Set<SmithingTableRecipe> allRecipes = new HashSet<>();

    public static void addRecipe(int baseID, int additionID, int resultID)
    {
        SmithingTableRecipe recipe = new SmithingTableRecipe(baseID, additionID, resultID);
        if(!allRecipes.contains(recipe))
        {
            allRecipes.add(recipe);
            recipesByResult.putIfAbsent(resultID, new HashSet<>());
            recipesByResult.get(resultID).add(recipe);
            recipesByBase.putIfAbsent(baseID, new HashSet<>());
            recipesByBase.get(baseID).add(recipe);
            nativeAddRecipe(baseID, additionID, resultID);
        }
    }

    public static void removeRecipe(int baseID, int additionID)
    {
        if(recipesByBase.containsKey(baseID))
        {
            Iterator<SmithingTableRecipe> iter = recipesByBase.get(baseID).iterator();
            while(iter.hasNext())
            {
                SmithingTableRecipe recipe = iter.next();
                if(recipe.additionID == additionID)
                {
                    allRecipes.remove(recipe);
                    recipesByResult.get(recipe.resultID).remove(recipe);
                    recipesByBase.get(recipe.baseID).remove(recipe);
                    nativeRemoveRecipe(baseID, additionID);
                    break;
                }
            }
        }
    }

    public static Set<SmithingTableRecipe> getRecipesByResult(int resultID)
    {
        return recipesByResult.containsKey(resultID) ? recipesByResult.get(resultID) : new HashSet<>();
    }

    public static Set<SmithingTableRecipe> getRecipesByBase(int baseID)
    {
        return recipesByBase.containsKey(baseID) ? recipesByBase.get(baseID) : new HashSet<>();
    }

    public static Set<SmithingTableRecipe> getAllRecipes()
    {
        return allRecipes;
    }

    public static void printRecipesCount()
    {
        Logger.debug("KEX-SmithingTableRecipes", String.format("Registered in total %d smithing table recipes.", new Object[]{ Integer.valueOf(allRecipes.size()) }));
    }

}
