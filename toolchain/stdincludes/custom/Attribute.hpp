#ifndef KEX_ATTRIBUTE_HPP
#define KEX_ATTRIBUTE_HPP


#ifndef KEX_HASHEDSTRING_HPP
    class HashedString { public: char filler[24]; };
#endif
enum RedefinitionMode: char {};

struct Attribute {
    RedefinitionMode redefMode; // 1
    bool clientSyncable; // 2 + 2
    void* attributeCollection_addAttribute_result; // 8
    HashedString name; // 32
};

class SharedAttributes {
    public:
    static Attribute HEALTH;
    static Attribute FOLLOW_RANGE;
    static Attribute KNOCKBACK_RESISTANCE;
    static Attribute MOVEMENT_SPEED;
    static Attribute UNDERWATER_MOVEMENT_SPEED;
    static Attribute LAVA_MOVEMENT_SPEED;
    static Attribute ATTACK_DAMAGE;
    static Attribute ABSORPTION;
    static Attribute LUCK;
    static Attribute JUMP_STRENGTH;
};


#endif //KEX_ATTRIBUTE_HPP