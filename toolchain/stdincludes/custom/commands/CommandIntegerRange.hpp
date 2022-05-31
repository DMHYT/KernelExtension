#ifndef KEX_COMMANDINTEGERRANGE_HPP
#define KEX_COMMANDINTEGERRANGE_HPP


class CommandIntegerRange {
    public:
    int min, max; // 8
    bool inverted; // 9 + 3
    CommandIntegerRange(int, int, bool);
    CommandIntegerRange();
    bool isWithinRange(int) const;
    int getMinValue() const;
    int getMaxValue() const;
    bool getInverted() const;
};


#endif //KEX_COMMANDINTEGERRANGE_HPP