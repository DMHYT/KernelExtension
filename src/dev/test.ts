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


// var __SIGNAL_STRENGTH__: number = 0;

// IDRegistry.genBlockID("testBlock");
// Block.createBlock("testBlock", [{name: "Test Block", texture: [["yyyy", 0]], inCreative: true}]);
// Block.registerClickFunction(BlockID.testBlock, (coords, item, block, player) => {
//     if(Entity.getSneaking(player)) __SIGNAL_STRENGTH__--;
//     else __SIGNAL_STRENGTH__++;
//     __SIGNAL_STRENGTH__ = __SIGNAL_STRENGTH__ < 0 ? 0 : __SIGNAL_STRENGTH__ > 15 ? 15 : __SIGNAL_STRENGTH__;
// });
// Block.registerComparatorSignalFunctionForID(BlockID.testBlock, () => __SIGNAL_STRENGTH__);


// IDRegistry.genBlockID("testLightBlock");
// Block.createBlock("testLightBlock", (() => {
//     const variations: Block.BlockVariation[] = [];
//     for(let i = 0; i < 16; i++)
//         variations.push({ name: `Test Light Block ${i}`, texture: [["yyyy", 0]], inCreative: true });
//     return variations;
// })());
// for(let i = 0; i < 16; i++) Block.setLightLevel(BlockID.testLightBlock, i, i);