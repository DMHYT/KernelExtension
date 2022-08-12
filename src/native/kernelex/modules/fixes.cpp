#include <stl/string>
#include <stl.h>

#include <hook.h>
#include <symbol.h>
#include <logger.h>

#include "fixes.hpp"


std::unordered_map<std::string, unsigned int> KEXFixesModule::blockSoundTypes {
    { "normal", 0 },
    { "gravel", 1 },
    { "wood", 2 },
    { "grass", 3 },
    { "metal", 4 },
    { "stone", 5 },
    { "cloth", 6 },
    { "glass", 7 },
    { "sand", 8 },
    { "snow", 9 },
    { "ladder", 10 },
    { "anvil", 11 },
    { "slime", 12 },
    { "silent", 13 },
    { "itemframe", 14 },
    { "turtle_egg", 15 },
    { "bamboo", 16 },
    { "bamboo_sapling", 17 },
    { "lantern", 18 },
    { "scaffolding", 19 },
    { "sweet_berry_bush", 20 },
    { "soul_sand", 21 },
    { "soul_soil", 22 },
    { "nylium", 23 },
    { "roots", 24 },
    { "fungus", 25 },
    { "stem", 26 },
    { "shroomlight", 27 },
    { "basalt", 28 },
    { "bone_block", 29 },
    { "nether_brick", 30 },
    { "netherrack", 31 },
    { "nether_sprouts", 32 },
    { "nether_wart", 33 },
    { "nether_gold_ore", 34 },
    { "ancient_debris", 35 },
    { "honey_block", 36 },
    { "honeycomb_block", 37 },
    { "coral", 38 },
    { "netherite", 39 },
    { "lodestone", 40 },
    { "chain", 41 },
    { "vines", 42 },
    { "default", 43 },
    { "undefined", 44 }
};

