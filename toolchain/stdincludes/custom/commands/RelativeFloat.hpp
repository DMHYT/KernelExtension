#ifndef KEX_RELATIVEFLOAT_HPP
#define KEX_RELATIVEFLOAT_HPP


class RelativeFloat {
    public:
    float value; // 4
    bool isRelative; // 5 + 3
    RelativeFloat(float _value): value(_value), isRelative(true) {}
    RelativeFloat(float _value, bool _isRelative): value(_value), isRelative(_isRelative) {}
    RelativeFloat(): value(0.0f), isRelative(true) {}
    float getValue(float center) const;
};


#endif //KEX_RELATIVEFLOAT_HPP