package vsdum.kex.japi.blocks.components;

public interface ITechBlock {

    public boolean isTech(int meta);

    public default boolean isInCreative(int meta)
    {
        return !this.isTech(meta);
    }

}
