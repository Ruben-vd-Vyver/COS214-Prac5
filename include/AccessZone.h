#pragma once

#include <string>
enum class AccessLevel;
class AccessZone {
protected:
    std::string name;
public:
    explicit AccessZone(const std::string& name);
    virtual ~AccessZone() = default;
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual void restrict() = 0;
    virtual AccessLevel level() = 0;
    virtual AccessZone* find(const std::string& targetName);
    const std::string& getName();
};
