// const testRender = new Render();
// testRender.getPart("head").addPart("box");
// testRender.setPart("box", [
//     {
//         coords: { x: 0, y: 0, z: 0 },
//         size: { x: 16, y: 16, z: 16 },
//         uv: { x: 0, y: 0 },
//     }
// ], { width: 16, height: 16 });

// let testAnim: Animation.Base = null;

// Callback.addCallback("ItemUse", (coords, item) => {
//     if(testAnim == null) testAnim = new Animation.Base(0, 10, 0);
//     if(item.id == 280) {
//         testAnim.describe({ render: testRender.getID(), skin: "terrain-atlas/test_anim_blue.png" });
//         testAnim.load();
//         testAnim.setSkylightMode();
//     } else testAnim.destroy();
// });


// TextureWorker.createPaintedTexture()
//     .source(`${__dir__}/resources/res/terrain-atlas/`, "test_anim")
//     .color(255, 255, 255)
//     .result(`${__dir__}/resources/res/terrain-atlas/`, "test_anim_blue")
//     .create();

// // @ts-ignore
// com.zhekasmirnov.horizon.launcher.env.AssetPatch.addSingleOverride("resource_packs/vanilla/terrain-atlas/test_anim_blue.png", `${__dir__}/resources/res/terrain-atlas/test_anim_blue.png`);

// ItemsModule.setDynamicFoodValues(VanillaItemID.sweet_berries, (stack) => {
//     return new FoodItemComponent.Builder()
//         .nutrition(Math.floor(Math.random() * 3) + 1)
//         .saturationMod(ESaturationModifier.NORMAL)
//         .alwaysEat();
// });

type LoadedRectangle = vsdum.kex.modules.ChunksModule.LoadedRectangle;
type LoadedCircle = vsdum.kex.modules.ChunksModule.LoadedCircle;




var testRectangle: LoadedRectangle;
var testCircle: LoadedCircle;
var testChunk: LoadedRectangle;

Callback.on("LevelDisplayed", () => {
    const dimension = Player.getDimension();
    testRectangle = ChunksModule.addLoadedRectangle(dimension, "test_rectangle")
        .start(30, 30)
        .end(50, 50)
        .load();
    testCircle = ChunksModule.addLoadedCircle(dimension, "test_circle")
        .center(8, 8)
        .radius(128)
        .load();
    testChunk = ChunksModule.addLoadedChunk(dimension, "test_chunk", 16, 16)
        .load();
});

Callback.on("ItemUse", (coords, item) => {
    if(item.id == 280) {
        testRectangle.unload();
        testCircle.unload();
        testChunk.unload();
    }
});