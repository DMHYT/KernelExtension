package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.natives.Actor;
import vsdum.kex.natives.ExtendedBlockSource;
import vsdum.kex.util.mcmath.BlockPos;

public interface IStepOffListener {

    public void stepOff(ExtendedBlockSource world, BlockPos pos, BlockState state, Actor entity);

}
