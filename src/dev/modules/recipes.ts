const SmithingTableRecipes = WRAP_JAVA("vsdum.kex.modules.misc.SmithingTableRecipes");


(() => {
    type VanillaSmithingRecipes = { recipes: [ number, number, number ][] }
    const recipes = FileTools.ReadJSON(`${__dir__}/data/vanilla_smithing_recipes.json`) as VanillaSmithingRecipes;
    recipes.recipes.forEach(recipe => SmithingTableRecipes.addRecipe(...recipe));
})();


Recipes.addSmithingTableRecipe = (baseID, additionID, resultID) => SmithingTableRecipes.addRecipe(baseID, additionID, resultID);
Recipes.removeSmithingTableRecipe = (baseID, additionID) => SmithingTableRecipes.removeRecipe(baseID, additionID);

Recipes.getSmithingTableRecipesByResult = resultID => {
    const result = [];
    const iter = SmithingTableRecipes.getRecipesByResult(resultID).iterator();
    while(iter.hasNext()) result.push(iter.next());
    return result;
}

Recipes.getSmithingTableRecipesByBase = baseID => {
    const result = [];
    const iter = SmithingTableRecipes.getRecipesByBase(baseID).iterator();
    while(iter.hasNext()) result.push(iter.next());
    return result;
}

Recipes.getAllSmithingTableRecipes = () => {
    const result = [];
    const iter = SmithingTableRecipes.getAllRecipes().iterator();
    while(iter.hasNext()) result.push(iter.next());
    return result;
}