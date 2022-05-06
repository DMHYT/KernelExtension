/// <reference path="core-engine.d.ts" />


declare type jstring = java.lang.String;
declare type any_string = string | jstring;

declare module com {
    export module zhekasmirnov {
        export module innercore {
            export module api {
                export class NativeItemInstance extends java.lang.Object {
                    static class: java.lang.Class<NativeItemInstance>;
                    count: number;
                    data: number;
                    extra: Nullable<NativeItemInstanceExtra>;
                    id: number;
                    isValid: boolean;
                    constructor(ptr: number);
                    constructor(id: number, count: number, data: number);
                    getPointer(): number;
                    destroy(): void;
                    toString(): string;
                }
            }
        }
    }
}


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
                getTickingArea(): Nullable<TickingArea>;
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
                getRegion(): Nullable<BlockSource>;
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
                dropTowards(stack: com.zhekasmirnov.innercore.api.NativeItemInstance, x: number, y: number, z: number): void;
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
                setArmor(slot: number, stack: com.zhekasmirnov.innercore.api.NativeItemInstance): void;
                getArmorMaterialTypeInSlot(slot: number): number;
                getArmorMaterialTextureTypeInSlot(slot: number): number;
                getEquippedSlot(slot: number): Nullable<ItemInstance>;
                setEquippedSlot(slot: number, stack: com.zhekasmirnov.innercore.api.NativeItemInstance): void;
                getCarriedItem(): Nullable<ItemInstance>;
                setCarriedItem(stack: com.zhekasmirnov.innercore.api.NativeItemInstance): void;
                setOffhandSlot(stack: com.zhekasmirnov.innercore.api.NativeItemInstance): void;
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
                add(stack: com.zhekasmirnov.innercore.api.NativeItemInstance): void;
                drop(stack: com.zhekasmirnov.innercore.api.NativeItemInstance, someBool: boolean): void;
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
                setItemSlot(slot: number, instance: com.zhekasmirnov.innercore.api.NativeItemInstance): void;
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
                canPickUpLoot(item: com.zhekasmirnov.innercore.api.NativeItemInstance): boolean;
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
                constructor(id: number, duration: number, amplifier: number, isAmbient: boolean, isVisible: boolean, displaysOnScreenTextureAnimation: boolean);
                getId(): number;
                getEffect(): Nullable<MobEffect>;
                getAmplifier(): number;
                isAmbient(): boolean;
                isVisible(): boolean;
                displaysOnScreenTextureAnimation(): boolean;
                isNoCounter(): boolean;
                getDuration(): number;
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.MobEffectInstance"): typeof vsdum.kex.natives.MobEffectInstance;

declare module vsdum {
    export module kex {
        export module natives {
            export class TickingArea extends common.INativeInterface {
                static class: java.lang.Class<TickingArea>;
                constructor(pointer: number);
            }
        }
    }
}

declare module vsdum {
    export module kex {
        export module natives {
            export class FoodItemComponent extends java.lang.Object {
                static class: java.lang.Class<FoodItemComponent>;
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
            }
        }
    }
}

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
                    create(): Nullable<LootTableContext>;
                }
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.LootTableContext"): typeof vsdum.kex.natives.LootTableContext;

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
                static addOnDropCallbackFor(tableName: any_string, cb: OnDropCallback): void;
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
                createNewPool(): LootPool;
                createNewPool(rolls: number): LootPool;
                createNewPool(minRolls: number, maxRolls: number): LootPool;
                modifyWithAnotherLootTable(path: any_string): LootModifier;
                modifyWithJSON(json: LootTableTypes.JsonFormat): LootModifier;
                addItem(id: number, count: number | MinMax, data: number, chance: number, rolls?: number | MinMax): LootModifier;
                addAddonItem(namespace: any_string, identifier: any_string, count: number | MinMax, data: number, chance: number, rolls?: number | MinMax): LootModifier;
                addJSModifyCallback(cb: JSModifyCallback): LootModifier;
                addJSONModifyCallback(cb: JSONModifyCallback): LootModifier;
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
                addRandomRegionalDifficultyChanceCondition(defaultChance: number, easy?: number, normal?: number, hard?: number, peaceful?: number): LootConditions;
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
                addBannerDetailsFunction(type: number): LootEntryFunctions;
                addBookContentsFunction(author: any_string, title: any_string, pages: any_string[]): LootEntryFunctions;
                addDataFromColorIndexFunction(): LootEntryFunctions;
                addLoreFunction(lore: any_string[]): LootEntryFunctions;
                addSpecificEnchantsFunction(enchants: java.util.Map<jstring, number>): LootEntryFunctions;
                addTraderMaterialTypeFunction(): LootEntryFunctions;
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
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.modules.ItemsModule"): typeof vsdum.kex.modules.ItemsModule;

