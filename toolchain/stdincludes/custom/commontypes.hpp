#include <stl/memory>
#include <stl/string>
#include <stl/utility>
#include <stl/vector>
#include <stl.h>

#include <static_symbol.h>

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
    AABB(const Vec3&, const Vec3&);
};

#endif //KEX_AABB_HPP


#ifndef KEX_HASHEDSTRING_HPP
#define KEX_HASHEDSTRING_HPP


class HashedString {
    public:
    unsigned long long hash; // 8
    stl::string str; // 20
    int something; // 24
    HashedString(const stl::string&);
    HashedString(const char*);
    HashedString(unsigned long long, const char*);
    const char* c_str() const;
    void clear();
    bool empty() const;
    unsigned long long getHash() const;
    const stl::string& getString() const;
    bool isEmpty() const;
    bool operator!=(const HashedString&) const;
    bool operator<(const HashedString&) const;
    HashedString& operator=(const HashedString&);
    bool operator==(const HashedString&) const;
    static unsigned long long computeHash(const stl::string&);
    static unsigned long long computeHash(const char*);
    static HashedString defaultErrorValue;
    static const HashedString& getEmptyString();
};
struct HashedStringHasher { size_t operator()(const HashedString& h) const { return static_cast<size_t>(h.getHash()); } };


#endif //KEX_HASHEDSTRING_HPP


#ifndef KEX_INVERTABLEFILTER_HPP
#define KEX_INVERTABLEFILTER_HPP


template<typename T>
struct InvertableFilter {
    T value;
    bool inverted;
};


#endif //KEX_INVERTABLEFILTER_HPP


#ifndef KEX_COMMANDSELECTORRESULTS_HPP
#define KEX_COMMANDSELECTORRESULTS_HPP


template<typename T>
class CommandSelectorResults {
    public:
    stl::shared_ptr<stl::vector<T*>> data;
    unsigned int size() const;
};


#endif //KEX_COMMANDSELECTORRESULTS_HPP


#ifndef KEX_AUTOMATICID_HPP
#define KEX_AUTOMATICID_HPP


template<typename A, typename T>
class AutomaticID {
    public:
    T id;
    AutomaticID(): id(0) {}
    AutomaticID(T x): id(x) {}
    inline operator T() const { return id; }
};


#endif //KEX_AUTOMATICID_HPP


#ifndef KEX_BOUNDS_HPP
#define KEX_BOUNDS_HPP


class Bounds {
    public:
    enum Option {};
    int filler[12]; // 48
    inline Bounds(const Bounds& other) {
        STATIC_SYMBOL(constructCopyC2, "_ZN6BoundsC2ERKS_", (Bounds*, const Bounds&), void);
        constructCopyC2(this, other);
    }
    bool contains(const Bounds&) const;
    bool contains(const BlockPos&) const;
    bool contains2D(const BlockPos&) const;
    bool operator==(const Bounds&) const;
    bool isValid() const;
};


#endif //KEX_BOUNDS_HPP


#ifndef KEX_CHUNKPOS_HPP
#define KEX_CHUNKPOS_HPP


class ChunkPos {
    public:
    int x, z;
    ChunkPos(int xIn, int zIn): x(xIn), z(zIn) {}
    ChunkPos(const BlockPos&);
};


#endif //KEX_CHUNKPOS_HPP


#ifndef KEX_CHUNKBLOCKPOS_HPP
#define KEX_CHUNKBLOCKPOS_HPP


class ChunkBlockPos {
    public:
    char filler[4];
    ChunkBlockPos(const BlockPos&, short s = 0);
};


#endif //KEX_CHUNKBLOCKPOS_HPP


long long getTimeMilliseconds();