package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.util.mcmath.Rotation;

public interface IRotatable {

    public BlockState rotate(BlockState state, Rotation rotation);

}