declare module vsdum {
    export module kex {
        export module modules {
            interface ExtendedToolParams extends ToolAPI.ToolParams {
                getAttackDamageBonus?: (item: ItemInstance) => number;
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
                static getDestroyTimeViaTool(block: Tile, x: number, y: number, z: number, side: number, itemID: number, itemCount: number, itemData: number, itemExtra: Nullable<com.zhekasmirnov.innercore.api.NativeItemInstanceExtra>): number;
                static registerCustomTool(id: number, nameId: any_string, name: any_string, textureName: any_string, textureMeta: number, tier: ToolsModule.ItemTier, isTech: boolean, isWeapon: boolean, blockMaterials: Nullable<any_string[]>, brokenId: number, baseAttackDamage: number, enchantType: number, toolData: ExtendedToolParams): void;
                static destroyBlockHook(coords: Callback.ItemUseCoordinates, block: Tile, item: ItemInstance, player: number): void;
                static playerAttackHook(attacker: number, victim: number, item: ItemInstance): void;
                static useCustomShearsOn(x: number, y: number, z: number, side: number, rx: number, ry: number, rz: number, actorUID: number): void;
                static useCustomFlintAndSteelOn(x: number, y: number, z: number, side: number, rx: number, ry: number, rz: number, actorUID: number): void;
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
    function createFoodItem(nameID: any_string, name: any_string, texture: TextureData, params: FoodParamsDescription): NativeItem;
    function createSwordItem(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: any_string | ToolAPI.ToolMaterial }): void;
    function createAxeItem(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: any_string | ToolAPI.ToolMaterial }): void;
    function createPickaxeItem(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: any_string | ToolAPI.ToolMaterial }): void;
    function createShovelItem(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: any_string | ToolAPI.ToolMaterial }): void;
    function createHoeItem(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: any_string | ToolAPI.ToolMaterial }): void;
    function createShearsItem(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: any_string | ToolAPI.ToolMaterial, durability?: number }): void;
    function createFlintAndSteelItem(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, durability?: number }): void;
    function createCustomTool(id: any_string, name: any_string, texture: TextureData, params: { stack?: number, isTech?: boolean, tier?: any_string | ToolAPI.ToolMaterial }, toolParams?: vsdum.kex.modules.ExtendedToolParams, numericId?: number): void;
}


declare namespace Callback {
    export function addCallback(name: "KEX-InnerCoreIdsCached", func: () => void, priority?: number): void;
    export function addCallback(name: "PlayerJump", func: (player: number) => void, priority?: number): void;
    export function addCallback(name: "GameModeChanged", func: (mode: number) => void, priority?: number): void;
    export var on: typeof addCallback;
    export var once: typeof addCallback;
    export var off: typeof addCallback;
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
    LootTableContext: typeof vsdum.kex.natives.LootTableContext,
    MobEffect: typeof vsdum.kex.natives.MobEffect,
    MobEffectInstance: typeof vsdum.kex.natives.MobEffectInstance,
    Actor: typeof vsdum.kex.natives.Actor,
    Mob: typeof vsdum.kex.natives.Mob,
    Player: typeof vsdum.kex.natives.Player,
    LocalPlayer: typeof vsdum.kex.natives.LocalPlayer,
    Slime: typeof vsdum.kex.natives.Slime,
    GlobalContext: typeof vsdum.kex.natives.GlobalContext,
    AddonUtils: typeof vsdum.kex.util.AddonUtils,
    ESaturationModifier: {
        readonly POOR: 0.2,
        readonly LOW: 0.6,
        readonly NORMAL: 1.2,
        readonly GOOD: 1.6,
        readonly MAX: 2.0,
        readonly SUPERNATURAL: 2.4
    },
    getKEXVersion: () => [ number, number, number ],
    getKEXVersionCode: () => number;
}