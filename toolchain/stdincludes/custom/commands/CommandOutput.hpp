#include <stl/string>
#include <stl/vector>

#include <enums.hpp>

#ifndef KEX_COMMANDOUTPUT_HPP
#define KEX_COMMANDOUTPUT_HPP


#ifndef KEX_ACTOR_HPP
    class Actor;
#endif
#ifndef KEX_BLOCKPOS_HPP
    class BlockPos;
#endif
#ifndef KEX_PLAYER_HPP
    class Player;
#endif
#ifndef KEX_VEC3_HPP
    class Vec3;
#endif

class CommandOutputParameter {
    public:
    std::__ndk1::string _text; // 12
    int _count; // 16
    CommandOutputParameter(std::__ndk1::vector<const Actor*> const&);
    CommandOutputParameter(const Actor&);
    CommandOutputParameter(bool);
    CommandOutputParameter(float);
    CommandOutputParameter(int);
    CommandOutputParameter(std::__ndk1::vector<std::__ndk1::string> const&);
    CommandOutputParameter(const Actor*);
    CommandOutputParameter(Vec3);
    CommandOutputParameter(const char*);
    CommandOutputParameter(const std::__ndk1::string&, int);
    CommandOutputParameter(const std::__ndk1::string&);
    CommandOutputParameter(std::__ndk1::vector<const Player*> const&);
    CommandOutputParameter(BlockPos);
    std::__ndk1::string getText() const;
    int count() const;
};


class CommandOutput {
    public:
    bool empty() const;
    bool wantsData() const;
    CommandOutputType getType() const;
    void addToResultList(const std::__ndk1::string&, const std::__ndk1::string&);
    void addToResultList(const std::__ndk1::string&, const Actor&);
    void success(const std::__ndk1::string&, std::__ndk1::vector<CommandOutputParameter> const&);
    void success();
    void error(const std::__ndk1::string&, std::__ndk1::vector<CommandOutputParameter> const&);
};


#endif //KEX_COMMANDOUTPUT_HPP