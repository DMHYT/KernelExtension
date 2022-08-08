package vsdum.kex.util.mcmath;

public class Vec3i implements Comparable<Vec3i> {
    
    public static final Vec3i NULL_VECTOR = new Vec3i(0, 0, 0);

    public final int x;
    public final int y;
    public final int z;
    public final Vec3d vec;
    public final int side;

    public Vec3i(int x, int y, int z, int side, Vec3d vec)
    {
        this.x = x;
        this.y = y;
        this.z = z;
        this.side = side;
        this.vec = vec;
    }

    public Vec3i(int x, int y, int z, int side, double dx, double dy, double dz)
    {
        this(x, y, z, 0, new Vec3d(dx,dy,dz));
    }

    public Vec3i(int x, int y, int z)
    {
        this(x, y, z, 0, new Vec3d(0,0,0));
    }

    public Vec3i(double x, double y, double z)
    {
        this((int) Math.floor(x), (int) Math.floor(y), (int) Math.floor(z));
    }

    @Override public boolean equals(Object obj)
    {
        if(this == obj) return true;
        else if(!(obj instanceof Vec3i)) return false;
        else {
            Vec3i vec = (Vec3i) obj;
            return this.getX() == vec.getX() && this.getY() == vec.getY() && this.getZ() == vec.getZ();
        }
    }

    @Override public int hashCode()
    {
        return (this.getY() + this.getZ() * 31) * 31 + this.getX();
    }

    @Override public int compareTo(Vec3i vec)
    {
        return this.getY() == vec.getY() ? (this.getZ() == vec.getZ() ? this.getX() - vec.getX() : this.getZ() - vec.getZ()) : this.getY() - vec.getY();
    }

    public int getX()
    {
        return this.x;
    }

    public int getY()
    {
        return this.y;
    }

    public int getZ()
    {
        return this.z;
    }

    public Vec3i crossProduct(Vec3i vec)
    {
        return new Vec3i(this.getY() * vec.getZ() - this.getZ() * vec.getY(), this.getZ() * vec.getX() - this.getX() * vec.getZ(), this.getX() * vec.getY() - this.getY() * vec.getX());
    }

    public double getDistance(int x, int y, int z)
    {
        return Math.sqrt(this.distanceSq(x, y, z));
    }

    public double distanceSq(double toX, double toY, double toZ)
    {
        double dx = (double) (this.getX() - x);
        double dy = (double) (this.getY() - y);
        double dz = (double) (this.getZ() - z);
        return dx * dx + dy * dy + dz * dz;
    }

    public double distanceSqToCenter(double x, double y, double z)
    {
        double dx = (double) this.getX() + 0.5D - x;
        double dy = (double) this.getY() + 0.5D - y;
        double dz = (double) this.getZ() + 0.5D - z;
        return dx * dx + dy * dy + dz * dz;
    }

    public double distanceSq(Vec3i to)
    {
        return this.distanceSq((double) to.getX(), (double) to.getY(), (double) to.getZ());
    }

    @Override public String toString()
    {
        return "(" + this.getX() + ", " + this.getY() + ", " + this.getZ() + ")";
    }

}