std::unordered_map<std::string, unsigned int> KEXFixesModule::levelSoundEventNameToType {
    { "item.use.on", 0 },
    { "hit", 1 },
    { "step", 2 },
    { "fly", 3 },
    { "jump", 4 },
    { "break", 5 },
    { "place", 6 },
    { "heavy.step", 7 },
    { "gallop", 8 },
    { "fall", 9 },
    { "ambient", 10 },
    { "ambient.baby", 11 },
    { "ambient.in.water", 12 },
    { "breathe", 13 },
    { "death", 14 },
    { "death.in.water", 15 },
    { "death.to.zombie", 16 },
    { "hurt", 17 },
    { "hurt.in.water", 18 },
    { "mad", 19 },
    { "boost", 20 },
    { "bow", 21 },
    { "squish.big", 22 },
    { "squish.small", 23 },
    { "fall.big", 24 },
    { "fall.small", 25 },
    { "splash", 26 },
    { "fizz", 27 },
    { "flap", 28 },
    { "swim", 29 },
    { "drink", 30 },
    { "eat", 31 },
    { "takeoff", 32 },
    { "shake", 33 },
    { "plop", 34 },
    { "land", 35 },
    { "saddle", 36 },
    { "armor", 37 },
    { "mob.armor_stand.place", 38 },
    { "add.chest", 39 },
    { "throw", 40 },
    { "attack", 41 },
    { "attack.nodamage", 42 },
    { "attack.strong", 43 },
    { "warn", 44 },
    { "shear", 45 },
    { "milk", 46 },
    { "thunder", 47 },
    { "explode", 48 },
    { "fire", 49 },
    { "ignite", 50 },
    { "fuse", 51 },
    { "stare", 52 },
    { "spawn", 53 },
    { "shoot", 54 },
    { "break.block", 55 },
    { "launch", 56 },
    { "blast", 57 },
    { "large.blast", 58 },
    { "twinkle", 59 },
    { "remedy", 60 },
    { "unfect", 61 },
    { "levelup", 62 },
    { "bow.hit", 63 },
    { "bullet.hit", 64 },
    { "extinguish.fire", 65 },
    { "item.fizz", 66 },
    { "chest.open", 67 },
    { "chest.closed", 68 },
    { "shulkerbox.open", 69 },
    { "shulkerbox.closed", 70 },
    { "enderchest.open", 71 },
    { "enderchest.closed", 72 },
    { "power.on", 73 },
    { "power.off", 74 },
    { "attach", 75 },
    { "detach", 76 },
    { "deny", 77 },
    { "tripod", 78 },
    { "pop", 79 },
    { "drop.slot", 80 },
    { "note", 81 },
    { "thorns", 82 },
    { "piston.in", 83 },
    { "piston.out", 84 },
    { "portal", 85 },
    { "water", 86 },
    { "lava.pop", 87 },
    { "lava", 88 },
    { "burp", 89 },
    { "bucket.fill.water", 90 },
    { "bucket.fill.lava", 91 },
    { "bucket.empty.water", 92 },
    { "bucket.empty.lava", 93 },
    { "armor.equip_chain", 94 },
    { "armor.equip_diamond", 95 },
    { "armor.equip_generic", 96 },
    { "armor.equip_gold", 97 },
    { "armor.equip_iron", 98 },
    { "armor.equip_leather", 99 },
    { "armor.equip_elytra", 100 },
    { "record.13", 101 },
    { "record.cat", 102 },
    { "record.blocks", 103 },
    { "record.chirp", 104 },
    { "record.far", 105 },
    { "record.mall", 106 },
    { "record.mellohi", 107 },
    { "record.stal", 108 },
    { "record.strad", 109 },
    { "record.ward", 110 },
    { "record.11", 111 },
    { "record.wait", 112 },    
    { "flop", 114 },
    { "guardian.flop", 114 },
    { "elderguardian.curse", 115 },
    { "mob.warning", 116 },
    { "mob.warning.baby", 117 },
    { "teleport", 118 },
    { "shulker.open", 119 },
    { "shulker.close", 120 },
    { "haggle", 121 },
    { "haggle.yes", 122 },
    { "haggle.no", 123 },
    { "haggle.idle", 124 },
    { "chorusgrow", 125 },
    { "chorusdeath", 126 },
    { "glass", 127 },
    { "potion.brewed", 128 },
    { "cast.spell", 129 },
    { "prepare.attack", 130 },
    { "prepare.summon", 131 },
    { "prepare.wololo", 132 },
    { "fang", 133 },
    { "charge", 134 },
    { "camera.take_picture", 135 },
    { "leashknot.place", 136 },
    { "leashknot.break", 137 },
    { "growl", 138 },
    { "whine", 139 },
    { "pant", 140 },
    { "purr", 141 },
    { "purreow", 142 },
    { "death.min.volume", 143 },
    { "death.mid.volume", 144 },
    { "imitate.blaze", 145 },
    { "imitate.cave_spider", 146 },
    { "imitate.creeper", 147 },
    { "imitate.elder_guardian", 148 },
    { "imitate.ender_dragon", 149 },
    { "imitate.enderman", 150 },
    { "imitate.evocation_illager", 152 },
    { "imitate.ghast", 153 },
    { "imitate.husk", 154 },
    { "imitate.illusion_illager", 155 },
    { "imitate.magma_cube", 156 },
    { "imitate.polar_bear", 157 },
    { "imitate.shulker", 158 },
    { "imitate.silverfish", 159 },
    { "imitate.skeleton", 160 },
    { "imitate.slime", 161 },
    { "imitate.spider", 162 },
    { "imitate.stray", 163 },
    { "imitate.vex", 164 },
    { "imitate.vindication_illager", 165 },
    { "imitate.witch", 166 },
    { "imitate.wither", 167 },
    { "imitate.wither_skeleton", 168 },
    { "imitate.wolf", 169 },
    { "imitate.zombie", 170 },
    { "imitate.zombie_pigman", 171 },
    { "imitate.zombie_villager", 172 },
    { "block.end_portal_frame.fill", 173 },
    { "block.end_portal.spawn", 174 },
    { "random.anvil_use", 175 },
    { "bottle.dragonbreath", 176 },
    { "portal.travel", 177 },
    { "item.trident.hit", 178 },
    { "item.trident.return", 179 },
    { "item.trident.riptide_1", 180 },
    { "item.trident.riptide_2", 181 },
    { "item.trident.riptide_3", 182 },
    { "item.trident.throw", 183 },
    { "item.trident.thunder", 184 },
    { "item.trident.hit_ground", 185 },
    { "default", 186 },
    { "block.fletching_table.use", 187 },
    { "elemconstruct.open", 188 },
    { "icebomb.hit", 189 },
    { "balloonpop", 190 },
    { "lt.reaction.icebomb", 191 },
    { "lt.reaction.bleach", 192 },
    { "lt.reaction.epaste", 193 },
    { "lt.reaction.epaste2", 194 },
    { "lt.reaction.fertilizer", 195 },
    { "lt.reaction.fireball", 196 },
    { "lt.reaction.mgsalt", 197 },
    { "lt.reaction.miscfire", 198 },
    { "lt.reaction.fire", 203 },
    { "lt.reaction.miscexplosion", 204 },
    { "lt.reaction.miscmystical", 205 },
    { "lt.reaction.miscmystical2", 206 },
    { "lt.reaction.product", 207 },
    { "sparkler.use", 208 },
    { "glowstick.use", 209 },
    { "sparkler.active", 210 },
    { "convert_to_drowned", 211 },
    { "bucket.fill.fish", 212 },
    { "bucket.empty.fish", 213 },
    { "bubble.up", 214 },
    { "bubble.down", 215 },
    { "bubble.pop", 216 },
    { "bubble.upinside", 217 },
    { "bubble.downinside", 218 },
    { "hurt.baby", 219 },
    { "death.baby", 220 },
    { "step.baby", 221 },
    { "born", 223 },
    { "block.turtle_egg.break", 224 },
    { "block.turtle_egg.crack", 225 },
    { "block.turtle_egg.hatch", 226 },
    { "lay_egg", 227 },
    { "block.turtle_egg.attack", 228 },
    { "beacon.activate", 229 },
    { "beacon.ambient", 230 },
    { "beacon.deactivate", 231 },
    { "beacon.power", 232 },
    { "conduit.activate", 233 },
    { "conduit.ambient", 234 },
    { "conduit.attack", 235 },
    { "conduit.deactivate", 236 },
    { "conduit.short", 237 },
    { "swoop", 238 },
    { "block.bamboo_sapling.place", 239 },
    { "presneeze", 240 },
    { "sneeze", 241 },
    { "ambient.tame", 242 },
    { "scared", 243 },
    { "block.scaffolding.climb", 244 },
    { "crossbow.loading.start", 245 },
    { "crossbow.loading.middle", 246 },
    { "crossbow.loading.end", 247 },
    { "crossbow.shoot", 248 },
    { "crossbow.quick_charge.start", 249 },
    { "crossbow.quick_charge.middle", 250 },
    { "crossbow.quick_charge.end", 251 },
    { "ambient.aggressive", 252 },
    { "ambient.worried", 253 },
    { "cant_breed", 254 },
    { "item.shield.block", 255 },
    { "item.book.put", 256 },
    { "block.grindstone.use", 257 },
    { "block.bell.hit", 258 },
    { "block.campfire.crackle", 259 },
    { "block.sweet_berry_bush.hurt", 262 },
    { "block.sweet_berry_bush.pick", 263 },
    { "block.cartography_table.use", 264 },
    { "block.stonecutter.use", 265 },
    { "block.composter.empty", 266 },
    { "block.composter.fill", 267 },
    { "block.composter.fill_success", 268 },
    { "block.composter.ready", 269 },
    { "roar", 260 },
    { "stun", 261 },
    { "block.barrel.open", 270 },
    { "block.barrel.close", 271 },
    { "raid.horn", 272 },
    { "block.loom.use", 273 },
    { "ambient.in.raid", 274 },
    { "ui.cartography_table.take_result", 275 },
    { "ui.stonecutter.take_result", 276 },
    { "ui.loom.take_result", 277 },
    { "block.smoker.smoke", 278 },
    { "block.blastfurnace.fire_crackle", 279 },
    { "block.smithing_table.use", 280 },
    { "screech", 281 },
    { "sleep", 282 },
    { "block.furnace.lit", 283 },
    { "convert_mooshroom", 284 },
    { "milk_suspiciously", 285 },
    { "celebrate", 286 },
    { "jump.prevent", 287 },
    { "ambient.pollinate", 288 },
    { "block.beehive.drip", 289 },
    { "block.beehive.enter", 290 },
    { "block.beehive.exit", 291 },
    { "block.beehive.work", 292 },
    { "block.beehive.shear", 293 },
    { "drink.honey", 294 },
    { "ambient.cave", 295 },
    { "retreat", 296 },
    { "converted_to_zombified", 297 },
    { "admire", 298 },
    { "step_lava", 299 },
    { "tempt", 300 },
    { "panic", 301 },
    { "angry", 302 },
    { "ambient.warped_forest.mood", 303 },
    { "ambient.soulsand_valley.mood", 304 },
    { "ambient.nether_wastes.mood", 305 },
    { "respawn_anchor.basalt_deltas.mood", 306 },
    { "ambient.crimson_forest.mood", 307 },
    { "respawn_anchor.charge", 308 },
    { "respawn_anchor.deplete", 309 },
    { "respawn_anchor.set_spawn", 310 },
    { "respawn_anchor.ambient", 311 },
    { "particle.soul_escape.quiet", 312 },
    { "particle.soul_escape.loud", 313 },
    { "record.pigstep", 314 },
    { "lodestone_compass.link_compass_to_lodestone", 315 },
    { "smithing_table.use", 316 },
    { "armor.equip_netherite", 317 },
    { "undefined", 318 }
};
std::unordered_map<unsigned int, std::string> KEXFixesModule::levelSoundEventTypeToName;

