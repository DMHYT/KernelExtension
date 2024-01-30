/// <reference path="core-engine.d.ts" />


declare type jstring = java.lang.String;
declare type any_string = string | jstring;


declare module vsdum {
    export module kex {
        export module util {
            export class ItemFactoryHelper extends java.lang.Object {
                static class: java.lang.Class<ItemFactoryHelper>;
                static killItem(id: number): Nullable<ItemFactoryInterface>;
            }
            interface ItemFactoryInterface {
                readonly nameId: jstring;
                readonly nameToDisplay: jstring;
                readonly iconName: jstring;
                readonly iconIndex: number;
                readonly stack: number;
                applyOldFactoryProperties(id: number): void;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.util.ItemFactoryHelper"): typeof vsdum.kex.util.ItemFactoryHelper;

declare module vsdum {
    export module kex {
        export module util {
            export module mcmath {
                export class Vec2f extends java.lang.Object {
                    static class: java.lang.Class<Vec2f>;
                    static readonly ZERO: Vec2f;
                    static readonly ONE: Vec2f;
                    static readonly UNIT_X: Vec2f;
                    static readonly NEGATIVE_UNIT_X: Vec2f;
                    static readonly UNIT_Y: Vec2f;
                    static readonly NEGATIVE_UNIT_Y: Vec2f;
                    static readonly MAX: Vec2f;
                    static readonly MIN: Vec2f;
                    readonly x: number;
                    readonly y: number;
                    constructor(x: number, y: number);
                }
                export class Vec3d extends java.lang.Object {
                    static class: java.lang.Class<Vec3d>;
                    static readonly ZERO: Vec3d;
                    readonly x: number;
                    readonly y: number;
                    readonly z: number;
                    constructor(x: number, y: number, z: number);
                    constructor(vector: Vec3d);
                    subtractReverse(vec: Vec3d): Vec3d;
                    normalize(): Vec3d;
                    dotProduct(vec: Vec3d): number;
                    crossProduct(vec: Vec3d): Vec3d;
                    subtract(vec: Vec3d): Vec3d;
                    subtract(x: number, y: number, z: number): Vec3d;
                    add(vec: Vec3d): Vec3d;
                    addVector(x: number, y: number, z: number): Vec3d;
                    distanceTo(vec: Vec3d): number;
                    squareDistanceTo(vec: Vec3d): number;
                    squareDistanceTo(x: number, y: number, z: number): number;
                    scale(factor: number): Vec3d;
                    lengthVector(): number;
                    lengthSquared(): number;
                    getIntermediateWithXValue(vec: Vec3d, x: number): Nullable<Vec3d>;
                    getIntermediateWithYValue(vec: Vec3d, y: number): Nullable<Vec3d>;
                    getIntermediateWithZValue(vec: Vec3d, z: number): Nullable<Vec3d>;
                    rotatePitch(pitch: number): Vec3d;
                    rotateYaw(yaw: number): Vec3d;
                    static fromPitchYawVector(pitchYawVec: Vec2f): Vec3d;
                    static fromPitchYaw(pitch: number, yaw: number): Vec3d;
                }
                export class Vec3i extends java.lang.Object implements java.lang.Comparable<Vec3i> {
                    static class: java.lang.Class<Vec3i>;
                    static readonly NULL_VECTOR: Vec3i;
                    readonly x: number;
                    readonly y: number;
                    readonly z: number;
                    readonly vec: Vec3d;
                    readonly side: number;
                    constructor(x: number, y: number, z: number, side: number, vec: Vec3d);
                    constructor(x: number, y: number, z: number, side: number, dx: number, dy: number, dz: number);
                    constructor(x: number, y: number, z: number);
                    compareTo(vec: Vec3i): number;
                    getX(): number;
                    getY(): number;
                    getZ(): number;
                    crossProduct(vec: Vec3i): Vec3i;
                    getDistance(x: number, y: number, z: number): number;
                    distanceSq(toX: number, toY: number, toZ: number): number;
                    distanceSqToCenter(x: number, y: number, z: number): number;
                    distanceSq(to: Vec3i): number;
                }
                export class Direction extends java.lang.Object {
                    static class: java.lang.Class<Direction>;
                    private constructor(index: number, opposite: number, horizontalIndex: number, name: any_string, axisDirection: Direction.AxisDirection, axis: Direction.Axis, directionVec: Vec3i);
                    getIndex(): number;
                    getAxisDirection(): Direction.AxisDirection;
                    getOpposite(): Direction;
                    rotateAround(axis: Direction.Axis): Direction;
                    rotateY(): Direction;
                    rotateX(): Direction;
                    rotateZ(): Direction;
                    rotateYCCW(): Direction;
                    getFrontOffsetX(): number;
                    getFrontOffsetY(): number;
                    getFrontOffsetZ(): number;
                    getAxis(): Direction.Axis;
                    static byName(name: any_string): Nullable<Direction>;
                    static getFront(index: number): Direction;
                    static getHorizontal(index: number): Direction;
                    static fromAngle(angle: number): Direction;
                    getHorizontalAngle(): number;
                    static random(rand: java.util.Random): Direction;
                    static getFacingFromVector(x: number, y: number, z: number): Direction;
                    static getFacingFromAxis(axisDir: Direction.AxisDirection, axis: Direction.Axis): Direction;
                    getDirectionVec(): Vec3i;
                    getClockWise(axis: Direction.Axis): Direction;
                    getCounterClockWise(axis: Direction.Axis): Direction;
                    getClockWise(): Direction;
                    getCounterClockWise(): Direction;
                    getClockWiseX(): Direction;
                    getCounterClockWiseX(): Direction;
                    getClockWiseZ(): Direction;
                    getCounterClockWiseZ(): Direction;
                }
                export module Direction {
                    export const DOWN: Direction;
                    export const UP: Direction;
                    export const NORTH: Direction;
                    export const SOUTH: Direction;
                    export const WEST: Direction;
                    export const EAST: Direction;
                    export class Axis extends java.lang.Object {
                        static class: java.lang.Class<Axis>;
                        static readonly X: Axis;
                        static readonly Y: Axis;
                        static readonly Z: Axis;
                        private constructor(name: any_string, plane: Plane);
                        static byName(name: any_string): Nullable<Axis>;
                        isVertical(): boolean;
                        isHorizontal(): boolean;
                        apply(to: Nullable<Direction>): boolean;
                        test(dir: Direction): boolean;
                        getPlane(): Plane;
                    }
                    export class AxisDirection extends java.lang.Object {
                        static class: java.lang.Class<AxisDirection>;
                        static readonly POSITIVE: AxisDirection;
                        static readonly NEGATIVE: AxisDirection;
                        private constructor(offset: number, description: any_string);
                        getOffset(): number;
                    }
                    export class Plane extends java.lang.Object {
                        static class: java.lang.Class<Plane>;
                        static readonly HORIZONTAL: Plane;
                        static readonly VERTICAL: Plane;
                        facings(): Direction[];
                        random(rand: java.util.Random): Direction;
                        apply(dir: Nullable<Direction>): boolean;
                        test(dir: Direction): boolean;
                        iterator(): java.util.Iterator<Direction>;
                    }
                }
                export class BlockPos extends Vec3i {
                    static class: java.lang.Class<BlockPos>;
                    static readonly ORIGIN: BlockPos;
                    constructor(x: number, y: number, z: number, side: number, vec: Vec3d);
                    constructor(x: number, y: number, z: number, side: number, dx: number, dy: number, dz: number);
                    constructor(x: number, y: number, z: number);
                    constructor(vec: Vec3d);
                    constructor(vec: Vec3i);
                    add(x: number, y: number, z: number): BlockPos;
                    add(vec: Vec3i): BlockPos;
                    subtract(vec: Vec3i): BlockPos;
                    up(): BlockPos;
                    up(n: number): BlockPos;
                    down(): BlockPos;
                    down(n: number): BlockPos;
                    north(): BlockPos;
                    north(n: number): BlockPos;
                    south(): BlockPos;
                    south(n: number): BlockPos;
                    west(): BlockPos;
                    west(n: number): BlockPos;
                    east(): BlockPos;
                    east(n: number): BlockPos;
                    offset(facing: Direction): BlockPos;
                    offset(facing: Direction, n: number): BlockPos;
                    crossProduct(vec: Vec3i): BlockPos;
                    toLong(): number;
                    static fromLong(serialized: number): BlockPos;
                }
                export class Rotation extends java.lang.Object {
                    static class: java.lang.Class<Rotation>;
                    static readonly NONE: Rotation;
                    static readonly CLOCKWISE_90: Rotation;
                    static readonly CLOCKWISE_180: Rotation;
                    static readonly COUNTERCLOCKWISE_90: Rotation;
                    private constructor();
                    getRotated(rot: Rotation): Rotation;
                    rotate(dir: Direction): Direction;
                    // TODO rotate(i: number, j: number): number;
                    getRandom(rand: java.util.Random): Rotation;
                    getShuffled(rand: java.util.Random): java.util.List<Rotation>;
                }
                export class Mirror extends java.lang.Object {
                    static class: java.lang.Class<Mirror>;
                    static readonly NONE: Mirror;
                    static readonly LEFT_RIGHT: Mirror;
                    static readonly FRONT_BACK: Mirror;
                    private constructor();
                    // TODO mirror(k: number, l: number): number;
                    getRotation(dir: Direction): Rotation;
                    mirror(dir: Direction): Direction;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.util.mcmath.Vec2f"): typeof vsdum.kex.util.mcmath.Vec2f;
declare function WRAP_JAVA(clazz: "vsdum.kex.util.mcmath.Vec3d"): typeof vsdum.kex.util.mcmath.Vec3d;
declare function WRAP_JAVA(clazz: "vsdum.kex.util.mcmath.Vec3i"): typeof vsdum.kex.util.mcmath.Vec3i;
declare function WRAP_JAVA(clazz: "vsdum.kex.util.mcmath.Direction"): typeof vsdum.kex.util.mcmath.Direction;
declare function WRAP_JAVA(clazz: "vsdum.kex.util.mcmath.BlockPos"): typeof vsdum.kex.util.mcmath.BlockPos;
declare function WRAP_JAVA(clazz: "vsdum.kex.util.mcmath.Rotation"): typeof vsdum.kex.util.mcmath.Rotation;
declare function WRAP_JAVA(clazz: "vsdum.kex.util.mcmath.Mirror"): typeof vsdum.kex.util.mcmath.Mirror;

declare module vsdum {
    export module kex {
        export module common {
            export class INativeInterface extends java.lang.Object {
                static class: java.lang.Class<INativeInterface>;
                getPointer(): number;
                constructor();
                constructor(impl: { getPointer: () => number });
            }
        }
    }
}

declare module vsdum {
    export module kex {
        export module natives {
            export class Actor extends common.INativeInterface {
                static class: java.lang.Class<Actor>;
                static isValid(entityUID: number): boolean;
                constructor(entity: number);
                isBreakingObstruction(): boolean;
                setBreakingObstruction(breaking: boolean): void;
                isDancing(): boolean;
                setDancing(dancing: boolean): void;
                healEffects(value: number): void;
                getColor(): number;
                setColor(color: number): void;
                getColor2(): number;
                setColor2(color: number): void;
                isInClouds(): boolean;
                hasUniqueID(): boolean;
                getUniqueID(): number;
                getHurtDir(): number;
                setHurtDir(hurtDir: number): void;
                isEnchanted(): boolean;
                setEnchanted(enchanted: boolean): void;
                getMarkVariant(): number;
                setMarkVariant(variant: number): void;
                hasDimension(): boolean;
                canChangeDimensions(): boolean;
                getDimensionId(): number;
                getDimension(): Nullable<Dimension>;
                wasLastHitByPlayer(): boolean;
                isDelayedAttacking(): boolean;
                setDelayedAttacking(delayed: boolean): void;
                canBeginOrContinueClimbingLadder(): boolean;
                getStructuralIntegrity(): number;
                setStructuralIntegrity(integrity: number): void;
                hasLevel(): boolean;
                getLevel(): Nullable<Level>;
                getCameraDistance(): number;
                setCameraDistance(distance: number): void;
                isDoorOpener(): boolean;
                setDoorOpener(opener: boolean): void;
                hasType(type: number): boolean;
                isType(type: number): boolean;
                removeEffectNoUpdate(id: number): void;
                getEffect(effect: MobEffect): Nullable<MobEffectInstance>;
                getEffect(effectId: number): Nullable<MobEffectInstance>;
                getActiveEffectCount(): number;
                hasEffect(effect: MobEffect): boolean;
                hasEffect(effectId: number): boolean;
                hasAnyVisibleEffects(): boolean;
                removeEffect(id: number): void;
                hasAnyEffects(): boolean;
                removeAllEffects(): void;
                addEffect(effectInstance: MobEffectInstance): void;
                removeEffects(harmful: boolean, harmless: boolean): void;
                isInSnow(): boolean;
                canMate(mate: Actor): boolean;
                hasTickingArea(): boolean;
                getIsOnScreen(): boolean;
                setIsOnScreen(onScreen: boolean): void;
                isOverScaffolding(): boolean;
                isInScaffolding(): boolean;
                shouldOrphan(world: BlockSource): boolean;
                isOrphan(): boolean;
                isPredictedMovementEnabled(): boolean;
                isInRain(): boolean;
                isWASDControlled(): boolean;
                setWASDControlled(wasd: boolean): void;
                hasPriorityAmmunition(): boolean;
                hasRuntimeID(): boolean;
                getVariant(): number;
                setVariant(variant: number): void;
                isRiding(ridden: Actor): boolean;
                isRider(rider: Actor): boolean;
                removeAllRiders(b1: boolean, b2: boolean): void;
                hasPlayerRider(): boolean;
                isRiding(): boolean;
                getRide(): Nullable<Actor>;
                hasRider(): boolean;
                getStatusFlag(flag: number): boolean;
                isChested(): boolean;
                isStackable(): boolean;
                isResting(): boolean;
                setResting(resting: boolean): void;
                getHealth(): number;
                getMaxHealth(): number;
                getControllingSeat(): number;
                setControllingSeat(seat: number): void;
                isInsidePortal(): boolean;
                hasTeleported(): boolean;
                moveRelative(strafe: number, up: number, forward: number, friction: number): void;
                getRegion(): Nullable<ExtendedBlockSource>;
                isTame(): boolean;
                isLeashed(): boolean;
                isLeashableType(): boolean;
                isMoving(): boolean;
                setMoving(moving: boolean): void;
                hasTotemEquipped(): boolean;
                isAutonomous(): boolean;
                setAutonomous(auto: boolean): void;
                isPersistent(): boolean;
                removeEntity(): void;
                setCollidableMob(collidable: boolean): void;
                getCollidableMobNear(): boolean;
                setCollidableMobNear(collidable: boolean): void;
                hasFishingHook(): boolean;
                getChainedDamageEffects(): boolean;
                setChainedDamageEffects(chained: boolean): void;
                isPacified(): boolean;
                distanceTo(actor: Actor): number;
                distanceTo(x: number, y: number, z: number): number;
                canCurrentlySwim(): boolean;
                isSwimming(): boolean;
                isSwimmer(): boolean;
                setSwimmer(swimmer: boolean): void;
                hasFamily(family: any_string): boolean;
                hasAttributeBuff(buffType: number): boolean;
                isClientSide(): boolean;
                isControlledByLocalInstance(): boolean;
                isClimbing(): boolean;
                setClimbing(climbing: boolean): void;
                canClimb(): boolean;
                setCanClimb(canClimb: boolean): void;
                getSkinID(): number;
                setSkinID(id: number): void;
                getSpeedInMetersPerSecond(): number;
                getStrength(): number;
                setStrength(strength: number): void;
                getStrengthMax(): number;
                setStrengthMax(strength: number): void;
                getDamageNearbyMobs(): boolean;
                setDamageNearbyMobs(damage: boolean): void;
                isLayingDown(): boolean;
                setLayingDown(laying: boolean): void;
                getTempted(): boolean;
                setTempted(tempted: boolean): void;
                dropTowards(x: number, y: number, z: number, id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                isTrading(): boolean;
                inDownwardFlowingLiquid(): boolean;
                getJumpDuration(): number;
                setJumpDuration(dur: number): void;
                isScared(): boolean;
                setScared(scared: boolean): void;
                isSitting(): boolean;
                setSitting(sitting: boolean): void;
                isBaby(): boolean;
                isIgnited(): boolean;
                getLifeSpan(): number;
                setLimitedLife(life: number): void;
                isInvisible(): boolean;
                setInvisible(invisible: boolean): void;
                isInWorld(): boolean;
                isInLove(): boolean;
                setInLove(lover: Actor): void;
                isDoorBreaker(): boolean;
                setDoorBreaker(breaker: boolean): void;
                isWalker(): boolean;
                setWalker(walker: boolean): void;
                isCharged(): boolean;
                setCharged(charged: boolean): void;
                canFly(): boolean;
                setCanFly(canFly: boolean): void;
                isInPrecipitation(): boolean;
                setAABB(x1: number, y1: number, z1: number, x2: number, y2: number, z2: number): void;
                isSafeToSleepNear(): boolean;
                setBlockTarget(x: number, y: number, z: number): void;
                isAngry(): boolean;
                isPowered(): boolean;
                setPowered(powered: boolean): void;
                isSheared(): boolean;
                isOutOfControl(): boolean;
                isSneaking(): boolean;
                setSneaking(sneaking: boolean): void;
                getTarget(): Nullable<Actor>;
                setTarget(target: Actor): void;
                setStunned(stunned: boolean): void;
                getTotalAirSupply(): number;
                getAirSupply(): number;
                isInThunderstorm(): boolean;
                isBribed(): boolean;
                isStanding(): boolean;
                setStanding(standing: boolean): void;
                getShakeTime(): number;
                setShakeTime(time: number): void;
                hasCategory(category: number): boolean;
                getVerticalSpeedInMetersPerSecond(): number;
                isTrusting(): boolean;
                getRadius(): number;
                hasComponent(component: any_string): boolean;
                getOnDeathExperience(): number;
                getInterpolatedBodyYaw(partialTicks: number): number;
                getYawSpeedInDegreesPerSecond(): number;
                getInterpolatedWalkAnimSpeed(partialTicks: number): number;
                isFireImmune(): boolean;
                breaksFallingBlocks(): boolean;
                chorusFruitTeleport(x: number, y: number, z: number): void;
                lerpTo(x: number, y: number, z: number, rotX: number, rotY: number): void;
                lerpMotion(x: number, y: number, z: number): void;
                getRidingHeight(): number;
                startRiding(ridden: Actor): void;
                addRider(rider: Actor): void;
                intersects(x1: number, y1: number, z1: number, x2: number, y2: number, z2: number): boolean;
                isFree(x: number, y: number, z: number): boolean;
                isFree(x: number, y: number, z: number, someFloat: number): boolean;
                isInWall(): boolean;
                canShowNameTag(): boolean;
                canExistInPeaceful(): boolean;
                setNameTagVisible(visible: boolean): void;
                getAlwaysShowNameTag(): boolean;
                isInWater(): boolean;
                hasEnteredWater(): boolean;
                isImmersedInWater(): boolean;
                isInWaterOrRain(): boolean;
                isInLava(): boolean;
                isUnderLiquid(materialType: number): boolean;
                isOverWater(): boolean;
                getShadowRadius(): number;
                canSeeInvisible(): boolean;
                canSee(actor: Actor): boolean;
                canSee(x: number, y: number, z: number): boolean;
                isImmobile(): boolean;
                isSilent(): boolean;
                isPickable(): boolean;
                isFishable(): boolean;
                isSleeping(): boolean;
                isShootable(): boolean;
                isBlocking(): boolean;
                isAlive(): boolean;
                isOnFire(): boolean;
                setOnFire(fireTicks: number): void;
                isOnHotBlock(): boolean;
                isCreativeModeAllowed(): boolean;
                isSurfaceMob(): boolean;
                isTargetable(): boolean;
                isLocalPlayer(): boolean;
                isPlayer(): boolean;
                canAttack(victim: Actor, someBool: boolean): boolean;
                isValidTarget(potentialTarget: Actor): boolean;
                attack(victim: Actor): void;
                performRangedAttack(victim: Actor, distanceFactor: number): void;
                getEquipmentCount(): number;
                getInventorySize(): number;
                getEquipSlots(): number;
                getChestSlots(): number;
                canPowerJump(): boolean;
                setCanPowerJump(canPowerJump: boolean): void;
                isJumping(): boolean;
                doFireHurt(amount: number): void;
                onLightningHit(): void;
                feed(amount: number): void;
                getPickRadius(): number;
                getArmor(slot: number): Nullable<ItemInstance>;
                setArmor(slot: number, id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                getArmorMaterialTypeInSlot(slot: number): number;
                getArmorMaterialTextureTypeInSlot(slot: number): number;
                getEquippedSlot(slot: number): Nullable<ItemInstance>;
                setEquippedSlot(slot: number, id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                getCarriedItem(): Nullable<ItemInstance>;
                setCarriedItem(id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                setOffhandSlot(id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                consumeTotem(): void;
                getPortalCooldown(): number;
                getPortalWaitTime(): number;
                canBePulledIntoVehicle(): boolean;
                inCaravan(): boolean;
                heal(amount: number): void;
                isInvertedHealAndHarm(): boolean;
                canBeAffected(effectId: number): boolean;
                canBeAffected(effect: MobEffectInstance): boolean;
                canBeAffectedByArrow(effect: MobEffectInstance): boolean;
                swing(): void;
                hasOutputSignal(signal: number): boolean;
                getOutputSignal(): number;
                getRiderYRotation(rider: Actor): number;
                isWorldBuilder(): boolean;
                isCreative(): boolean;
                isAdventure(): boolean;
                add(id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                drop(id: number, count: number, data: number, extra: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>, someBool: boolean): void;
                setAuxValue(aux: number): void;
                wobble(): void;
                hasHurt(): boolean;
                startSpinAttack(): void;
                stopSpinAttack(): void;
                kill(): void;
                shouldTryMakeStepSound(): boolean;
                canMakeStepSound(): boolean;
                outOfWorld(): boolean;
                pushOutOfBlocks(x: number, y: number, z: number): void;
                doWaterSplashEffect(): void;
                spawnTrailBubbles(): void;
                isOnGround(): boolean;
                calculateAttackDamage(victim: number | Actor): number;
                calculateAttackDamage(id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>, victim?: number | Actor): number;
                canBreatheAir(): boolean;
                canBreatheWater(): boolean;
                canBreatheLava(): boolean;
                canBreatheSolids(): boolean;
                generatesBubbles(): boolean;
                getInhaleTime(): number;
                getSuffocateTime(): number;
                setAirSupply(supply: number): void;
                getMaxAirSupply(): number;
                setMaxAirSupply(supply: number): void;
                getAirRegenPerTick(): number;
                isElytraFlying(): boolean;
                isMob(): boolean;
                asMob(): Nullable<Mob>;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.Actor"): typeof vsdum.kex.natives.Actor;

declare module vsdum {
    export module kex {
        export module natives {
            export class Mob extends Actor {
                static class: java.lang.Class<Mob>;
                constructor(entity: number);
                constructor(actor: Actor);
                setSleeping(sleeping: boolean): void;
                isSprinting(): boolean;
                setSprinting(sprinting: boolean): void;
                getSpeed(): number;
                setSpeed(speed: number): void;
                getJumpPower(): number;
                getMeleeWeaponDamageBonus(mob: Mob): number;
                getMeleeKnockbackBonus(): number;
                travel(strafe: number, vertical: number, forward: number): void;
                applyFinalFriction(friction: number, discardFriction: boolean): void;
                isLookingAtAnEntity(): boolean;
                getItemUseDuration(): number;
                getItemUseStartupProgress(): number;
                getItemUseIntervalProgress(): number;
                getMaxHeadXRot(): number;
                getLastHurtByMob(): Nullable<Mob>;
                setLastHurtByMob(mob: Mob): void;
                getLastHurtMob(): Nullable<Actor>;
                setLastHurtMob(actor: Actor): void;
                isAlliedTo(mob: Mob): boolean;
                canBeControlledByRider(): boolean;
                leaveCaravan(): void;
                joinCaravan(caravanHead: Mob): void;
                hasCaravanTail(): boolean;
                getCaravanHead(): Nullable<Mob>;
                getArmorValue(): number;
                getArmorCoverPercentage(): number;
                getItemSlot(slot: number): Nullable<ItemInstance>;
                setItemSlot(slot: number, id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                isTransitioningSitting(): boolean;
                setTransitioningSitting(transitioningSitting: boolean): void;
                canExistWhenDisallowMob(): boolean;
                jumpFromGround(): void;
                getNoActionTime(): number;
                resetNoActionTime(): void;
                wantsToBeJockey(): boolean;
                setWantsToBeJockey(wantsToBeJockey: boolean): void;
                isLayingEgg(): boolean;
                setIsLayingEgg(laying: boolean): void;
                getGlidingTicks(): number;
                getFrictionModifier(): number;
                setFrictionModifier(frictionModifier: number): void;
                snapToYBodyRot(rot: number): void;
                snapToYHeadRot(rot: number): void;
                incrementArrowCount(increment: number): void;
                canPickUpLoot(id: number, count: number, data: number, extra?: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): boolean;
                getJumpMultiplier(): number;
                hasBeenHurtByMobInLastTicks(ticks: number): boolean;
                isHeadInWater(): boolean;
                getMovementComponentCurrentSpeed(): number;
                setMovementComponentCurrentSpeed(speed: number): void;
                getFlightSpeed(): number;
                setFlightSpeed(speed: number): void;
                isInterpolationActive(): boolean;
                setInterpolationActive(interpolationActive: boolean): void;
                setYHeadRot(rot: number): void;
                getRiderRotLimit(): number;
                setRiderRotLimit(lim: number): void;
                getRollCounter(): number;
                isRolling(): boolean;
                setRolling(rolling: boolean): void;
                getSpawnMethod(): number;
                setSpawnMethod(method: number): void;
                getXxa(): number;
                setXxa(xxa: number): void;
                getYya(): number;
                setYya(yya: number): void;
                getZza(): number;
                setZza(yya: number): void;
                getTravelType(): number;
                setSurfaceMob(isSurfaceMob: boolean): void;
                isPregnant(): boolean;
                setIsPregnant(pregnant: boolean): void;
                isNaturallySpawned(): boolean;
                setNaturallySpawned(naturallySpawned: boolean): void;
                getRiderLockedBodyRot(): number;
                setRiderLockedBodyRot(rot: number): void;
                isFrostWalking(): boolean;
                setJumpVelRedux(redux: number): void;
                calcMoveRelativeSpeed(travelType: number): number;
                isEating(): boolean;
                setEating(eating: boolean): void;
                getEatCounter(): number;
                setEatCounter(counter: number): void;
                hasBoundOrigin(): boolean;
                getCaravanSize(): number;
                shouldApplyWaterGravity(): boolean;
                isGliding(): boolean;
                getFirstCaravanHead(): Nullable<Mob>;
                getYRotA(): number;
                setYRotA(yrota: number): void;
                setJumping(jumping: boolean): void;
                setSpeedModifier(speedModifier: number): void;
                getCurrentSwingDuration(): number;
                isSwinging(): boolean;
                calculateJumpImpulse(): number;
                isSlime(): boolean;
                asSlime(): Nullable<Slime>;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.Mob"): typeof vsdum.kex.natives.Mob;

declare module vsdum {
    export module kex {
        export module natives {
            export class Slime extends Mob {
                static class: java.lang.Class<Slime>;
                constructor(entity: number);
                constructor(mob: Mob);
                constructor(actor: Actor);
                decreaseSquish(): number;
                justJumped(): boolean;
                justLanded(): boolean;
                getSquishValue(): number;
                getOldSquishValue(): number;
                getTargetSquish(): number;
                getSlimeSize(): number;
                setSlimeSize(size: number): void;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.Slime"): typeof vsdum.kex.natives.Slime;

declare module vsdum {
    export module kex {
        export module natives {
            export class Player extends Mob {
                static class: java.lang.Class<Player>;
                constructor(entity: number);
                constructor(mob: Mob);
                constructor(actor: Actor);
                addExperience(exp: number): void;
                addItemToInventory(id: number, count: number, data: number, extra?: com.zhekasmirnov.innercore.api.NativeItemInstanceExtra, dropRemaining?: boolean): void;
                getExhaustion(): number;
                getExperience(): number;
                getGameMode(): number;
                getHunger(): number;
                getInventorySlot(slot: number): ItemInstance;
                getExpLevel(): number;
                getSaturation(): number;
                getScore(): number;
                getSelectedSlot(): number;
                invokeUseItemNoTarget(id: number, count: number, data: number, extra: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                setExhaustion(value: number): void;
                setExperience(value: number): void;
                setHunger(value: number): void;
                setInventorySlot(slot: number, id: number, count: number, data: number, extra: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): void;
                setExpLevel(level: number): void;
                setRespawnCoords(x: number, y: number, z: number): void;
                setSaturation(value: number): void;
                setSelectedSlot(slot: number): void;
                spawnExpOrbs(x: number, y: number, z: number, value: number): void;
                isAutoJumpEnabled(): boolean;
                getCommandPermissionLevel(): number;
                setPermissions(level: number): void;
                getPlayerPermissionLevel(): number;
                displayChatMessage(prefix: any_string, message: any_string): void;
                displayClientMessage(message: any_string): void;
                displayWhisperMessage(s1: any_string, s2: any_string, s3: any_string, s4: any_string): void;
                startSleepInBed(x: number, y: number, z: number): void;
                stopSleepInBed(b1: boolean, b2: boolean): void;
                canStartSleepInBed(): boolean;
                getSleepTimer(): number;
                getPreviousTickSleepTimer(): number;
                openSign(x: number, y: number, z: number): void;
                playEmote(emote: any_string): void;
                isHostingPlayer(): boolean;
                setGameMode(mode: number): void;
                addLevels(levels: number): void;
                setFieldOfViewModifier(modifier: number): void;
                startCooldown(id: number): void;
                startGliding(): void;
                stopGliding(): void;
                isChatAllowed(): boolean;
                getHasSeenCredits(): boolean;
                setHasSeenCredits(seen: boolean): void;
                shouldShowCredits(): boolean;
                getLuck(): number;
                forceAllowEating(): boolean;
                eat(nutrition: number, saturation: number): void;
                eat2(nutrition: number, saturationModifier: number): void;
                causeFoodExhaustion(exhaustion: number): void;
                isBouncing(): boolean;
                isForcedRespawn(): boolean;
                getEnchantmentSeed(): number;
                setEnchantmentSeed(seed: number): void;
                getNewEnchantmentSeed(): number;
                getTicksUsingItem(): number;
                canUseOperatorBlocks(): boolean;
                isOperator(): boolean;
                isViewer(): boolean;
                getXpNeededForNextLevel(): number;
                getXpNeededForLevelRange(min: number, max: number): number;
                isEmoting(): boolean;
                getLevelProgress(): number;
                getMapIndex(): number;
                setMapIndex(index: number): void;
                getAttackDamage(): number;
                isHungry(): boolean;
                isInRaid(): boolean;
                hasOpenContainer(): boolean;
                isUsingItem(): boolean;
                getUnderwaterLightLevel(): number;
                setUnderwaterLightLevel(level: number): void;
                canBeSeenOnMap(): boolean;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.Player"): typeof vsdum.kex.natives.Player;

declare module vsdum {
    export module kex {
        export module natives {
            export class LocalPlayer extends Player {
                static class: java.lang.Class<LocalPlayer>;
                constructor(entity: number);
                constructor(player: Player);
                constructor(mob: Mob);
                constructor(actor: Actor);
                getMoveInputHandler(): Nullable<MoveInputHandler>;
                isFlying(): boolean;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.LocalPlayer"): typeof vsdum.kex.natives.LocalPlayer;

declare module vsdum {
    export module kex {
        export module natives {
            export class MoveInputHandler extends common.INativeInterface {
                static class: java.lang.Class<MoveInputHandler>;
                constructor(ptr: number);
                clearInputState(): void;
                isChangeHeight(): boolean;
                isPlayerMoving(): boolean;
                isJumpDown(): boolean;
                wantsMoveForward(): boolean;
                setSneakPersistence(persistence: boolean): void;
                setGazeDirection(x: number, y: number, z: number): void;
                isMovingForward(): boolean;
                isMovingBackward(): boolean;
                isMovingLeft(): boolean;
                isMovingRight(): boolean;
                getMovingForward(): number;
                getMovingBackward(): number;
                getMovingLeft(): number;
                getMovingRight(): number;
            }
        }
    }
}

declare module vsdum {
    export module kex {
        export module natives {
            export class GlobalContext extends java.lang.Object {
                static class: java.lang.Class<GlobalContext>;
                static getLocalPlayer(): Nullable<LocalPlayer>;
                static getLevel(): Nullable<Level>;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.GlobalContext"): typeof vsdum.kex.natives.GlobalContext;

declare module vsdum {
    export module kex {
        export module natives {
            export class Dimension extends common.INativeInterface {
                static class: java.lang.Class<Dimension>;
                constructor(pointer: number);
                getDimensionId(): number;
                getLevel(): Nullable<Level>;
            }
        }
    }
}

declare module vsdum {
    export module kex {
        export module natives {
            export class Level extends common.INativeInterface {
                static class: java.lang.Class<Level>;
                constructor(pointer: number);
                getTickingAreasManager(): Nullable<TickingAreasManager>;
            }
        }
    }
}

declare module vsdum {
    export module kex {
        export module natives {
            export class MobEffect extends common.INativeInterface {
                static class: java.lang.Class<MobEffect>;
                constructor(pointer: number);
                static getById(id: number): Nullable<MobEffect>;
                isVisible(): boolean;
                getId(): number;
                isHarmful(): boolean;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.MobEffect"): typeof vsdum.kex.natives.MobEffect;

declare module vsdum {
    export module kex {
        export module natives {
            export class MobEffectInstance extends common.INativeInterface {
                static class: java.lang.Class<MobEffectInstance>;
                constructor(pointer: number, flagForPointerOverload: boolean);
                constructor(id: number);
                constructor(id: number, duration: number);
                constructor(id: number, duration: number, amplifier: number);
                constructor(id: number, duration: number, amplifier: number, isAmbient: boolean, isEffectVisible: boolean, displaysOnScreenTextureAnimation: boolean);
                constructor(id: number, durationPeaceful: number, durationEasy: number, durationNormal: number, durationHard: number, amplifier: number, isAmbient: boolean, isEffectVisible: boolean, displaysOnScreenTextureAnimation: boolean);
                getId(): number;
                getDuration(): number;
                setDuration(dur: number): void;
                hasDifficultyDuration(difficulty: 1 | 2 | 3): boolean;
                getDifficultyDuration(difficulty: 1 | 2 | 3): number;
                setDifficultyDuration(difficulty: 1 | 2 | 3, duration: number): void;
                getAmplifier(): number;
                isAmbient(): boolean;
                isEffectVisible(): boolean;
                displaysOnScreenTextureAnimation(): boolean;
                isNoCounter(): boolean;
                setNoCounter(noCounter: boolean): void;
                getSplashDuration(): number;
                getLingerDuration(): number;
                getEffect(): Nullable<MobEffect>;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.MobEffectInstance"): typeof vsdum.kex.natives.MobEffectInstance;

declare module vsdum {
    export module kex {
        export module natives {
            export class FoodItemComponent extends java.lang.Object {
                static class: java.lang.Class<FoodItemComponent>;
                constructor(pointer: number, isGlobal?: boolean);
                getItem(): number;
                getNutrition(): number;
                getSaturationModifier(): number;
                getSaturation(): number;
                getUsingConvertsTo(): Nullable<jstring>;
                getOnUseAction(): number;
                getOnUseRange(): Vector;
                getCooldownType(): Nullable<jstring>;
                getCooldownTime(): number;
                canAlwaysEat(): boolean;
                getEffects(): java.util.List<FoodItemComponent.Effect>;
                getRemoveEffects(): java.util.List<number>;
            }
            export module FoodItemComponent {
                export class Effect extends java.lang.Object {
                    static class: java.lang.Class<Effect>;
                    getDescriptionId(): Nullable<jstring>;
                    getId(): number;
                    getEffect(): Nullable<MobEffect>;
                    getDuration(): number;
                    getAmplifier(): number;
                    getChance(): number;
                }
                export class Builder extends java.lang.Object {
                    static class: java.lang.Class<Builder>;
                    constructor();
                    nutrition(nutr: number): Builder;
                    saturationMod(sat: number): Builder;
                    alwaysEat(): Builder;
                    effect(eff: MobEffectInstance, chance?: number): Builder;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.FoodItemComponent"): typeof vsdum.kex.natives.FoodItemComponent;

declare module vsdum {
    export module kex {
        export module natives {
            export class LootTableContext extends common.INativeInterface {
                static class: java.lang.Class<LootTableContext>;
                constructor(ptr: number);
                getThisEntity(): Nullable<Actor>;
                getOriginalItemName(): Nullable<jstring>;
                setOriginalItemName(name: any_string): void;
                getLevel(): Nullable<Level>;
                getExplosionRadius(): number;
                getLuck(): number;
                getKillerPlayer(): Nullable<Player>;
                getKillerPet(): Nullable<Actor>;
                getKillerEntity(): Nullable<Actor>;
            }
            export module LootTableContext {
                export class Builder extends common.INativeInterface {
                    static class: java.lang.Class<Builder>;
                    constructor(level: Level);
                    withExplosionRadius(radius: number): Builder;
                    withThisEntity(entity: Actor): Builder;
                    withLuck(luck: number): Builder;
                    withOriginalItemName(name: any_string): Builder;
                    withKillerPlayer(player: Player): Builder;
                    create(): LootTableContext;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.LootTableContext"): typeof vsdum.kex.natives.LootTableContext;

declare module vsdum {
    export module kex {
        export module natives {
            export class I18n extends java.lang.Object {
                static class: java.lang.Class<I18n>;
                static translate(key: any_string): jstring;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.I18n"): typeof vsdum.kex.natives.I18n;

declare module vsdum {
    export module kex {
        export module natives {
            export class ActorDamageSource extends common.INativeInterface {
                static class: java.lang.Class<ActorDamageSource>;
                constructor(ptr: number);
                isEntitySource(): boolean;
                isChildEntitySource(): boolean;
                isBlockSource(): boolean;
                isEntityCreative(): boolean;
                isEntityWorldBuilder(): boolean;
                getEntityUniqueID(): number;
                getEntityType(): number;
                getEntityCategories(): number;
                getEntity(): Nullable<Actor>;
                isDamagingEntityCreative(): boolean;
                isDamagingEntityWorldBuilder(): boolean;
                getDamagingEntityUniqueID(): number;
                getDamagingEntityType(): number;
                getDamagingEntityCategories(): number;
                getDamagingEntity(): Nullable<Actor>;
                getCause(): number;
                setCause(cause: number): void;
                getBlock(): Nullable<modules.states.BlockState>;
            }
        }
    }
}

declare module vsdum {
    export module kex {
        export module natives {
            export class ExtendedBlockSource extends BlockSource {
                static class: java.lang.Class<ExtendedBlockSource>;
                getPointer(): number;
                constructor(icObj: BlockSource);
                constructor(ptr: number);
                static toKEXBlockSource(icObj: BlockSource): ExtendedBlockSource;
                static getCurrentClientRegion(): Nullable<ExtendedBlockSource>;
                static getCurrentWorldGenRegion(): Nullable<ExtendedBlockSource>;
                static getDefaultForActor(entity: Actor): Nullable<ExtendedBlockSource>;
                static getDefaultForActor(entityUID: number): Nullable<ExtendedBlockSource>;
                static getDefaultForDimension(dimensionId: number): Nullable<ExtendedBlockSource>;
                getLevel(): Nullable<Level>;
                getDimensionObject(): Nullable<Dimension>;
                getCustomBlockEntity(pos: util.mcmath.BlockPos): Nullable<modules.TileEntityModule.BlockActor>;
                getCustomBlockEntity(x: number, y: number, z: number): Nullable<modules.TileEntityModule.BlockActor>;
                getBlockState(pos: util.mcmath.BlockPos): Nullable<modules.states.BlockState>;
                getBlockState(x: number, y: number, z: number): Nullable<modules.states.BlockState>;
                setBlockState(x: number, y: number, z: number, state: modules.states.BlockState, flags: number): boolean;
                setBlockStateNoUpdate(x: number, y: number, z: number, state: modules.states.BlockState): boolean;
                getBiome(x: number, z: number): number;
                getBiomeFast(x: number, z: number): number;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.ExtendedBlockSource"): typeof vsdum.kex.natives.ExtendedBlockSource;

declare module vsdum {
    export module kex {
        export module natives {
            type WorldOrDimension = number | BlockSource | Dimension;
            export class TickingAreasManager extends common.INativeInterface {
                static class: java.lang.Class<TickingAreasManager>;
                constructor(ptr: number);
                hasActiveAreas(): boolean;
                countAreasIn(worldOrDimension: WorldOrDimension): number;
                countAllAreas(): number;
                hasArea(areaName: any_string, worldOrDimension: WorldOrDimension): boolean;
                addRectangleArea(worldOrDimension: WorldOrDimension, x1: number, z1: number, x2: number, z2: number): void;
                addRectangleArea(worldOrDimension: WorldOrDimension, name: any_string, x1: number, z1: number, x2: number, z2: number): void;
                addCircleArea(worldOrDimension: WorldOrDimension, x: number, z: number, radius: number): void;
                addCircleArea(worldOrDimension: WorldOrDimension, name: any_string, x: number, z: number, radius: number): void;
                removeAreaByPosition(worldOrDimension: WorldOrDimension, x: number, z: number): void;
                removeAreaByName(worldOrDimension: WorldOrDimension, name: any_string): void;
                findUsableDefaultName(worldOrDimension: WorldOrDimension): jstring;
            }
        }
    }
}

type MinMax = { min: number, max: number }
type FeatureTypes = "buriedtreasure" | "endcity" | "fortress" | "mansion" | "mineshaft" | "monument" | "pillageroutpost" | "ruins" | "shipwreck" | "stronghold" | "temple" | "village";
type EnchantTypes = Lowercase<keyof typeof EEnchantment>;

declare namespace LootTableTypes {
    export type LootPoolEntryFunction = {
        function: "enchant_book_for_trading",
        base_cost: number,
        base_random_cost: number,
        per_level_cost: number,
        per_level_random_cost: number;
    } | {
        function: "enchant_random_gear",
        chance?: number;
    } | {
        function: "enchant_randomly",
        treasure?: boolean;
    } | {
        function: "enchant_with_levels",
        levels?: number | MinMax,
        treasure?: boolean;
    } | {
        function: "exploration_map",
        destination?: FeatureTypes;
    } | {
        function: "fill_container",
        loot_table?: any_string;
    } | {
        function: "furnace_smelt",
        conditions?: LootCondition[];
    } | {
        function: "looting_enchant",
        count?: MinMax;
    } | {
        function: "random_aux_value",
        values?: MinMax;
    } | {
        function: "random_block_state",
        block_state?: any_string,
        values?: MinMax;
    } | { function: "random_dye" | "set_data_from_color_index" | "trader_material_type" } | {
        function: "set_actor_id",
        id?: any_string;
    } | {
        function: "set_banner_details",
        type?: number;
    } | {
        function: "set_book_contents",
        author: any_string,
        title: any_string,
        pages: any_string[];
    } | {
        function: "set_count",
        count?: number | MinMax;
    } | {
        function: "set_damage",
        damage?: number | MinMax;
    } | {
        function: "set_data",
        data?: number | MinMax;
    } | {
        function: "set_lore",
        lore?: any_string[];
    } | {
        function: "set_name",
        name?: any_string;
    } | {
        function: "specific_enchants",
        enchants?: { id?: EnchantTypes, level?: number }[];
    } | {
        function: string,
        [key: string]: any;
    }
    export type LootPoolEntry = { type: "empty" } | { type: "loot_table", pools?: LootPool[] } | {
        type: "item",
        name?: any_string,
        count?: number,
        quality?: number,
        weight?: number,
        functions?: LootPoolEntryFunction[];
    }
    export type LootCondition = {
        condition: "entity_properties",
        entity?: "this",
        properties?: {
            on_fire?: boolean,
            on_ground?: boolean;
        };
    } | {
        condition: "has_mark_variant",
        value?: number;
    } | { condition: "killed_by_player" | "killed_by_player_or_pets" } | {
        condition: "random_chance",
        chance?: number,
        max_chance?: number;
    } | {
        condition: "random_chance_with_looting",
        chance?: number,
        looting_multiplier?: number;
    } | {
        condition: "random_difficulty_chance" | "random_regional_difficulty_chance",
        default_chance?: number,
        easy?: number,
        normal?: number,
        hard?: number,
        peaceful?: number;
    } | {
        condition: "and" | "or",
        clauses: LootCondition[];
    } | {
        condition: "not",
        clause: LootCondition;
    }
    export interface LootTiers {
        bonus_chance?: number,
        bonus_rolls?: number,
        initial_range?: number;
    }
    export interface LootPool {
        type?: "item",
        rolls?: number | MinMax,
        tiers?: LootTiers,
        conditions?: LootCondition[],
        entries?: LootPoolEntry[];
    }
    export interface JsonFormat { pools?: LootPool[] }
}

declare module vsdum {
    export module kex {
        export module modules {
            export class LootModule extends java.lang.Object {
                static class: java.lang.Class<LootModule>;
                static createLootTableModifier(tableName: any_string): LootModifier;
                static createConditionsList(): LootConditions;
                static addPiglinBarteringItem(): LootEntry;
                static addOnDropCallbackFor(tableName: any_string, cb: OnDropCallback, priority?: number): void;
                static fillContainer(region: BlockSource, x: number, y: number, z: number, tableName: any_string, actor: Nullable<natives.Actor>): void;
                static getRandomItems(tableName: any_string, context: natives.LootTableContext): java.util.List<ItemInstance>;
                static forceLoad(tableName: any_string): void;
                static registerCustomLootCondition(conditionName: any_string, callback: CustomLootConditionCallback): void;
                static registerCustomLootConditionJS(conditionName: any_string, callback: CustomLootConditionCallbackJS): void;
                static registerCustomLootFunction(functionName: any_string, callback: CustomLootFunctionCallback): void;
                static registerCustomLootFunctionJS(functionName: any_string, callback: CustomLootFunctionCallbackJS): void;
                static runLootCondition(json: org.json.JSONObject, context: natives.LootTableContext): boolean;
                static runLootCondition(json: {[key: string]: any}, context: natives.LootTableContext): boolean;
            }
            export interface CustomLootConditionCallback {
                (json: org.json.JSONObject, context: natives.LootTableContext): boolean;
            }
            export interface CustomLootConditionCallbackJS {
                (json: {[key: string]: any}, context: natives.LootTableContext): boolean;
            }
            export interface CustomLootFunctionCallback {
                (json: org.json.JSONObject, stack: ItemInstance, context: natives.LootTableContext): void;
            }
            export interface CustomLootFunctionCallbackJS {
                (json: {[key: string]: any}, stack: ItemInstance, context: natives.LootTableContext): void;
            }
            export interface OnDropCallback {
                (drops: RandomItemsList, context: natives.LootTableContext): void;
            }
            export interface RandomItemsList extends java.util.ArrayList<ItemInstance> {
                getPointer(): number;
                markChanged(): void;
                addItem(id: number, count: number, data: number, extra?: Nullable<ItemExtraData>): void;
            }
            export interface LootModifier {
                lock(): LootModifier;
                isLocked(): boolean;
                createNewPool(): LootPool;
                createNewPool(rolls: number): LootPool;
                createNewPool(minRolls: number, maxRolls: number): LootPool;
                modifyWithAnotherLootTable(path: any_string): LootModifier;
                modifyWithJSON(json: LootTableTypes.JsonFormat): LootModifier;
                addItem(id: number, count: number | MinMax, data: number, chance: number, rolls?: number | MinMax): LootModifier;
                addAddonItem(namespace: any_string, identifier: any_string, count: number | MinMax, data: number, chance: number, rolls?: number | MinMax): LootModifier;
                addJSModifyCallback(cb: JSModifyCallback, priority?: number): LootModifier;
                addJSONModifyCallback(cb: JSONModifyCallback, priority?: number): LootModifier;
                addJSPostModifyCallback(cb: JSModifyCallback): LootModifier;
                addJSONPostModifyCallback(cb: JSONModifyCallback): LootModifier;
            }
            export interface JSModifyCallback {
                (obj: LootTableTypes.JsonFormat): void;
            }
            export interface JSONModifyCallback {
                (obj: org.json.JSONObject): void;
            }
            export interface LootPool {
                beginConditions(): LootConditions;
                beginTiers(): LootTiers;
                addEntry(): LootEntry;
                endPool(): LootModifier;
            }
            export interface LootConditions {
                addEntityOnFireCondition(onFire: boolean): LootConditions;
                addEntityOnGroundCondition(onGround: boolean): LootConditions;
                addEntityPropertiesCondition(onFire: boolean, onGround: boolean): LootConditions;
                addMarkVariantCondition(markVariant: number): LootConditions;
                addKilledByPlayerCondition(): LootConditions;
                addKilledByPlayerOrPetsCondition(): LootConditions;
                addRandomChanceCondition(chance: number, maxChance?: number): LootConditions;
                addRandomChanceWithLootingCondition(chance: number, lootingMultiplier: number): LootConditions;
                addRandomDifficultyChanceCondition(defaultChance: number, easy?: number, normal?: number, hard?: number, peaceful?: number): LootConditions;
                addRandomRegionalDifficultyChanceCondition(maxChance: number): LootConditions;
                addCustomCondition(conditionName: any_string, json: org.json.JSONObject): LootConditions;
                addCustomCondition(conditionName: any_string, json: object): LootConditions;
                addANDCondition(clauses: LootConditions): LootConditions;
                addORCondition(clauses: LootConditions): LootConditions;
                addNOTCondition(clause: LootConditions): LootConditions;
                endConditions(): LootPool;
            }
            export interface LootTiers {
                setBonusChance(bonusChance: number): LootTiers;
                setBonusRolls(bonusRolls: number): LootTiers;
                setInitialRange(initialRange: number): LootTiers;
                endTiers(): LootPool;
            }
            export interface LootEntry {
                describeItem(numericId: number): LootEntry;
                describeItem(namespace: any_string, identifier: any_string): LootEntry;
                setCount(count: number): LootEntry;
                setCount(min: number, max: number): LootEntry;
                setData(data: number): LootEntry;
                setData(minData: number, maxData: number): LootEntry;
                setDamage(damage: number): LootEntry;
                setDamage(minDamage: number, maxDamage: number): LootEntry;
                setCustomName(name: any_string): LootEntry;
                setWeight(weight: number): LootEntry;
                setQuality(quality: number): LootEntry;
                beginFunctions(): LootEntryFunctions;
                endEntry(): LootPool;
            }
            export interface LootEntryFunctions {
                addEnchantBookForTradingFunction(baseCost: number, baseRandomCost: number, perLevelCost: number, perLevelRandomCost: number): LootEntryFunctions;
                addEnchantRandomGearFunction(chance?: number): LootEntryFunctions;
                addEnchantRandomlyFunction(treasure?: boolean): LootEntryFunctions;
                addEnchantWithLevelsFunction(levels: number, treasure?: boolean): LootEntryFunctions;
                addEnchantWithLevelsFunction(minLevels: number, maxLevels: number, treasure?: boolean): LootEntryFunctions;
                addExplorationMapFunction(destination: FeatureTypes): LootEntryFunctions;
                addFillContainerFunction(lootTable: any_string): LootEntryFunctions;
                addFurnaceSmeltFunction(conditions?: LootConditions): LootEntryFunctions;
                addLootingEnchantFunction(): LootEntryFunctions;
                addLootingEnchantFunction(minCount: number, maxCount: number): LootEntryFunctions;
                addRandomAuxValueFunction(): LootEntryFunctions;
                addRandomAuxValueFunction(minValue: number, maxValue: number): LootEntryFunctions;
                addRandomDyeFunction(): LootEntryFunctions;
                addActorIdFunction(actorId: any_string): LootEntryFunctions;
                addBookContentsFunction(author: any_string, title: any_string, pages: any_string[]): LootEntryFunctions;
                addDataFromColorIndexFunction(): LootEntryFunctions;
                addLoreFunction(lore: any_string[]): LootEntryFunctions;
                addSpecificEnchantsFunction(enchants: java.util.Map<jstring, number> | { [key in EnchantTypes]: number }): LootEntryFunctions;
                addTraderMaterialTypeFunction(): LootEntryFunctions;
                addCustomFunction(functionName: any_string, json: org.json.JSONObject): LootEntryFunctions;
                addCustomFunction(functionName: any_string, json: object): LootEntryFunctions;
                endFunctions(): LootEntry;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.LootModule"): typeof vsdum.kex.modules.LootModule;

declare module vsdum {
    export module kex {
        export module modules {
            interface UseDurationCallback {
                (stack: ItemInstance): number;
            }
            interface OnTooltipCallback {
                (stack: ItemInstance, text: java.util.List<jstring>, level: natives.Level): void;
            }
            interface FoodValuesCallback {
                (stack: ItemInstance): natives.FoodItemComponent.Builder;
            }
            export class ItemsModule extends java.lang.Object {
                static class: java.lang.Class<ItemsModule>;
                static setRequiresWorldBuilder(id: number, requiresWorldBuilder: boolean): void;
                static setExplodable(id: number, explodable: boolean): void;
                static setFireResistant(id: number, fireResistant: boolean): void;
                static setShouldDespawn(id: number, shouldDespawn: boolean): void;
                static setIsMirroredArt(id: number, isMirroredArt: boolean): void;
                static setFurnaceBurnIntervalMultiplier(id: number, multiplier: number): void;
                static setFurnaceXPMultiplier(id: number, multiplier: number): void;
                static setCannotBeRepairedInAnvil(id: number): void;
                static isFood(id: number): boolean;
                static getFood(id: number): Nullable<natives.FoodItemComponent>;
                static newFoodSaturationModifier(name: any_string, value: number): void;
                static saturationModifierFromString(name: any_string): number;
                static setMaxUseDurationDynamic(id: number, callback: UseDurationCallback): void;
                static addTooltip(id: number, callback: OnTooltipCallback, priority?: number, isCallbackForced?: boolean): void;
                static setDynamicFoodValues(id: number, callback: FoodValuesCallback): void;
                static registerReachDistanceModifierFor(id: number, modifier: misc.ReachDistanceModifier): void;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.ItemsModule"): typeof vsdum.kex.modules.ItemsModule;

declare module vsdum {
    export module kex {
        export module modules {
            interface ExtendedToolParams extends ToolAPI.ToolParams {
                getAttackDamageBonus?: (item: ItemInstance, attacker: number, victim: number) => number;
            }
            interface BlockData {
                readonly materialName: Nullable<jstring>;
                readonly destroyLevel: number;
                readonly isNative: boolean;
            }
            export class ToolsModule extends java.lang.Object {
                static class: java.lang.Class<ToolsModule>;
                static getBlockDestroyTime(blockID: number): number;
                static getToolLevel(itemID: number): number;
                static getToolLevelViaBlock(itemID: number, blockID: number): number;
                static enableDynamicDamageFor(itemID: number): void;
                static getTierByName(tierName: any_string): Nullable<ToolsModule.ItemTier>;
                static registerSword(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tier: ToolsModule.ItemTier, isTech?: boolean): void;
                static registerAxe(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tier: ToolsModule.ItemTier, isTech?: boolean): void;
                static registerPickaxe(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tier: ToolsModule.ItemTier, isTech?: boolean): void;
                static registerShovel(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tier: ToolsModule.ItemTier, isTech?: boolean): void;
                static registerHoe(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tier: ToolsModule.ItemTier, isTech?: boolean): void;
                static registerShears(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tierOrDurability: ToolsModule.ItemTier | number, isTech?: boolean): void;
                static registerFlintAndSteel(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, durability: number, isTech?: boolean): void;
                static addBlockMaterial(name: any_string, breakingMultiplier: number): void;
                static getBlockMaterialBreakingMultiplier(name: any_string): number;
                static getBlockData(id: number): BlockData;
                static getBlockMaterialName(id: number): Nullable<jstring>;
                static getBlockDestroyLevel(id: number): number;
                static getBlockIsNative(id: number): boolean;
                static setBlockData(id: number, materialName: any_string, destroyLevel: number, isNative: boolean): void;
                static setBlockMaterialName(id: number, materialName: any_string): void;
                static setBlockDestroyLevel(id: number, destroyLevel: number): void;
                static setBlockIsNative(id: number, isNative: boolean): void;
                static registerCustomTool(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tier: ToolsModule.ItemTier, isTech: boolean, isWeapon: boolean, blockMaterials: Nullable<any_string[]>, brokenId: number, baseAttackDamage: number, enchantType: number, toolData: ExtendedToolParams): void;
                static destroyBlockHook(coords: Callback.ItemUseCoordinates, block: Tile, item: ItemInstance, player: number): void;
                static playerAttackHook(attacker: number, victim: number, item: ItemInstance): void;
                static useCustomShearsOn(x: number, y: number, z: number, side: number, rx: number, ry: number, rz: number, actorUID: number): void;
                static useCustomFlintAndSteelOn(x: number, y: number, z: number, side: number, rx: number, ry: number, rz: number, actorUID: number): void;
                static isTool(id: number): boolean;
                static isSword(id: number): boolean;
                static isAxe(id: number): boolean;
                static isPickaxe(id: number): boolean;
                static isShovel(id: number): boolean;
                static isHoe(id: number): boolean;
                static isCustomTool(id: number): boolean;
                static isShears(id: number): boolean;
                static isFlintAndSteel(id: number): boolean;
            }
            export module ToolsModule {
                export class ItemTier extends java.lang.Object {
                    static class: java.lang.Class<ItemTier>;
                    constructor(name: any_string, level: number, uses: number, speed: number, attackDamageBonus: number, enchantmentValue: number);
                    getLevel(): number;
                    getUses(): number;
                    getSpeed(): number;
                    getAttackDamageBonus(): number;
                    getEnchantmentValue(): number;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.ToolsModule"): typeof vsdum.kex.modules.ToolsModule;

declare module vsdum {
    export module kex {
        export module modules {
            export class BlocksModule extends java.lang.Object {
                static class: java.lang.Class<BlocksModule>;
                static registerComparatorSignalCallbackJS(id: number, callback: BlocksModule.ComparatorSignalCallbackJS, isCallbackForced?: boolean): void;
                static registerComparatorSignalCallback(id: number, callback: BlocksModule.ComparatorSignalCallback, isCallbackForced?: boolean): void;
                static registerOnStepOnCallback(id: number, callback: BlocksModule.OnStepOnCallback): void;
                static registerOnStepOffCallback(id: number, callback: BlocksModule.OnStepOffCallback): void;
                static setLightEmission(id: number, data: number, lightLevel: number): void;
                static getLightEmission(id: number, data: number): number;
                static registerStateForBlock(id: number, state: NonNullable<states.properties.Property<any>>): void;
            }
            export module BlocksModule {
                export interface ComparatorSignalCallback {
                    (block: states.BlockState, world: natives.ExtendedBlockSource, pos: util.mcmath.BlockPos, side: util.mcmath.Direction): number;
                }
                export interface ComparatorSignalCallbackJS {
                    (block: states.BlockState, world: natives.ExtendedBlockSource, coords: Callback.ItemUseCoordinates): number;
                }
                export interface OnStepOnCallback {
                    (world: natives.ExtendedBlockSource, pos: Vector, state: states.BlockState, entity: natives.Actor): void;
                }
                export type OnStepOffCallback = OnStepOnCallback;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.BlocksModule"): typeof vsdum.kex.modules.BlocksModule;

declare module vsdum {
    export module kex {
        export module modules {
            export module DamageModule {
                export type DamageDealingParams = {} | {
                    source: "actor" | "entity" | "blocksource" | "world" | "block",
                    bool1?: boolean, bool2?: boolean,
                    attacker?: number,
                    world?: BlockSource,
                    region?: BlockSource,
                    pos?: Partial<Vector>,
                    position?: Partial<Vector>,
                    x?: number, y?: number, z?: number;
                }
                export interface CustomTranslationCallback {
                    (source: natives.ActorDamageSource, nickname: jstring, actor: natives.Actor): any_string;
                }
                export function isFire(id: number): boolean;
                export function damageEntity(entity: number, damage: number, cause: number, params?: DamageDealingParams): void;
                export class CustomCause extends java.lang.Object {
                    static class: java.lang.Class<CustomCause>;
                    readonly name: jstring;
                    readonly id: number;
                    constructor(name: any_string);
                    setFire(): CustomCause;
                    setDeathMessage(message: any_string): CustomCause;
                    setDeathMessage(translations: object): CustomCause;
                    setDeathMessageCallback(callback: CustomTranslationCallback): CustomCause;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.DamageModule"): typeof vsdum.kex.modules.DamageModule;

declare module vsdum {
    export module kex {
        export module modules {
            export module CommandsModule {
                export interface CommandContext {
                    getInt(name: any_string): number;
                    getFloat(name: any_string): number;
                    getBool(name: any_string): boolean;
                    getRelativeFloat(name: any_string, center: number): number;
                    getPosition(name: any_string): Vector;
                    getFloatPosition(name: any_string): Vector;
                    getString(name: any_string): jstring;
                    getMessage(name: any_string): jstring;
                    getJson(name: any_string): Nullable<org.json.JSONObject>;
                    getEntities(name: any_string): java.util.List<natives.Actor>;
                    getPlayers(name: any_string): java.util.List<natives.Player>;
                    getPlayer(name: any_string): Nullable<natives.Player>;
                    getSourceBlockPosition(): Vector;
                    getSourceWorldPosition(): Vector;
                    getSourceLevel(): Nullable<natives.Level>;
                    getSourceDimension(): Nullable<natives.Dimension>;
                    getSourceEntity(): Nullable<natives.Actor>;
                    getSourcePlayer(): Nullable<natives.Player>;
                    success(msg?: any_string): void;
                    error(msg: any_string): void;
                }
                export interface CommandExecuteCallback {
                    (ctx: CommandContext): void;
                }
                export interface CustomParserCommandExecuteCallback {
                    (text: jstring, ctx: CommandContext): void;
                }
                export interface CommandArgument {
                    then(child: CommandArgument): CommandArgument;
                    executes(callback: CommandExecuteCallback): CommandArgument;
                    getCallback(): Nullable<CommandExecuteCallback>;
                }
                export interface CommandOverloadBase {
                    then(child: CommandArgument): CommandOverloadBase;
                    executes(callback: CommandExecuteCallback): CommandOverloadBase;
                    getCallback(): Nullable<CommandExecuteCallback>;
                    addAlias(alias: any_string): CommandOverloadBase;
                    addAliases(aliases: any_string[]): CommandOverloadBase;
                    setDescription(description: any_string): CommandOverloadBase;
                    setDescription(translations: object): CommandOverloadBase;
                    listOverloads(): java.util.List<java.util.List<CommandArgument>>;
                }
                export interface EnumBuilder {
                    add(key: any_string, value: number): EnumBuilder;
                    register(): void;
                }
                export interface StringEnumBuilder {
                    add(value: any_string): StringEnumBuilder;
                    register(): void;
                }
                export function newCommand(name: any_string, permissionLevel?: number): CommandOverloadBase;
                export function registerCommand(base: CommandOverloadBase): void;
                export function registerCustomParserCommand(name: any_string, callback: CustomParserCommandExecuteCallback, permissionLevel?: number): void;
                export function intArg(name: any_string, defaultValue?: number): CommandArgument;
                export function floatArg(name: any_string, defaultValue?: number): CommandArgument;
                export function boolArg(name: any_string, defaultValue?: boolean): CommandArgument;
                export function relativeFloatArg(name: any_string, defaultValue?: number): CommandArgument;
                export function positionArg(name: any_string): CommandArgument;
                export function positionArg(name: any_string, defaultX: number, defaultY: number, defaultZ: number): CommandArgument;
                export function floatPositionArg(name: any_string): CommandArgument;
                export function floatPositionArg(name: any_string, defaultX: number, defaultY: number, defaultZ: number): CommandArgument;
                export function stringArg(name: any_string, defaultValue?: any_string): CommandArgument;
                export function messageArg(name: any_string): CommandArgument;
                export function jsonArg(name: any_string): CommandArgument;
                export function entityArg(name: any_string): CommandArgument;
                export function playerArg(name: any_string): CommandArgument;
                export function enumArg(name: any_string, enumName: any_string, defaultValue?: number): CommandArgument;
                export function stringEnumArg(name: any_string, enumName: any_string, defaultValue: any_string): CommandArgument;
                export function literal(l: any_string): CommandArgument;
                export function registerAlias(name: any_string, alias: any_string): void;
                export function addEnum(name: any_string, values: java.util.Map<any_string, number>): void;
                export function addEnum(name: any_string, values: {[key: string]: number}): void;
                export function addStringEnum(name: any_string, values: java.util.Set<any_string>): void;
                export function addStringEnum(name: any_string, values: any_string[]): void;
                export function newEnum(name: any_string): EnumBuilder;
                export function newStringEnum(name: any_string): StringEnumBuilder;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.CommandsModule"): typeof vsdum.kex.modules.CommandsModule;

declare module vsdum {
    export module kex {
        export module modules {
            export module ChunksModule {
                export interface LoadedRectangle {
                    start(x: number, z: number): LoadedRectangle;
                    end(x: number, z: number): LoadedRectangle;
                    load(): LoadedRectangle;
                    unload(): LoadedRectangle;
                    isLoaded(): boolean;
                }
                export interface LoadedCircle {
                    center(x: number, z: number): LoadedCircle;
                    radius(r: number): LoadedCircle;
                    load(): LoadedCircle;
                    unload(): LoadedCircle;
                    isLoaded(): boolean;
                }
                export function addLoadedRectangle(worldOrDimension: natives.WorldOrDimension, name?: any_string): LoadedRectangle;
                export function addLoadedCircle(worldOrDimension: natives.WorldOrDimension, name?: any_string): LoadedCircle;
                export function addLoadedChunk(worldOrDimension: natives.WorldOrDimension, x: number, z: number, name?: any_string): LoadedRectangle;
                export function areaExists(name: any_string, worldOrDimension: natives.WorldOrDimension): boolean;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.ChunksModule"): typeof vsdum.kex.modules.ChunksModule;

declare module vsdum {
    export module kex {
        export module modules {
            export module TileEntityModule {
                export interface TileEntityCreationCallback {
                    (pointer: number, type: number, pos: util.mcmath.BlockPos): BlockActor;
                }
                export function registerTileEntityType(typeName: any_string, callback: TileEntityCreationCallback): number;
                export function registerForBlock(blockID: number, type: number): void;
                export interface BlockActor extends common.INativeInterface {
                    networkEntityType: Nullable<NetworkEntityType>;
                    networkEntity: Nullable<NetworkEntity>;
                    networkData: Nullable<SyncedNetworkData>;
                    container: Nullable<ItemContainer>;
                    getBlockPos(): util.mcmath.BlockPos;
                    getDimension(): number;
                    updateBlockPos(): BlockActor;
                    getBlockState(): Nullable<states.BlockState>;
                    getWorld(): Nullable<natives.ExtendedBlockSource>;
                    hasWorld(): boolean;
                    getType(): number;
                    getLife(): number;
                    isClient(): boolean;
                    isServer(): boolean;
                    load(data: NBT.CompoundTag): void;
                    save(data: NBT.CompoundTag): boolean;
                    getUpdatePacket(): Nullable<NBT.CompoundTag>;
                    onUpdatePacket(packet: NBT.CompoundTag): void;
                    getUpdatePacketJSON(): Nullable<org.json.JSONObject>;
                    onUpdatePacketJSON(packet: org.json.JSONObject): void;
                    tick(): void;
                    isFinished(): boolean;
                    onChanged(): void;
                    isMovable(): boolean;
                    onPlace(): void;
                    onMove(): void;
                    onRemoved(): void;
                    triggerEvent(id: number, type: number): void;
                    onNeighborChanged(pos: util.mcmath.BlockPos): void;
                    getCustomName(): Nullable<jstring>;
                    setCustomName(customName: any_string): void;
                    getName(): Nullable<jstring>;
                    onChunkLoaded(): void;
                    onChunkUnloaded(): void;
                    onUse(player: natives.Player, side: number, vec: util.mcmath.Vec3d): boolean;
                    getScreenByName(container: ItemContainer, screenName: any_string): Nullable<UI.IWindow>;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.TileEntityModule"): typeof vsdum.kex.modules.TileEntityModule;

declare module vsdum {
    export module kex {
        export module modules {
            export module BiomesModule {
                export function setBiomeTranslationKey(biomeNameID: any_string, key: any_string): void;
                export function setModNameForBiome(biomeNameID: any_string, modName: any_string): void;
                export function getBiomeById(id: number): Nullable<BiomeInterface>;
                export function getBiomeByName(name: any_string): Nullable<BiomeInterface>;
                export function forEachBiome(callback: (biome: BiomeInterface) => void): void;
                export interface BiomeInterface {
                    getNumericID(): number;
                    getNameID(): jstring;
                    getTemperature(): number;
                    getDownfall(): number;
                    isHumid(): boolean;
                    isSnowCovered(): boolean;
                    isVanilla(): boolean;
                    isModded(): boolean;
                    getTranslationKey(): jstring;
                    getName(): jstring;
                    getModName(): jstring;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.BiomesModule"): typeof vsdum.kex.modules.BiomesModule;

declare module vsdum {
    export module kex {
        export module modules {
            export module states {
                export module properties {
                    export abstract class Property<T extends java.lang.Comparable<T>> extends java.lang.Object implements common.INativeInterface {
                        static class: java.lang.Class<Property<any>>;
                        getPointer(): number;
                        equals(other: any): boolean;
                        hashCode(): number;
                        generateHashCode(): number;
                        getName(): jstring;
                        getNumericID(): number;
                        getValueClass(): java.lang.Class<T>;
                        abstract getIndex(value: T): number;
                        abstract getPossibleValues(): java.util.Collection<T>;
                        abstract getValue(index: number): java.util.Optional<T>;
                    }
                    export class IntegerProperty extends Property<java.lang.Integer> {
                        equals(other: any): boolean;
                        generateHashCode(): number;
                        getPossibleValues(): java.util.Collection<java.lang.Integer>;
                        getIndex(value: java.lang.Integer): number;
                        getValue(index: number): java.util.Optional<java.lang.Integer>;
                        static create(name: any_string, min: number, max: number): IntegerProperty;
                    }
                    export class BooleanProperty extends Property<java.lang.Boolean> {
                        equals(other: any): boolean;
                        generateHashCode(): number;
                        getPossibleValues(): java.util.Collection<java.lang.Boolean>;
                        getIndex(value: java.lang.Boolean): number;
                        getValue(index: number): java.util.Optional<java.lang.Boolean>;
                        static create(name: any_string): BooleanProperty;
                    }
                    export class EnumProperty<T extends java.lang.Enum<T>> extends Property<T> {
                        equals(other: any): boolean;
                        generateHashCode(): number;
                        getPossibleValues(): java.util.Collection<T>;
                        getIndex(value: T): number;
                        getValue(index: number): java.util.Optional<T>;
                        toIntegerProperty(): IntegerProperty;
                    }
                }
                export class BlockState extends java.lang.Object {
                    static class: java.lang.Class<BlockState>;
                    constructor(id: number, data: number);
                    getRuntimeID(): number;
                    hasBlockEntity(): boolean;
                    getProperties(): java.util.Collection<properties.Property<any>>;
                    hasProperty<T extends java.lang.Comparable<T>>(property: properties.Property<T>): boolean;
                    getValue<T extends java.lang.Comparable<T>>(property: properties.Property<T>): T;
                    getOptionalValue<T extends java.lang.Comparable<T>>(properties: properties.Property<T>): java.util.Optional<T>;
                    setValue<T extends java.lang.Comparable<T>, V extends T>(property: properties.Property<T>, value: V): BlockState;
                    cycle<T extends java.lang.Comparable<T>>(property: properties.Property<T>): BlockState;
                    rotate(rotation: util.mcmath.Rotation): BlockState;
                    mirror(m: util.mcmath.Mirror): BlockState;
                    getFriction(): number;
                    getDestroySpeed(): number;
                    getLightBlock(): number;
                    getLightEmission(): number;
                }
                export module VanillaStates {
                    export const AGE_BIT: properties.BooleanProperty;
                    export const AGE: properties.IntegerProperty;
                    export const ATTACHED_BIT: properties.BooleanProperty;
                    export const PORTAL_AXIS: properties.EnumProperty<any>;
                    export const BITE_COUNTER: properties.IntegerProperty;
                    export const BREWING_STAND_SLOT_A_BIT: properties.BooleanProperty;
                    export const BREWING_STAND_SLOT_B_BIT: properties.BooleanProperty;
                    export const BREWING_STAND_SLOT_C_BIT: properties.BooleanProperty;
                    export const BUTTON_PRESSED_BIT: properties.BooleanProperty;
                    export const CONDITIONAL_BIT: properties.BooleanProperty;
                    export const COVERED_BIT: properties.BooleanProperty;
                    export const ANVIL_DAMAGE: properties.EnumProperty<any>;
                    export const DISARMED_BIT: properties.BooleanProperty;
                    export const DOOR_HINGE_BIT: properties.BooleanProperty;
                    export const UPPER_BLOCK_BIT: properties.BooleanProperty;
                    export const HORIZONTAL_FACING: properties.EnumProperty<any>;
                    export const END_PORTAL_EYE_BIT: properties.BooleanProperty;
                    export const EXPLODE_BIT: properties.BooleanProperty;
                    export const FACING_DIRECTION: properties.EnumProperty<any>;
                    export const CAULDRON_FILL_LEVEL: properties.IntegerProperty;
                    export const GROWTH: properties.IntegerProperty;
                    export const HEAD_PIECE_BIT: properties.BooleanProperty;
                    export const HEIGHT: properties.IntegerProperty;
                    export const INFINIBURN_BIT: properties.BooleanProperty;
                    export const IN_WALL_BIT: properties.BooleanProperty;
                    export const LIQUID_DEPTH: properties.IntegerProperty;
                    export const MOISTURIZED_AMOUNT: properties.IntegerProperty;
                    export const NO_DROP_BIT: properties.BooleanProperty;
                    export const KELP_AGE: properties.IntegerProperty;
                    export const OCCUPIED_BIT: properties.BooleanProperty;
                    export const OPEN_BIT: properties.BooleanProperty;
                    export const OUTPUT_SUBTRACT_BIT: properties.BooleanProperty;
                    export const OUTPUT_LIT_BIT: properties.BooleanProperty;
                    export const PERSISTENT_BIT: properties.BooleanProperty;
                    export const POWERED_BIT: properties.BooleanProperty;
                    export const RAIL_DATA_BIT: properties.BooleanProperty;
                    export const RAIL_DIRECTION: properties.EnumProperty<any>;
                    export const REDSTONE_SIGNAL: properties.IntegerProperty;
                    export const REPEATER_DELAY: properties.IntegerProperty;
                    export const SUSPENDED_BIT: properties.BooleanProperty;
                    export const TOGGLE_BIT: properties.BooleanProperty;
                    export const TOP_SLOT_BIT: properties.BooleanProperty;
                    export const TRIGGERED_BIT: properties.BooleanProperty;
                    export const UPDATE_BIT: properties.BooleanProperty;
                    export const UPSIDE_DOWN_BIT: properties.BooleanProperty;
                    export const VINE_DIRECTION_BITS: properties.IntegerProperty;
                    export const ALLOW_UNDERWATER_BIT: properties.BooleanProperty;
                    export const COLOR_BIT: properties.BooleanProperty;
                    export const DEAD_BIT: properties.BooleanProperty;
                    export const CLUSTER_COUNT: properties.IntegerProperty;
                    export const ITEM_FRAME_MAP_BIT: properties.BooleanProperty;
                    export const SAPLING_TYPE: properties.IntegerProperty;
                    export const TORCH_FACING_DIRECTION: properties.EnumProperty<any>;
                    export const DRAG_DOWN: properties.BooleanProperty;
                    export const TURTLE_EGG_COUNT: properties.IntegerProperty;
                    export const HATCH_LEVEL: properties.EnumProperty<any>;
                    export const GROUND_SIGN_DIRECTION: properties.IntegerProperty;
                    export const WEIRDO_DIRECTION: properties.IntegerProperty;
                    export const CORAL_DIRECTION: properties.IntegerProperty;
                    export const BLOCK_COLOR: properties.EnumProperty<any>;
                    export const BAMBOO_THICKNESS: properties.EnumProperty<any>;
                    export const BAMBOO_LEAF_SIZE: properties.EnumProperty<any>;
                    export const STABILITY: properties.IntegerProperty;
                    export const STABILITY_CHECK_BIT: properties.BooleanProperty;
                    export const WOOD_TYPE: properties.IntegerProperty;
                    export const STONE_TYPE: properties.IntegerProperty;
                    export const DIRT_TYPE: properties.IntegerProperty;
                    export const SAND_TYPE: properties.IntegerProperty;
                    export const OLD_LOG_TYPE: properties.IntegerProperty;
                    export const NEW_LOG_TYPE: properties.IntegerProperty;
                    export const CHISEL_TYPE: properties.IntegerProperty;
                    export const DEPRECATED: properties.IntegerProperty;
                    export const OLD_LEAF_TYPE: properties.IntegerProperty;
                    export const NEW_LEAF_TYPE: properties.IntegerProperty;
                    export const SPONGE_TYPE: properties.IntegerProperty;
                    export const SAND_STONE_TYPE: properties.IntegerProperty;
                    export const TALL_GRASS_TYPE: properties.IntegerProperty;
                    export const FLOWER_TYPE: properties.IntegerProperty;
                    export const STONE_SLAB_TYPE: properties.IntegerProperty;
                    export const STONE_SLAB_TYPE_2: properties.IntegerProperty;
                    export const STONE_SLAB_TYPE_3: properties.IntegerProperty;
                    export const STONE_SLAB_TYPE_4: properties.IntegerProperty;
                    export const MONSTER_EGG_STONE_TYPE: properties.IntegerProperty;
                    export const STONE_BRICK_TYPE: properties.IntegerProperty;
                    export const HUGE_MUSHROOM_BITS: properties.IntegerProperty;
                    export const WALL_BLOCK_TYPE: properties.IntegerProperty;
                    export const PRISMARINE_BLOCK_TYPE: properties.IntegerProperty;
                    export const DOUBLE_PLANT_TYPE: properties.IntegerProperty;
                    export const CHEMISTRY_TABLE_TYPE: properties.IntegerProperty;
                    export const SEA_GRASS_TYPE: properties.IntegerProperty;
                    export const CORAL_COLOR: properties.EnumProperty<any>;
                    export const CAULDRON_LIQUID_TYPE: properties.IntegerProperty;
                    export const HANGING_BIT: properties.BooleanProperty;
                    export const STRIPPED_BIT: properties.BooleanProperty;
                    export const CORAL_HANG_TYPE_BIT: properties.BooleanProperty;
                    export const BELL_ATTACHMENT: properties.EnumProperty<any>;
                    export const STRUCTURE_VOID_TYPE: properties.EnumProperty<any>;
                    export const STRUCTURE_BLOCK_TYPE: properties.EnumProperty<any>;
                    export const EXTINGUISHED: properties.BooleanProperty;
                    export const COMPOSTER_FILL_LEVEL: properties.IntegerProperty;
                    export const CORAL_FAN_DIRECTION: properties.IntegerProperty;
                    export const LEVER_DIRECTION: properties.EnumProperty<any>;
                    export const PILLAR_AXIS: properties.EnumProperty<any>;
                    export const BLOCK_LIGHT_LEVEL: properties.IntegerProperty;
                    export const HONEY_LEVEL: properties.IntegerProperty;
                    export const WEEPING_VINES_AGE: properties.IntegerProperty;
                    export const WALL_POST_BIT: properties.BooleanProperty;
                    export const WALL_CONNECTION_TYPE_NORTH: properties.EnumProperty<any>;
                    export const WALL_CONNECTION_TYPE_EAST: properties.EnumProperty<any>;
                    export const WALL_CONNECTION_TYPE_SOUTH: properties.EnumProperty<any>;
                    export const WALL_CONNECTION_TYPE_WEST: properties.EnumProperty<any>;
                    export const ROTATION: properties.IntegerProperty;
                    export const TWISTING_VINES_AGE: properties.IntegerProperty;
                    export const RESPAWN_ANCHOR_CHARGE: properties.IntegerProperty;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.states.properties.IntegerProperty"): typeof vsdum.kex.modules.states.properties.IntegerProperty;
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.states.properties.BooleanProperty"): typeof vsdum.kex.modules.states.properties.BooleanProperty;
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.states.BlockState"): typeof vsdum.kex.modules.states.BlockState;
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.states.VanillaStates"): typeof vsdum.kex.modules.states.VanillaStates;

declare module vsdum {
    export module kex {
        export class KernelExtension extends java.lang.Object {
            static class: java.lang.Class<KernelExtension>;
            static getVersion(): [number, number, number];
            static getVersionCode(): number;
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.KernelExtension"): typeof vsdum.kex.KernelExtension;

declare module vsdum {
    export module kex {
        export module util {
            export class AddonUtils extends java.lang.Object {
                static class: java.lang.Class<AddonUtils>;
                static getAddonItemIdentifier(id: number): jstring;
                static getAddonItemIdentifier(namespace: any_string, identifier: any_string): jstring;
                static getBlockNameId(id: number): Nullable<jstring>;
                static getNumericIdFromIdentifier(identifier: any_string): number;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.util.AddonUtils"): typeof vsdum.kex.util.AddonUtils;

declare module vsdum {
    export module kex {
        export module util {
            export module TextureWorker {
                interface OverlaidTextureBuilder {
                    bitmap(width: number, height: number, config?: android.graphics.Bitmap.Config): OverlaidTextureBuilder;
                    overlay(path: any_string, name: any_string): OverlaidTextureBuilder;
                    overlay(path: any_string, name: any_string, colorR: number, colorG: number, colorB: number, colorA?: number): OverlaidTextureBuilder;
                    overlay(bitmap: android.graphics.Bitmap): OverlaidTextureBuilder;
                    overlay(bitmap: android.graphics.Bitmap, colorR: number, colorG: number, colorB: number, colorA?: number): OverlaidTextureBuilder;
                    result(path: any_string, name: any_string): OverlaidTextureBuilder;
                    create(): Nullable<android.graphics.Bitmap>;
                }
                interface PaintedTextureBuilder {
                    bitmap(width: number, height: number, config?: android.graphics.Bitmap.Config): PaintedTextureBuilder;
                    source(path: any_string, name: any_string): PaintedTextureBuilder;
                    source(bitmap: android.graphics.Bitmap): PaintedTextureBuilder;
                    color(r: number, g: number, b: number, a?: number): PaintedTextureBuilder;
                    result(path: any_string, name: any_string): PaintedTextureBuilder;
                    create(): Nullable<android.graphics.Bitmap>;
                }
                interface GrayscaledTextureBuilder {
                    source(path: any_string, name: any_string): GrayscaledTextureBuilder;
                    source(src: android.graphics.Bitmap): GrayscaledTextureBuilder;
                    result(path: any_string, name: any_string): GrayscaledTextureBuilder;
                    create(): Nullable<android.graphics.Bitmap>;
                }
                export function changeBitmapColor(source: android.graphics.Bitmap, colorR: number, colorG: number, colorB: number, colorA?: number): android.graphics.Bitmap;
                export function changeBitmapColor(source: android.graphics.Bitmap, color: number): android.graphics.Bitmap;
                export function createTextureWithOverlays(): OverlaidTextureBuilder;
                export function createPaintedTexture(): PaintedTextureBuilder;
                export function createGrayscaledTexture(): GrayscaledTextureBuilder;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.util.TextureWorker"): typeof vsdum.kex.util.TextureWorker;

declare module vsdum {
    export module kex {
        export module util {
            export module ItemAnimHelper {
                export function convertTexture(sourcePath: any_string, resultPath: any_string): void;
                export function makeCommonAnim(id: number, textureName: any_string, ticks: number, frames: number): void;
                export function makeAdvancedAnim(id: number, textureName: any_string, interval: number, frames: number[]): void;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.util.ItemAnimHelper"): typeof vsdum.kex.util.ItemAnimHelper;

declare module vsdum {
    export module kex {
        export module modules {
            export module misc {
                export class ReachDistanceModifier extends java.lang.Object {
                    static class: java.lang.Class<ReachDistanceModifier>;
                    constructor();
                    setModifier(modifier: number): ReachDistanceModifier;
                    setMultiplier(multiplier: number): ReachDistanceModifier;
                    enable(): ReachDistanceModifier;
                    disable(): ReachDistanceModifier;
                    getModifier(): number;
                    getMultiplier(): number;
                    isActive(): boolean;
                }
                export class CameraRollModifier extends java.lang.Object {
                    static class: java.lang.Class<CameraRollModifier>;
                    constructor();
                    setModifier(modifier: number): CameraRollModifier;
                    setInterpolationEnabled(enabled: boolean): CameraRollModifier;
                    setSmoothing(smoothing: number): CameraRollModifier;
                    enable(): CameraRollModifier;
                    disable(): CameraRollModifier;
                    getModifier(): number;
                    isInterpolationEnabled(): boolean;
                    getSmoothing(): number;
                    isActive(): boolean;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.misc.ReachDistanceModifier"): typeof vsdum.kex.modules.misc.ReachDistanceModifier;
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.misc.CameraRollModifier"): typeof vsdum.kex.modules.misc.CameraRollModifier;


declare module vsdum {
    export module kex {
        export module modules {
            export module misc {
                export module SmithingTableRecipes {
                    interface SmithingTableRecipe {
                        readonly baseID: number;
                        readonly additionID: number;
                        readonly resultID: number;
                    }
                    export function addRecipe(baseID: number, additionID: number, resultID: number): void;
                    export function removeRecipe(baseID: number, additionID: number): void;
                    export function getRecipesByResult(resultID: number): java.util.Set<SmithingTableRecipe>;
                    export function getRecipesByBase(baseID: number): java.util.Set<SmithingTableRecipe>;
                    export function getAllRecipes(): java.util.Set<SmithingTableRecipe>;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.misc.SmithingTableRecipes"): typeof vsdum.kex.modules.misc.SmithingTableRecipes;


declare namespace Item {
    interface FoodParamsDescription {
        stack?: number,
        isTech?: boolean,
        food?: number,
        nutrition?: number,
        saturation_modifier?: "poor" | "low" | "normal" | "good" | "max" | "supernatural",
        is_meat?: boolean,
        can_always_eat?: boolean,
        cooldown_time?: number,
        cooldown_type?: "chorusfruit" | "none",
        on_use_range?: [ number, number, number ],
        on_use_action?: "chorus_teleport" | "suspicious_stew_effect" | "none",
        using_converts_to?: any_string,
        effects?: {
            name?: Lowercase<keyof typeof EPotionEffect> | any_string,
            duration?: number,
            amplifier?: number,
            chance?: number
        }[]
    }
    function createFoodItem(nameID: string, name: string, texture: TextureData, params: FoodParamsDescription): NativeItem;
    function createSwordItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void;
    function createAxeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void;
    function createPickaxeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void;
    function createShovelItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void;
    function createHoeItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }): void;
    function createShearsItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial, durability?: number }): void;
    function createFlintAndSteelItem(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, durability?: number }): void;
    function createCustomTool(id: string, name: string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: string | ToolAPI.ToolMaterial }, toolParams?: vsdum.kex.modules.ExtendedToolParams, numericId?: number): void;
}


declare namespace Callback {
    export function addCallback(name: "KEX-InnerCoreIdsCached", func: () => void, priority?: number): void;
    export function addCallback(name: "PlayerJump", func: (player: number) => void, priority?: number): void;
    export function addCallback(name: "GameModeChanged", func: (mode: number) => void, priority?: number): void;
    export function addCallback(name: "ChangeCarriedItem", func: (player: number, oldItem: ItemInstance, newItem: ItemInstance, hand: 0 | 1) => void, priority?: number): void;
    export function addCallback(name: "EntitySneakChanged", func: (entity: number, sneaking: boolean) => void, priority?: number): void;
    export function addCallback(name: "ItemTooltip", func: vsdum.kex.modules.OnTooltipCallback, priority?: number): void;
    export function addCallback(name: "BlockEventEntityStepOff", func: Block.EntityStepOffFunction, priority?: number): void;
    export function addCallback(name: "BiomesInitialized", func: () => void, priority?: number): void;
    export var on: typeof addCallback;
    export var once: typeof addCallback;
    export var off: typeof addCallback;
}


declare namespace Commands {
    interface Argument<T, D, I> {
        label: string,
        type: T | I,
        default?: D,
        optional?: boolean;
    }
    type IntArgument = Argument<"int" | "integer", number, 0>;
    type FloatArgument = Argument<"float", number, 1>;
    type BoolArgument = Argument<"bool" | "boolean", boolean ,2>;
    type RelativeFloatArgument = Argument<"relfloat" | "relativefloat", number, 3>;
    type PositionArgument = Argument<"pos" | "position", Vector, 4>;
    type FloatPositionArgument = Argument<"floatpos" | "floatposition", Vector, 5>;
    type StringArgument = Argument<"str" | "string", string, 6>;
    type MessageArgument = Argument<"msg" | "message", never, 7>;
    type JsonArgument = Argument<"json", never, 8>;
    type EntityArgument = Argument<"entity", never, 9>;
    type PlayerArgument = Argument<"player", never, 10>;
    interface EnumArgument extends Argument<"enum", number, 11> {
        name: string;
    }
    interface StringEnumArgument extends Argument<"strenum" | "stringenum", string, 12> {
        name: string,
        default: string;
    }
    type LiteralArgument = Argument<"literal", never, 13>;
    type Arguments =
        IntArgument |
        FloatArgument |
        BoolArgument |
        RelativeFloatArgument |
        PositionArgument |
        FloatPositionArgument |
        StringArgument |
        MessageArgument |
        JsonArgument |
        EntityArgument |
        PlayerArgument |
        EnumArgument |
        StringEnumArgument |
        LiteralArgument;
    type RelativeFloat = (center?: number) => number;
    interface ExecuteCallback {
        (args: object, context: vsdum.kex.modules.CommandsModule.CommandContext): void;
    }
    interface CustomCommandBuilder {
        addOverload(args: Arguments[], callback: ExecuteCallback): CustomCommandBuilder;
        setDescription(translations: object): CustomCommandBuilder;
        setDescription(desc: string): CustomCommandBuilder;
        register(): void;
    }
    export function newEnum(enumName: string): vsdum.kex.modules.CommandsModule.EnumBuilder;
    export function newStringEnum(enumName: string): vsdum.kex.modules.CommandsModule.StringEnumBuilder;
    export function create(commandName: string, permissionLevel?: number): CustomCommandBuilder;
}


declare namespace Recipes {
    type SmithingTableRecipe = vsdum.kex.modules.misc.SmithingTableRecipes.SmithingTableRecipe;
    export function addSmithingTableRecipe(baseID: number, additionID: number, resultID: number): void;
    export function removeSmithingTableRecipe(baseID: number, additionID: number): void;
    export function getSmithingTableRecipesByResult(resultID: number): SmithingTableRecipe[];
    export function getSmithingTableRecipesByBase(baseID: number): SmithingTableRecipe[];
    export function getAllSmithingTableRecipes(): SmithingTableRecipe[];
}


declare namespace Block {
    type ComparatorSignalFunction = vsdum.kex.modules.BlocksModule.ComparatorSignalCallbackJS;
    type EntityStepOffFunction = EntityStepOnFunction;
    export function registerComparatorSignalFunctionForID(id: number, func: ComparatorSignalFunction, isCallbackForced?: boolean): void;
    export function registerComparatorSignalFunction(id: string | number, func: ComparatorSignalFunction, isCallbackForced?: boolean): void;
    export function registerEntityStepOffFunctionForID(id: number, func: EntityStepOffFunction): void;
    export function registerEntityStepOffFunction(id: string | number, func: EntityStepOffFunction): void;
    export function getLightLevel(id: number, data?: number): number;
    export function setLightLevel(id: number, lightLevel: number): void;
    export function setLightLevel(id: number, data: number, lightLevel: number): void;
}


declare enum EItemAnimation {
    NONE = 0,
    EAT = 1,
    DRINK = 2,
    BLOCK = 3,
    CAMERA = 5,
    SPEAR = 6,
    CROSSBOW = 9
}


declare enum ETileEntityType {
    NETHER_REACTOR = 3,
    SIGN = 4,
    MOB_SPAWNER = 5,
    SKULL = 6,
    FLOWER_POT = 7,
    ENCHANTING_TABLE = 9,
    DAYLIGHT_DETECTOR = 10,
    MUSIC_BLOCK = 11,
    COMPARATOR = 12,
    DROPPER = 14,
    ITEM_FRAME = 17,
    PISTON = 18,
    CHALKBOARD = 20,
    END_PORTAL = 22,
    END_GATEWAY = 24,
    COMMAND_BLOCK = 26,
    BED = 27,
    BANNER = 28,
    STRUCTURE_BLOCK = 32,
    CHEMISTRY_TABLE = 34,
    CONDUIT_BLOCK = 35,
    JIGSAW = 36,
    BLAST_FURNACE = 38,
    SMOKER = 39,
    BELL = 40,
    CAMPFIRE = 41,
    BARREL = 42,
    BEEHIVE = 43,
    LODESTONE = 44,
    // SHULKER_BOX = ???,
    // ENDER_CHEST = ???,
}


/**
 * Interface you can use in case you inject KEX API
 * into some variable and not into the global mod scope.
 * For example, if you inject API like this:
 * ```js
 * ModAPI.addAPICallback("KernelExtension", api => {
 *     Launch({ KEX: api });
 * });
 * ```
 * You can then write this at the top of the code:
 * ```ts
 * declare var KEX: KEXAPI;
 * // and then access like `KEX.LootModule.createLootTableModifier(...)`
 * ```
 */
 declare interface KEXAPI {
    ItemsModule: typeof vsdum.kex.modules.ItemsModule,
    LootModule: typeof vsdum.kex.modules.LootModule,
    ToolsModule: typeof vsdum.kex.modules.ToolsModule,
    DamageModule: typeof vsdum.kex.modules.DamageModule,
    CommandsModule: typeof vsdum.kex.modules.CommandsModule,
    TileEntityModule: typeof vsdum.kex.modules.TileEntityModule,
    BlocksModule: typeof vsdum.kex.modules.BlocksModule,
    LootTableContext: typeof vsdum.kex.natives.LootTableContext,
    MobEffect: typeof vsdum.kex.natives.MobEffect,
    MobEffectInstance: typeof vsdum.kex.natives.MobEffectInstance,
    Actor: typeof vsdum.kex.natives.Actor,
    Mob: typeof vsdum.kex.natives.Mob,
    Player: typeof vsdum.kex.natives.Player,
    LocalPlayer: typeof vsdum.kex.natives.LocalPlayer,
    Slime: typeof vsdum.kex.natives.Slime,
    GlobalContext: typeof vsdum.kex.natives.GlobalContext,
    I18n: typeof vsdum.kex.natives.I18n;
    AddonUtils: typeof vsdum.kex.util.AddonUtils,
    FoodItemComponent: typeof vsdum.kex.natives.FoodItemComponent,
    ReachDistanceModifier: typeof vsdum.kex.modules.misc.ReachDistanceModifier,
    CameraRollModifier: typeof vsdum.kex.modules.misc.CameraRollModifier,
    TextureWorker: typeof vsdum.kex.util.TextureWorker,
    ItemAnimHelper: typeof vsdum.kex.util.ItemAnimHelper,
    ESaturationModifier: {
        readonly POOR: 0.2,
        readonly LOW: 0.6,
        readonly NORMAL: 1.2,
        readonly GOOD: 1.6,
        readonly MAX: 2.0,
        readonly SUPERNATURAL: 2.4
    },
    EDamageCause: {
        readonly NONE: -1,
        readonly OVERRIDE: 0,
        readonly CONTACT: 1,
        readonly ENTITY_ATTACK: 2,
        readonly PROJECTILE: 3,
        readonly SUFFOCATION: 4,
        readonly FALL: 5,
        readonly FIRE: 6,
        readonly FIRE_TICK: 7,
        readonly LAVA: 8,
        readonly DROWNING: 9,
        readonly BLOCK_EXPLOSION: 10,
        readonly ENTITY_EXPLOSION: 11,
        readonly VOID: 12,
        readonly SUICIDE: 13,
        readonly MAGIC: 14,
        readonly WITHER: 15,
        readonly STARVE: 16,
        readonly ANVIL: 17,
        readonly THORNS: 18,
        readonly FALLING_BLOCK: 19,
        readonly PISTON: 20,
        readonly FLY_INTO_WALL: 21,
        readonly MAGMA: 22,
        readonly FIREWORKS: 23,
        readonly LIGHTNING: 24,
        readonly CHARGING: 25,
        readonly TEMPERATURE: 26,
        readonly ALL: 31
    },
    EArgumentType: {
        readonly INT: 0,
        readonly FLOAT: 1,
        readonly BOOL: 2,
        readonly RELATIVE_FLOAT: 3,
        readonly POSITION: 4,
        readonly FLOAT_POSITION: 5,
        readonly STRING: 6,
        readonly MESSAGE: 7,
        readonly JSON: 8,
        readonly ENTITY: 9,
        readonly PLAYER: 10,
        readonly ENUM: 11,
        readonly STRING_ENUM: 12,
        readonly LITERAL: 13
    },
    getKEXVersion: () => [ number, number, number ],
    getKEXVersionCode: () => number;
}