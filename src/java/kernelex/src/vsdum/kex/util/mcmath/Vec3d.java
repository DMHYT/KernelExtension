package vsdum.kex.util.mcmath;

import android.support.annotation.Nullable;

public class Vec3d {
    
    public static final Vec3d ZERO = new Vec3d(0.0D, 0.0D, 0.0D);
    public final double x;
    public final double y;
    public final double z;

    public Vec3d(double x, double y, double z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vec3d(Vec3i vector)
    {
        this( (double) vector.getX(), (double) vector.getY(), (double) vector.getZ());
    }

    public Vec3d subtractReverse(Vec3d vec)
    {
        return new Vec3d(vec.x - this.x, vec.y - this.y, vec.z - this.z);
    }

    public Vec3d normalize()
    {
        double d0 = (double) Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
        return d0 < 1.0E-4D ? ZERO : new Vec3d(this.x / d0, this.y / d0, this.z / d0);
    }

    public double dotProduct(Vec3d vec)
    {
        return this.x * vec.x + this.y * vec.y + this.z * vec.z;
    }

    public Vec3d crossProduct(Vec3d vec)
    {
        return new Vec3d(this.y * vec.z - this.z * vec.y, this.z * vec.x - this.x * vec.z, this.x * vec.y - this.y * vec.x);
    }

    public Vec3d subtract(Vec3d vec)
    {
        return this.subtract(vec.x, vec.y, vec.z);
    }

    public Vec3d subtract(double x, double y, double z)
    {
        return this.addVector(-x, -y, -z);
    }

    public Vec3d add(Vec3d vec)
    {
        return this.addVector(vec.x, vec.y, vec.z);
    }

    public Vec3d addVector(double x, double y, double z)
    {
        return new Vec3d(this.x + x, this.y + y, this.z + z);
    }

    public double distanceTo(Vec3d vec)
    {
        double d0 = vec.x - this.x;
        double d1 = vec.y - this.y;
        double d2 = vec.z - this.z;
        return (double) Math.sqrt(d0 * d0 + d1 * d1 + d2 * d2);
    }

    public double squareDistanceTo(Vec3d vec)
    {
        double d0 = vec.x - this.x;
        double d1 = vec.y - this.y;
        double d2 = vec.z - this.z;
        return d0 * d0 + d1 * d1 + d2 * d2;
    }

    public double squareDistanceTo(double xIn, double yIn, double zIn)
    {
        double d0 = xIn - this.x;
        double d1 = yIn - this.y;
        double d2 = zIn - this.z;
        return d0 * d0 + d1 * d1 + d2 * d2;
    }

    public Vec3d scale(double val)
    {
        return new Vec3d(this.x * val, this.y * val, this.z * val);
    }

    public double lengthVector()
    {
        return (double) Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
    }

    public double lengthSquared()
    {
        return this.x * this.x + this.y * this.y + this.z * this.z;
    }

    @Nullable public Vec3d getIntermediateWithXValue(Vec3d vec, double x)
    {
        double d0 = vec.x - this.x;
        double d1 = vec.y - this.y;
        double d2 = vec.z - this.z;
        if (d0 * d0 < 1.0000000116860974E-7D) return null;
        else {
            double d3 = (x - this.x) / d0;
            return d3 >= 0.0D && d3 <= 1.0D ? new Vec3d(this.x + d0 * d3, this.y + d1 * d3, this.z + d2 * d3) : null;
        }
    }

    @Nullable public Vec3d getIntermediateWithYValue(Vec3d vec, double y)
    {
        double d0 = vec.x - this.x;
        double d1 = vec.y - this.y;
        double d2 = vec.z - this.z;
        if (d1 * d1 < 1.0000000116860974E-7D) return null;
        else {
            double d3 = (y - this.y) / d1;
            return d3 >= 0.0D && d3 <= 1.0D ? new Vec3d(this.x + d0 * d3, this.y + d1 * d3, this.z + d2 * d3) : null;
        }
    }

    @Nullable public Vec3d getIntermediateWithZValue(Vec3d vec, double z)
    {
        double d0 = vec.x - this.x;
        double d1 = vec.y - this.y;
        double d2 = vec.z - this.z;
        if (d2 * d2 < 1.0000000116860974E-7D) return null;
        else {
            double d3 = (z - this.z) / d2;
            return d3 >= 0.0D && d3 <= 1.0D ? new Vec3d(this.x + d0 * d3, this.y + d1 * d3, this.z + d2 * d3) : null;
        }
    }

    @Override public boolean equals(Object obj)
    {
        if (this == obj) return true;
        else if (!(obj instanceof Vec3d)) return false;
        else {
            Vec3d vec3d = (Vec3d) obj;
            return Double.compare(vec3d.x, this.x) != 0 ? false : (Double.compare(vec3d.y, this.y) != 0 ? false : Double.compare(vec3d.z, this.z) == 0);
        }
    }

    @Override public int hashCode()
    {
        long j = Double.doubleToLongBits(this.x);
        int i = (int) (j ^ j >>> 32);
        j = Double.doubleToLongBits(this.y);
        i = 31 * i + (int) (j ^ j >>> 32);
        j = Double.doubleToLongBits(this.z);
        i = 31 * i + (int) (j ^ j >>> 32);
        return i;
    }

    @Override public String toString()
    {
        return "(" + this.x + ", " + this.y + ", " + this.z + ")";
    }

    public Vec3d rotatePitch(float pitch)
    {
        float f = (float) Math.cos(pitch);
        float f1 = (float) Math.sin(pitch);
        double d0 = this.x;
        double d1 = this.y * (double)f + this.z * (double)f1;
        double d2 = this.z * (double)f - this.y * (double)f1;
        return new Vec3d(d0, d1, d2);
    }

    public Vec3d rotateYaw(float yaw)
    {
        float f = (float) Math.cos(yaw);
        float f1 = (float) Math.sin(yaw);
        double d0 = this.x * (double)f + this.z * (double)f1;
        double d1 = this.y;
        double d2 = this.z * (double)f - this.x * (double)f1;
        return new Vec3d(d0, d1, d2);
    }
    
    public static Vec3d fromPitchYawVector(Vec2f pitchYawVec)
    {
        return fromPitchYaw(pitchYawVec.x, pitchYawVec.y);
    }

    public static Vec3d fromPitchYaw(float pitch, float yaw)
    {
        float f = (float) Math.cos(-yaw * 0.017453292F - (float)Math.PI);
        float f1 = (float) Math.sin(-yaw * 0.017453292F - (float)Math.PI);
        float f2 = (float) -Math.cos(pitch * 0.017453292F);
        float f3 = (float) Math.sin(pitch * 0.017453292F);
        return new Vec3d((double)(f1 * f2), (double)f3, (double)(f * f2));
    }
    
}
