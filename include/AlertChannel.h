#pragma once

#include <string>
enum class Severity;
class AlertChannel {
public:
    virtual ~AlertChannel() = default;
    virtual void send(const std::string& audience, const std::string& message,Severity severity) = 0;
};