unsigned int KEXFixesModule::nextBlockSoundType = 2048;
unsigned int KEXFixesModule::nextLevelSoundEventType = 4096;


void KEXFixesModule::initialize() {

    for(auto iter = levelSoundEventNameToType.begin(); iter != levelSoundEventNameToType.end(); iter++) {
        levelSoundEventTypeToName.emplace(iter->second, iter->first);
    }

    DLHandleManager::initializeHandle("libminecraftpe.so", "mcpe");

    HookManager::addCallback(
        SYMBOL("mcpe", "_Z24BlockSoundTypeFromStringRKNSt6__ndk112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE"),
        LAMBDA((HookManager::CallbackController* controller, const stl::string& type), {
            controller->replace();
            auto found = blockSoundTypes.find(type.c_str());
            if(found != blockSoundTypes.end()) {
                return found->second;
            }
            Logger::debug("KEX-FixesModule", "Successfully assigned numeric ID %u to custom block sound type %s", nextBlockSoundType, type.c_str());
            blockSoundTypes.emplace(type.c_str(), nextBlockSoundType);
            return nextBlockSoundType++;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );
    
    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN18LevelSoundEventMap5getIdERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE"),
        LAMBDA((HookManager::CallbackController* controller, const stl::string& type), {
            controller->replace();
            auto found = levelSoundEventNameToType.find(type.c_str());
            if(found != levelSoundEventNameToType.end()) {
                return found->second;
            }
            Logger::debug("KEX-FixesModule", "Successfully assigned numeric ID %u to custom level sound event %s", nextLevelSoundEventType, type.c_str());
            levelSoundEventNameToType.emplace(type.c_str(), nextLevelSoundEventType);
            levelSoundEventTypeToName.emplace(nextLevelSoundEventType, type.c_str());
            return nextLevelSoundEventType++;
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

    HookManager::addCallback(
        SYMBOL("mcpe", "_ZN18LevelSoundEventMap7getNameE15LevelSoundEvent"),
        LAMBDA((HookManager::CallbackController* controller, unsigned int type), {
            controller->replace();
            auto found = levelSoundEventTypeToName.find(type);
            if(found != levelSoundEventTypeToName.end()) {
                return (const stl::string&) found->second;
            }
            return (const stl::string&) "undefined";
        }, ),
        HookManager::CALL | HookManager::LISTENER | HookManager::CONTROLLER | HookManager::RESULT
    );

}