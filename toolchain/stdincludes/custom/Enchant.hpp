#include <stl/vector>
#include <stl/memory>
#include <stl.h>

#ifndef KEX_ENCHANT_HPP
#define KEX_ENCHANT_HPP


class Enchant {
    public:
    enum Type: unsigned char {};
    void** vtable; // 4
    Type type; // 8
    static stl::vector<stl::unique_ptr<Enchant>> mEnchants;
};


#endif //KEX_ENCHANT_HPP