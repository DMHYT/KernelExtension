#include <stl/string>
#include <stl/vector>
#include <stl.h>

#ifndef KEX_LOCALIZATION_HPP
#define KEX_LOCALIZATION_HPP


class ResourcePackManager;

class Localization {
    public:
    char filler[28];
    Localization(const stl::string&, Localization*);
    Localization(const stl::string&);
    bool isFormattedString(const stl::string&);
    void appendTranslations(Localization const&);
    void appendTranslations(const stl::string&, const stl::vector<stl::string>&, const stl::vector<stl::string>&, const stl::string&);
    stl::string getCommaSeperator() const;
    stl::string getLanguageCode() const;
    stl::string getRegionCode() const;
    stl::string getFullLanguageCode() const;
    bool getStringIdExists(const stl::string&) const;
    void get(const stl::string&, stl::string&, const stl::vector<stl::string>&) const;
    stl::string _get(const stl::string&, const stl::vector<stl::string>&) const;
    void loadFromResourcePackManager(ResourcePackManager&, const stl::vector<stl::string>&);
    stl::string _replaceTokens(stl::string&, const stl::vector<stl::string>&) const;
    static stl::string getLanguageCode(const stl::string&);
    static stl::string getRegionCode(const stl::string&);
    static stl::string _getLangFilePath(const stl::string&);
    static bool _isCommaSeperatedLanguage(const stl::string&);
};


#endif //KEX_LOCALIZATION_HPP