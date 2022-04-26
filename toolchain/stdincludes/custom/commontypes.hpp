#ifndef KEX_BLOCKPOS_HPP
#define KEX_BLOCKPOS_HPP

class BlockPos {
    public:
    int x, y, z;
    BlockPos(float, float, float);
    BlockPos(double, double, double);
    BlockPos(int, int, int);
};

#endif //KEX_BLOCKPOS_HPP

#ifndef KEX_VEC2_HPP
#define KEX_VEC2_HPP

class Vec2 {
    public:
    float x, y;
    Vec2(float, float);
};

#endif //KEX_VEC2_HPP


#ifndef KEX_VEC3_HPP
#define KEX_VEC3_HPP

class Vec3 {
    public:
    float x, y, z;
    Vec3(float, float, float);
};

#endif //KEX_VEC3_HPP


#ifndef KEX_AABB_HPP
#define KEX_AABB_HPP

class AABB {
    public:
    float minX, minY, minZ, maxX, maxY, maxZ;
    AABB(float, float, float, float, float, float);
    AABB(Vec3 const&, Vec3 const&);
};

#endif //KEX_AABB_HPP


#include <stl/string>

#ifndef KEX_HASHEDSTRING_HPP
#define KEX_HASHEDSTRING_HPP

class HashedString {
    public:
    char filler[20];
    HashedString(const char*);
    std::__ndk1::string const& getString() const;
    bool operator==(HashedString const&) const;
};

#endif //KEX_HASHEDSTRING_HPP