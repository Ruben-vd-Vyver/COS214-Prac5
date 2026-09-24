#pragma once

#include "AccessZone.h"
#include <memory>
#include <vector>
class ZoneGroup : public AccessZone {
    std::vector<std::unique_ptr<AccessZone>> children;
public:
    explicit ZoneGroup(const std::string& name);
    ~ZoneGroup() override;
    void add(AccessZone* child); // Takes ownership.
    void lock() override;
    void unlock() override;
    void restrict() override;
    AccessLevel level() override;
};
