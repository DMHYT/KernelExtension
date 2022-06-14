#ifndef KEX_COMMANDWILDCARDINT_HPP
#define KEX_COMMANDWILDCARDINT_HPP


class CommandWildcardInt {
    public:
    bool wildcard; // 1 + 3
    int value; // 8
    CommandWildcardInt();
    CommandWildcardInt(int);
    bool isWildcard() const;
    int getValue() const;
};


#endif //KEX_COMMANDWILDCARDINT_HPP