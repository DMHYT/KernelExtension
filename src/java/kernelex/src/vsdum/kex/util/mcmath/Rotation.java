package vsdum.kex.util.mcmath;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public enum Rotation {

    NONE,
    CLOCKWISE_90,
    CLOCKWISE_180,
    COUNTERCLOCKWISE_90;

    public Rotation getRotated(Rotation rot)
    {
        switch(rot) {
            case CLOCKWISE_180:
                switch(this) {
                    case NONE: return CLOCKWISE_180;
                    case CLOCKWISE_90: return COUNTERCLOCKWISE_90;
                    case CLOCKWISE_180: return NONE;
                    case COUNTERCLOCKWISE_90: return CLOCKWISE_90;
                }
            case COUNTERCLOCKWISE_90:
                switch(this) {
                    case NONE: return COUNTERCLOCKWISE_90;
                    case CLOCKWISE_90: return NONE;
                    case CLOCKWISE_180: return CLOCKWISE_90;
                    case COUNTERCLOCKWISE_90: return CLOCKWISE_180;
                }
            case CLOCKWISE_90:
                switch(this) {
                    case NONE: return CLOCKWISE_90;
                    case CLOCKWISE_90: return CLOCKWISE_180;
                    case CLOCKWISE_180: return COUNTERCLOCKWISE_90;
                    case COUNTERCLOCKWISE_90: return NONE;
                }
            default: return this;
        }
    }

    public Direction rotate(Direction dir)
    {
        if(dir.getAxis() == Direction.Axis.Y) return dir;
        else switch(this) {
            case CLOCKWISE_90: return dir.getClockWise();
            case CLOCKWISE_180: return dir.getOpposite();
            case COUNTERCLOCKWISE_90: return dir.getCounterClockWise();
            default: return dir;
        }
    }
    
    // todo: understand the params
    public int rotate(int i, int j)
    {
        switch(this) {
            case CLOCKWISE_90: return (i + j / 4) % j;
            case CLOCKWISE_180: return (i + j / 2) % j;
            case COUNTERCLOCKWISE_90: return (i + j * 3 / 4) % j;
            default: return i;
        }
    }

    public static Rotation getRandom(Random rand)
    {
        return values()[rand.nextInt(4)];
    }

    public static List<Rotation> getShuffled(Random rand)
    {
        List<Rotation> result = Arrays.asList(values());
        Collections.shuffle(result, rand);
        return result;
    }

}
