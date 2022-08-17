package vsdum.kex.util.mcmath;

public class MathHelper {
    
    private static final int[] MULTIPLY_DE_BRUIJN_BIT_POSITION = new int[] {0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9};
    
    public static int roundUpToPowerOfTwo(int value)
    {
        int i = value - 1;
        i = i | i >> 1;
        i = i | i >> 2;
        i = i | i >> 4;
        i = i | i >> 8;
        i = i | i >> 16;
        return i + 1;
    }

    private static boolean isPowerOfTwo(int value)
    {
        return value != 0 && (value & value - 1) == 0;
    }
    
    public static int calculateLogBaseTwoDeBruijn(int value)
    {
        value = isPowerOfTwo(value) ? value : roundUpToPowerOfTwo(value);
        return MULTIPLY_DE_BRUIJN_BIT_POSITION[ (int) ((long) value * 125613361L >> 27) & 31];
    }

    public static int calculateLogBaseTwo(int value)
    {
        return calculateLogBaseTwoDeBruijn(value) - (isPowerOfTwo(value) ? 0 : 1);
    }

    public static float intFloorDiv(float f)
    {
        float f1 = 0.5F * f;
        int i = Float.floatToIntBits(f);
        i = 1597463007 - (i >> 1);
        f = Float.intBitsToFloat(i);
        f *= 1.5 - f1 * f * f;
        return f;
    }

    public static int clamp(int num, int min, int max)
    {
        return num < min ? min : num > max ? max : num;
    }

    public static long clamp(long num, long min, long max)
    {
        return num < min ? min : num > max ? max : num;
    }

    public static float clamp(float num, float min, float max)
    {
        return num < min ? min : num > max ? max : num;
    }
    
    public static double clamp(double num, double min, double max)
    {
        return num < min ? min : num > max ? max : num;
    }

}
