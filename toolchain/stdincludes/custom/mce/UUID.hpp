#include <stl/string>
#include <stl.h>

#ifndef KEX_MCEUUID_HPP
#define KEX_MCEUUID_HPP


namespace mce {
    class UUID {
        public:
        char filler[16];
        unsigned long long getHash() const;
        stl::string asString() const;
        bool isEmpty() const;
        bool operator<(const UUID&) const;
        static UUID fromString(const stl::string&);
        static unsigned long long seedFromString(const stl::string&);
    };
}


#endif //KEX_MCEUUID_HPP