#include <stl/string>
#include <stl/vector>
#include <stl.h>

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
    stl::string _text; // 12
    int _count; // 16
    CommandOutputParameter(stl::vector<const Actor*> const&);
    CommandOutputParameter(const Actor&);
    CommandOutputParameter(bool);
    CommandOutputParameter(float);
    CommandOutputParameter(int);
    CommandOutputParameter(stl::vector<stl::string> const&);
    CommandOutputParameter(const Actor*);
    CommandOutputParameter(Vec3);
    CommandOutputParameter(const char*);
    CommandOutputParameter(const stl::string&, int);
    CommandOutputParameter(const stl::string&);
    CommandOutputParameter(stl::vector<const Player*> const&);
    CommandOutputParameter(BlockPos);
    stl::string getText() const;
    int count() const;
};


class CommandOutput {
    public:
    bool empty() const;
    bool wantsData() const;
    CommandOutputType getType() const;
    void addToResultList(const stl::string&, const stl::string&);
    void addToResultList(const stl::string&, const Actor&);
    void success(const stl::string&, stl::vector<CommandOutputParameter> const&);
    void success();
    void error(const stl::string&, stl::vector<CommandOutputParameter> const&);
};


#endif //KEX_COMMANDOUTPUT_HPP