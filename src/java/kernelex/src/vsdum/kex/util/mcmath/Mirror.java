package vsdum.kex.util.mcmath;

public enum Mirror {

    NONE,
    LEFT_RIGHT,
    FRONT_BACK;

    // todo understand
    public int mirror(int k, int l)
    {
        int i = l / 2;
        int j = k > i ? k - l : k;
        switch(this) {
            case FRONT_BACK: return (l - j) % l;
            case LEFT_RIGHT: return (i - j + l) % l;
            default: return k;
        }
    }

    public Rotation getRotation(Direction dir)
    {
        Direction.Axis axis = dir.getAxis();
        return (this != LEFT_RIGHT || axis != Direction.Axis.Z) && (this != FRONT_BACK || axis != Direction.Axis.X)
            ? Rotation.NONE : Rotation.CLOCKWISE_180;
    }

    public Direction mirror(Direction dir)
    {
        if(this == FRONT_BACK && dir.getAxis() == Direction.Axis.X) return dir.getOpposite();
        else return this == LEFT_RIGHT && dir.getAxis() == Direction.Axis.Z ? dir.getOpposite() : dir;
    }
    
}
