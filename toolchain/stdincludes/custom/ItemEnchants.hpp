#include <stl/vector>
#include <stl.h>

#ifndef KEX_ITEMENCHANTS_HPP
#define KEX_ITEMENCHANTS_HPP


#ifndef KEX_ENCHANT_HPP
    class Enchant { public: enum Type: unsigned char {}; };
#endif

struct EnchantmentInstance {
    Enchant::Type type;
    int level;
};

class ItemEnchants {
    public:
    char filler[40];
    bool hasEnchant(Enchant::Type) const;
    stl::vector<EnchantmentInstance> getAllEnchants() const;
};


#endif //KEX_ITEMENCHANTS_HPP