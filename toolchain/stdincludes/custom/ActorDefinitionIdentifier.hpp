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
    ActorDefinitionIdentifier(std::__ndk1::string const&);
    ActorDefinitionIdentifier(const char*);
    ActorDefinitionIdentifier(std::__ndk1::string, std::__ndk1::string, std::__ndk1::string);
    ActorDefinitionIdentifier(ActorType);
    ActorType _getLegacyActorType() const;
    void clear();
    HashedString const& getCanonicalHash() const;
    std::__ndk1::string const& getCanonicalName() const;
    std::__ndk1::string const& getFullName() const;
    std::__ndk1::string const& getIdentifier() const;
    std::__ndk1::string const& getInitEvent() const;
    std::__ndk1::string const& getNamespace() const;
    void initialize(std::__ndk1::string const&, std::__ndk1::string const&, std::__ndk1::string const&);
    void initialize(std::__ndk1::string const&);
    bool isEmpty() const;
    bool isVanilla() const;
    ActorDefinitionIdentifier& operator=(ActorDefinitionIdentifier const&);
    bool operator==(ActorDefinitionIdentifier const&) const;
    void setIdentifier(std::__ndk1::string const&);
    void setInitEvent(std::__ndk1::string const&);
};


#endif //KEX_ACTORDEFINITIONIDENTIFIER_HPP