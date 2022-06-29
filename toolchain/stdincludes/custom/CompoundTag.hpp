#include <stl/memory>
#include <stl.h>

#ifndef KEX_COMPOUNDTAG_HPP
#define KEX_COMPOUNDTAG_HPP


class CompoundTag {
    public:
    stl::unique_ptr<CompoundTag> clone() const;
};


#endif //KEX_COMPOUNDTAG_HPP