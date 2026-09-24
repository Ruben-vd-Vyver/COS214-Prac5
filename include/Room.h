#pragma once

#include "AccessZone.h"
class Room : public AccessZone {
    AccessLevel currentLevel;
public:
    explicit Room(const std::string& name);
    void lock() override;
    void unlock() override;
    void restrict() override;
    AccessLevel level() override;
};
