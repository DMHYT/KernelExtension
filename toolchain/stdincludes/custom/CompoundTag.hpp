#include <stl/memory>
#include <stl.h>

#ifndef KEX_COMPOUNDTAG_HPP
#define KEX_COMPOUNDTAG_HPP


class CompoundTag {
    public:
    char filler[60]; // 60
    stl::unique_ptr<CompoundTag> clone() const;
    CompoundTag();
};


#endif //KEX_COMPOUNDTAG_HPP