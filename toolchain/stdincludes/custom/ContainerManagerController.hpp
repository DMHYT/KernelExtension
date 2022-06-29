#include <stl/string>
#include <stl.h>

#include <ItemInstance.hpp>

#ifndef KEX_CONTAINERMANAGERCONTROLLER_HPP
#define KEX_CONTAINERMANAGERCONTROLLER_HPP


class SlotData {
    public:
    char filler[16];
    SlotData(const stl::string&, int);
};

class ItemTransferAmount {
    public:
    char filler[12];
    ItemTransferAmount(int);
};

class ContainerManagerController {
    public:
    ItemInstance* _getItem(const SlotData&, bool) const;
};


#endif //KEX_CONTAINERMANAGERCONTROLLER_HPP