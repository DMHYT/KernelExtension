package vsdum.kex.util.mcmath;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Random;

import android.support.annotation.Nullable;
import vsdum.kex.common.IStringSerializable;

public enum Direction implements IStringSerializable {
    
    DOWN(0, 1, -1, "down", AxisDirection.NEGATIVE, Axis.Y, new Vec3i(0, -1, 0)),
    UP(1, 0, -1, "up", AxisDirection.POSITIVE, Axis.Y, new Vec3i(0, 1, 0)),
    NORTH(2, 3, 2, "north", AxisDirection.NEGATIVE, Axis.Z, new Vec3i(0, 0, -1)),
    SOUTH(3, 2, 0, "south", AxisDirection.POSITIVE, Axis.Z, new Vec3i(0, 0, 1)),
    WEST(4, 5, 1, "west", AxisDirection.NEGATIVE, Axis.X, new Vec3i(-1, 0, 0)),
    EAST(5, 4, 3, "east", AxisDirection.POSITIVE, Axis.X, new Vec3i(1, 0, 0));

    private final int index;
    private final int opposite;
    private final int horizontalIndex;
    private final String name;
    private final Axis axis;
    private final AxisDirection axisDirection;
    private final Vec3i directionVec;

    public static final Direction[] VALUES = new Direction[6];
    private static final Direction[] HORIZONTALS = new Direction[4];
    private static final Map<String, Direction> NAME_LOOKUP = new HashMap<>();

    private Direction(int index, int opposite, int horizontalIndex, String name, AxisDirection axisDirection, Axis axis, Vec3i directionVec)
    {
        this.index = index;
        this.horizontalIndex = horizontalIndex;
        this.opposite = opposite;
        this.name = name;
        this.axis = axis;
        this.axisDirection = axisDirection;
        this.directionVec = directionVec;
    }

    public int getIndex()
    {
        return this.index;
    }

    public int getHorizontalIndex()
    {
        return this.horizontalIndex;
    }

    public AxisDirection getAxisDirection()
    {
        return this.axisDirection;
    }

    public Direction getOpposite()
    {
        return VALUES[this.opposite];
    }

    public Direction rotateAround(Axis axis)
    {
        switch(axis)
        {
            case X:
                if(this != WEST && this != EAST) return this.rotateX();
                return this;
            case Y:
                if(this != UP && this != DOWN) return this.rotateY();
                return this;
            case Z:
                if(this != NORTH && this != SOUTH) return this.rotateZ();
                return this;
            default:
                throw new IllegalStateException("Unable to get CW facing for axis " + axis);
        }
    }

    public Direction rotateY()
    {
        switch(this)
        {
            case NORTH: return EAST;
            case EAST: return SOUTH;
            case SOUTH: return WEST;
            case WEST: return NORTH;
            default:
                throw new IllegalStateException("Unable to get Y-rotated facing of " + this);
        }
    }

    private Direction rotateX()
    {
        switch(this)
        {
            case NORTH: return DOWN;
            case EAST: case WEST: default:
                throw new IllegalStateException("Unable to get X-rotated facing of " + this);
            case SOUTH: return UP;
            case UP: return NORTH;
            case DOWN: return SOUTH;
        }
    }

    private Direction rotateZ()
    {
        switch(this)
        {
            case EAST: return DOWN;
            case SOUTH: default:
                throw new IllegalStateException("Unable to get Z-rotated facing of " + this);
            case WEST: return UP;
            case UP: return EAST;
            case DOWN: return WEST;
        }
    }

    public Direction rotateYCCW()
    {
        switch(this)
        {
            case NORTH: return WEST;
            case EAST: return NORTH;
            case SOUTH: return EAST;
            case WEST: return SOUTH;
            default:
                throw new IllegalStateException("Unable to get CCW facing of " + this);
        }
    }

    public int getFrontOffsetX()
    {
        return this.axis == Axis.X ? this.axisDirection.getOffset() : 0;
    }

    public int getFrontOffsetY()
    {
        return this.axis == Axis.Y ? this.axisDirection.getOffset() : 0;
    }

    public int getFrontOffsetZ()
    {
        return this.axis == Axis.Z ? this.axisDirection.getOffset() : 0;
    }

    public Axis getAxis()
    {
        return this.axis;
    }

    @Nullable public static Direction byName(String name)
    {
        return name == null ? null : NAME_LOOKUP.get(name.toLowerCase());
    }

    public static Direction getFront(int index)
    {
        return VALUES[Math.abs(index % VALUES.length)];
    }

    public static Direction getHorizontal(int index)
    {
        return HORIZONTALS[Math.abs(index % HORIZONTALS.length)];
    }

    public static Direction fromAngle(double angle)
    {
        return getHorizontal((int) Math.floor(angle / 90.0D + 0.5D) & 3);
    }

    public float getHorizontalAngle()
    {
        return (float) ((this.horizontalIndex & 3) * 90);
    }

    public static Direction random(Random rand)
    {
        return values()[rand.nextInt(values().length)];
    }

    public static Direction getFacingFromVector(float x, float y, float z)
    {
        Direction facing = NORTH;
        float f = Float.MIN_VALUE;
        for(Direction ff : values())
        {
            float f1 = x * (float) ff.directionVec.getX() + y * (float) ff.directionVec.getY() + z * (float) ff.directionVec.getZ();
            if(f1 > f){ f = f1; facing = ff; }
        }
        return facing;
    }

    @Override public String toString()
    {
        return this.name;
    }

