package vsdum.kex.japi.blocks.components;

import vsdum.kex.modules.states.BlockState;
import vsdum.kex.util.mcmath.Mirror;

public interface IMirrorable {

    public BlockState mirror(BlockState state, Mirror m);

}
