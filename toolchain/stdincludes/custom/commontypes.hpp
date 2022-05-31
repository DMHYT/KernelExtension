#include <stl/memory>
#include <stl/string>
#include <stl/vector>

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


#ifndef KEX_HASHEDSTRING_HPP
#define KEX_HASHEDSTRING_HPP

class HashedString {
    public:
    unsigned long long hash; // 8
    std::__ndk1::string str; // 20
    int something; // 24
    HashedString(std::__ndk1::string const&);
    HashedString(const char*);
    HashedString(unsigned long long, const char*);
    const char* c_str() const;
    void clear();
    bool empty() const;
    unsigned long long getHash() const;
    std::__ndk1::string const& getString() const;
    bool isEmpty() const;
    bool operator!=(HashedString const&) const;
    bool operator<(HashedString const&) const;
    HashedString& operator=(HashedString const&);
    bool operator==(HashedString const&) const;
    static unsigned long long computeHash(std::__ndk1::string const&);
    static unsigned long long computeHash(const char*);
    static HashedString defaultErrorValue;
    static const HashedString& getEmptyString();
};

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
    std::__ndk1::shared_ptr<std::__ndk1::vector<T*>> data;
    typename std::__ndk1::vector<T*>::const_iterator begin() { return data->begin(); }
    typename std::__ndk1::vector<T*>::const_iterator end() { return data->end(); }
    unsigned int count() const { return data->size(); }
    bool empty() const { return data->empty(); }
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