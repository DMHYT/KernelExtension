#include <stl/string>
#include <stl.h>

#include <commontypes.hpp>
#include <enums.hpp>

#ifndef KEX_ACTORDEFINITIONIDENTIFIER_HPP
#define KEX_ACTORDEFINITIONIDENTIFIER_HPP


class ActorDefinitionIdentifier {
    public:
    stl::string namesp; // 12
    stl::string identifier; // 24
    stl::string event; // 36
    stl::string fullName; // 48
    HashedString canonicalHash; // 72
    ActorDefinitionIdentifier(const stl::string&);
    ActorDefinitionIdentifier(const char*);
    ActorDefinitionIdentifier(stl::string, stl::string, stl::string);
    ActorDefinitionIdentifier(ActorType);
    ActorType _getLegacyActorType() const;
    void clear();
    const HashedString& getCanonicalHash() const;
    const stl::string& getCanonicalName() const;
    const stl::string& getFullName() const;
    const stl::string& getIdentifier() const;
    const stl::string& getInitEvent() const;
    const stl::string& getNamespace() const;
    void initialize(const stl::string&, const stl::string&, const stl::string&);
    void initialize(const stl::string&);
    bool isEmpty() const;
    bool isVanilla() const;
    ActorDefinitionIdentifier& operator=(const ActorDefinitionIdentifier&);
    bool operator==(const ActorDefinitionIdentifier&) const;
    void setIdentifier(const stl::string&);
    void setInitEvent(const stl::string&);
};


#endif //KEX_ACTORDEFINITIONIDENTIFIER_HPP