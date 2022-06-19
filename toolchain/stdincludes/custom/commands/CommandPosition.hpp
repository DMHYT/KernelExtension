#include <commontypes.hpp>

#ifndef KEX_COMMANDPOSITION_HPP
#define KEX_COMMANDPOSITION_HPP


class CommandOrigin;

class CommandPosition {
    public:
    float offsetX, offsetY, offsetZ; // 12
    bool relativeX, relativeY, relativeZ, local; // 16
    CommandPosition(const Vec3&);
    CommandPosition();
    BlockPos getBlockPos(const CommandOrigin&, const Vec3&) const;
    BlockPos getBlockPos(const Vec3&, const Vec3&) const;
    Vec3 getPosition(const Vec3&, const Vec3&) const;
    Vec3 getPosition(const CommandOrigin&, const Vec3&) const;
};

class CommandPositionFloat : public CommandPosition {};


#endif //KEX_COMMANDPOSITION_HPP