    public static Direction getFacingFromAxis(AxisDirection axisDir, Axis axis)
    {
        for(Direction dir : values())
        {
            if(dir.getAxisDirection() == axisDir && dir.getAxis() == axis)
            {
                return dir;
            }
        }
        throw new IllegalArgumentException("No such direction: " + axisDir + " " + axis);
    }

    public Vec3i getDirectionVec()
    {
        return this.directionVec;
    }

    public Direction getClockWise(Direction.Axis axis)
    {
        switch(axis) {
            case X: return this != WEST && this != EAST ? this.getClockWiseX() : this;
            case Z: return this != NORTH && this != SOUTH ? this.getClockWiseZ() : this;
            case Y: return this != UP && this != DOWN ? this.getClockWise() : this;
            default: throw new IncompatibleClassChangeError();
        }
    }

    public Direction getCounterClockWise(Direction.Axis axis)
    {
        switch(axis) {
            case X: return this != WEST && this != EAST ? this.getCounterClockWiseX() : this;
            case Z: return this != NORTH && this != SOUTH ? this.getCounterClockWiseZ() : this;
            case Y: return this != UP && this != DOWN ? this.getCounterClockWise() : this;
            default: throw new IncompatibleClassChangeError();
        }
    }

    public Direction getClockWise()
    {
        switch(this) {
            case NORTH: return EAST;
            case SOUTH: return WEST;
            case WEST: return NORTH;
            case EAST: return SOUTH;
            default: throw new IllegalStateException("Unable to get Y-rotated facing of " + this);
        }
    }

    public Direction getCounterClockWise()
    {
        switch(this) {
            case NORTH: return WEST;
            case SOUTH: return EAST;
            case WEST: return SOUTH;
            case EAST: return NORTH;
            default: throw new IllegalStateException("Unable to get CCW facing of " + this);
        }
    }

    private Direction getClockWiseX()
    {
        switch(this) {
            case DOWN: return SOUTH;
            case UP: return NORTH;
            case NORTH: return DOWN;
            case SOUTH: return UP;
            default: throw new IllegalStateException("Unable to get X-rotated facing of " + this);
        }
    }

    private Direction getCounterClockWiseX()
    {
        switch(this) {
            case DOWN: return NORTH;
            case UP: return SOUTH;
            case NORTH: return UP;
            case SOUTH: return DOWN;
            default: throw new IllegalStateException("Unable to get X-rotated facing of " + this);
        }
    }

    private Direction getClockWiseZ()
    {
        switch(this) {
            case DOWN: return WEST;
            case UP: return EAST;
            case WEST: return UP;
            case EAST: return DOWN;
            default: throw new IllegalStateException("Unable to get Z-rotated facing of " + this);
        }
    }

    private Direction getCounterClockWiseZ()
    {
        switch(this) {
            case DOWN: return EAST;
            case UP: return WEST;
            case WEST: return DOWN;
            case EAST: return UP;
            default: throw new IllegalStateException("Unable to get Z-rotated facing of " + this);
        }
    }

    static {
        for(Direction dir : values())
        {
            VALUES[dir.index] = dir;
            if(dir.getAxis().isHorizontal())
                HORIZONTALS[dir.horizontalIndex] = dir;
            NAME_LOOKUP.put(dir.name.toLowerCase(), dir);
        }
    }

    public static enum Axis implements IStringSerializable {

        X("x", Plane.HORIZONTAL),
        Y("y", Plane.VERTICAL),
        Z("z", Plane.HORIZONTAL);

        private static final Map<String, Axis> NAME_LOOKUP = new HashMap<>();
        private final String name;
        private final Plane plane;

        private Axis(String name, Plane plane)
        {
            this.name = name;
            this.plane = plane;
        }

        @Nullable public static Axis byName(String name)
        {
            return name == null ? null : NAME_LOOKUP.get(name.toLowerCase());
        }

        public boolean isVertical()
        {
            return this.plane == Plane.VERTICAL;
        }

        public boolean isHorizontal()
        {
            return this.plane == Plane.HORIZONTAL;
        }

        @Override public String toString()
        {
            return this.name;
        }

        public boolean apply(@Nullable Direction to)
        {
            return to != null && to.getAxis() == this;
        }

        public boolean test(Direction dir)
        {
            return true;
        }

        public Plane getPlane()
        {
            return this.plane;
        }

        static {
            for(Axis axis : values())
            {
                NAME_LOOKUP.put(axis.name.toLowerCase(), axis);
            }
        }

    }

    public static enum AxisDirection {

        POSITIVE(1, "Towards positive"),
        NEGATIVE(-1, "Towards negative");

        private final int offset;
        private final String description;

        private AxisDirection(int offset, String description)
        {
            this.offset = offset;
            this.description = description;
        }

        public int getOffset()
        {
            return this.offset;
        }

        @Override public String toString()
        {
            return this.description;
        }

    }

    public static enum Plane {

        HORIZONTAL, VERTICAL;

        public Direction[] facings()
        {
            switch(this)
            {
                case HORIZONTAL:
                    return new Direction[]{ Direction.NORTH, Direction.EAST, Direction.SOUTH, Direction.WEST };
                case VERTICAL:
                    return new Direction[]{ Direction.UP, Direction.DOWN };
                default:
                    throw new Error("Someone\'s been tampering with the universe!");
            }
        }

        public Direction random(Random rand)
        {
            Direction[] dirs = this.facings();
            return dirs[rand.nextInt(dirs.length)];
        }

        public boolean apply(@Nullable Direction dir)
        {
            return dir != null && dir.getAxis().getPlane() == this;
        }

        public boolean test(Direction dir)
        {
            return true;
        }

        public Iterator<Direction> iterator()
        {
            return Arrays.asList(this.facings()).iterator();
        }

    }

}
