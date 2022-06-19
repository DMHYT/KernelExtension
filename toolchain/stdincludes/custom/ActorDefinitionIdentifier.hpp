#include <stl/string>

#include <commontypes.hpp>
#include <enums.hpp>

#ifndef KEX_ACTORDEFINITIONIDENTIFIER_HPP
#define KEX_ACTORDEFINITIONIDENTIFIER_HPP


class ActorDefinitionIdentifier {
    public:
    std::__ndk1::string namesp; // 12
    std::__ndk1::string identifier; // 24
    std::__ndk1::string event; // 36
    std::__ndk1::string fullName; // 48
    HashedString canonicalHash; // 72
    ActorDefinitionIdentifier(const std::__ndk1::string&);
    ActorDefinitionIdentifier(const char*);
    ActorDefinitionIdentifier(std::__ndk1::string, std::__ndk1::string, std::__ndk1::string);
    ActorDefinitionIdentifier(ActorType);
    ActorType _getLegacyActorType() const;
    void clear();
    const HashedString& getCanonicalHash() const;
    const std::__ndk1::string& getCanonicalName() const;
    const std::__ndk1::string& getFullName() const;
    const std::__ndk1::string& getIdentifier() const;
    const std::__ndk1::string& getInitEvent() const;
    const std::__ndk1::string& getNamespace() const;
    void initialize(const std::__ndk1::string&, const std::__ndk1::string&, const std::__ndk1::string&);
    void initialize(const std::__ndk1::string&);
    bool isEmpty() const;
    bool isVanilla() const;
    ActorDefinitionIdentifier& operator=(const ActorDefinitionIdentifier&);
    bool operator==(const ActorDefinitionIdentifier&) const;
    void setIdentifier(const std::__ndk1::string&);
    void setInitEvent(const std::__ndk1::string&);
};


#endif //KEX_ACTORDEFINITIONIDENTIFIER_HPP