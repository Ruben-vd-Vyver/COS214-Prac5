#include "AccessZone.h"

AccessZone::AccessZone(const std::string& name) : name(name) {}

const std::string& AccessZone::getName() {
    return name;
}

// Default behaviour -> a zone matches itself or nothing.
// ZoneGroup overrides this and recurses to children
AccessZone* AccessZone::find(const std::string& targetName) {
    if (name == targetName) {
        return this;
    }
    return nullptr;
}
