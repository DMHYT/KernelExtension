#include "CommandOutput.hpp"
#include <ItemInstance.hpp>

#ifndef KEX_COMMANDITEM_HPP
#define KEX_COMMANDITEM_HPP


class CommandItem {
    public:
    union {
        struct {
            short version; // 2
            bool something; // 3 + 1
            int itemID; // 8
        };
        unsigned long long ULL; // 8
    };
    CommandItem(int, short, bool);
    CommandItem(unsigned long long);
    CommandItem();
    operator bool() const;
    operator unsigned long long() const;
    short getVersion() const;
    int getId() const;
    ItemInstance* createInstance(int) const;
    ItemInstance* createInstance(int, int, CommandOutput*, bool) const;
};


#endif //KEX_COMMANDITEM_HPP