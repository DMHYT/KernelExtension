#include <commontypes.hpp>

#ifndef KEX_COMMANDPOSITION_HPP
#define KEX_COMMANDPOSITION_HPP


class CommandOrigin;

class CommandPosition {
    public:
    float offsetX, offsetY, offsetZ; // 12
    bool relativeX, relativeY, relativeZ, local; // 16
    CommandPosition(Vec3 const&);
    CommandPosition();
    BlockPos getBlockPos(CommandOrigin const&, Vec3 const&) const;
    BlockPos getBlockPos(Vec3 const&, Vec3 const&) const;
    Vec3 getPosition(Vec3 const&, Vec3 const&) const;
    Vec3 getPosition(CommandOrigin const&, Vec3 const&) const;
};

class CommandPositionFloat : public CommandPosition {};


#endif //KEX_COMMANDPOSITION_HPP