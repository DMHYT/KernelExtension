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
    CommandOutputParameter(std::__ndk1::vector<Actor const*> const&);
    CommandOutputParameter(Actor const&);
    CommandOutputParameter(bool);
    CommandOutputParameter(float);
    CommandOutputParameter(int);
    CommandOutputParameter(std::__ndk1::vector<std::__ndk1::string> const&);
    CommandOutputParameter(Actor const*);
    CommandOutputParameter(Vec3);
    CommandOutputParameter(const char*);
    CommandOutputParameter(std::__ndk1::string const&, int);
    CommandOutputParameter(std::__ndk1::string const&);
    CommandOutputParameter(std::__ndk1::vector<Player const*> const&);
    CommandOutputParameter(BlockPos);
    std::__ndk1::string getText() const;
    int count() const;
};


class CommandOutput {
    public:
    bool empty() const;
    bool wantsData() const;
    CommandOutputType getType() const;
    void addToResultList(std::__ndk1::string const&, std::__ndk1::string const&);
    void addToResultList(std::__ndk1::string const&, Actor const&);
    void success(std::__ndk1::string const&, std::__ndk1::vector<CommandOutputParameter> const&);
    void success();
    void error(std::__ndk1::string const&, std::__ndk1::vector<CommandOutputParameter> const&);
};


#endif //KEX_COMMANDOUTPUT_HPP