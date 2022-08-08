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


IDRegistry.genBlockID("testNativeTileBlock");
Block.createBlock("testNativeTileBlock", [ { name: "Test Native Tile Block", texture: [[ "aaa", 0 ]], inCreative: true } ]);
// @ts-ignore
MAIN.registerCustomTile(BlockID.testNativeTileBlock);