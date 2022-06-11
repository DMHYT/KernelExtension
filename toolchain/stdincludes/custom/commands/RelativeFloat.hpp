#ifndef KEX_RELATIVEFLOAT_HPP
#define KEX_RELATIVEFLOAT_HPP


class RelativeFloat {
    public:
    float value; // 4
    bool isRelative; // 5 + 3
    RelativeFloat(float value): value(value), isRelative(true) {}
    RelativeFloat(float, bool);
    RelativeFloat();
    inline float getFloat(float center) const {
        return isRelative ? center + value : value;
    }
};


#endif //KEX_RELATIVEFLOAT_HPP