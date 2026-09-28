#include "ZoneGroup.h"
#include "AccessLevel.h"

ZoneGroup::ZoneGroup(const std::string& name) : AccessZone(name) {}

ZoneGroup::~ZoneGroup() = default;

void ZoneGroup::add(AccessZone* child) {
    children.emplace_back(child);
}

void ZoneGroup::lock() {
    for (auto& child : children) {
        child->lock();
    }
}

void ZoneGroup::unlock() {
    for (auto& child : children) {
        child->unlock();
    }
}

void ZoneGroup::restrict() {
    for (auto& child : children) {
        child->restrict();
    }
}

// A group is reported as Locked if any child is Locked, Restricted if any
// child is Restricted, otherwise Normal.
AccessLevel ZoneGroup::level() {
    AccessLevel worst = AccessLevel::Normal;
    for (auto& child : children) {
        AccessLevel childLevel = child->level();
        if (childLevel == AccessLevel::Locked) {
            return AccessLevel::Locked;
        }
        if (childLevel == AccessLevel::Restricted) {
            worst = AccessLevel::Restricted;
        }
    }
    return worst;
}

AccessZone* ZoneGroup::find(const std::string& targetName) {
    if (getName() == targetName) {
        return this;
    }
    for (auto& child : children) {
        AccessZone* found = child->find(targetName);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}
