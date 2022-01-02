/// <reference path="core-engine.d.ts" />


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
                constructor(entity: number);
                constructor(pointer: number, flagForPointerOverload: boolean);
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
                hasFamily(family: string): boolean;
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
                dropTowards(stack: ItemStack, x: number, y: number, z: number): void;
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
                hasComponent(component: string): boolean;
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
                getArmor(slot: number): Nullable<ItemStack>;
                setArmor(slot: number, stack: ItemStack): void;
                getArmorMaterialTypeInSlot(slot: number): number;
                getArmorMaterialTextureTypeInSlot(slot: number): number;
                getEquippedSlot(slot: number): Nullable<ItemStack>;
                setEquippedSlot(slot: number, stack: ItemStack): void;
                getCarriedItem(): Nullable<ItemStack>;
                setCarriedItem(stack: ItemStack): void;
                setOffhandSlot(stack: ItemStack): void;
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
                add(stack: ItemStack): void;
                drop(stack: ItemStack, someBool: boolean): void;
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
            }
        }
    }
}
declare function WRAP_JAVA(clazz: "vsdum.kex.natives.Actor"): typeof vsdum.kex.natives.Actor;

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
            export class ItemStack extends common.INativeInterface {
                static class: java.lang.Class<ItemStack>;
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
            }
        }
    }
}

declare module vsdum {
    export module kex {
        export module natives {
            export class MobEffectInstance extends common.INativeInterface {
                static class: java.lang.Class<MobEffectInstance>;
                constructor(pointer: number);
            }
        }
    }
}

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

type MinMax = { min: number, max: number }

declare module vsdum {
    export module kex {
        export module modules {
            export class LootModule extends java.lang.Object {
                static class: java.lang.Class<LootModule>;
                static createLootTableModifier(tableName: string): LootModifier;
                static createConditionsList(): LootConditions;
            }
            export interface LootModifier {
                createNewPool(): LootPool;
                createNewPool(rolls: number): LootPool;
                createNewPool(minRolls: number, maxRolls: number): LootPool;
                modifyWithAnotherLootTable(path: string): LootModifier;
                addItem(id: number, count: number | MinMax, data: number, chance: number, rolls?: number | MinMax): LootModifier;
                addAddonItem(namespace: string, identifier: string, count: number | MinMax, data: number, chance: number, rolls?: number | MinMax): LootModifier;
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
                describeItem(namespace: string, identifier: string): LootEntry;
                setCount(count: number): LootEntry;
                setCount(min: number, max: number): LootEntry;
                setData(data: number): LootEntry;
                setData(minData: number, maxData: number): LootEntry;
                setDamage(damage: number): LootEntry;
                setDamage(minDamage: number, maxDamage: number): LootEntry;
                setCustomName(name: string): LootEntry;
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
                addExplorationMapFunction(destination: string): LootEntryFunctions;
                addFillContainerFunction(lootTable: string): LootEntryFunctions;
                addFurnaceSmeltFunction(conditions?: LootConditions): LootEntryFunctions;
                addLootingEnchantFunction(): LootEntryFunctions;
                addLootingEnchantFunction(minCount: number, maxCount: number): LootEntryFunctions;
                addRandomAuxValueFunction(): LootEntryFunctions;
                addRandomAuxValueFunction(minValue: number, maxValue: number): LootEntryFunctions;
                addRandomDyeFunction(): LootEntryFunctions;
                addActorIdFunction(actorId: string): LootEntryFunctions;
                addBannerDetailsFunction(type: number): LootEntryFunctions;
                addBookContentsFunction(author: string, title: string, pages: string[]): LootEntryFunctions;
                addDataFromColorIndexFunction(): LootEntryFunctions;
                addLoreFunction(lore: string[]): LootEntryFunctions;
                addSpecificEnchantsFunction(enchants: java.util.Map<string, number>): LootEntryFunctions;
                addTraderMaterialTypeFunction(): LootEntryFunctions;
                endFunctions(): LootEntry;
            }
        }
    }
}