#include <stl/string>
#include <stl.h>

#include <Localization.hpp>

#ifndef KEX_I18N_HPP
#define KEX_I18N_HPP


class I18n {
    public:
    static stl::string get(const stl::string&);
    static Localization* getCurrentLanguage();
};


#endif //KEX_I18N_HPP