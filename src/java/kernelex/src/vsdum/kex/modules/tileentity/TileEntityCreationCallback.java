package vsdum.kex.modules.tileentity;

import vsdum.kex.util.mcmath.BlockPos;

public interface TileEntityCreationCallback {
    
    public BlockActor create(long ptr, int type, BlockPos pos);

}
