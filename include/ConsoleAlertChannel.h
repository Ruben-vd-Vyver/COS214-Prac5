#pragma once

#include "AlertChannel.h"
class ConsoleAlertChannel : public AlertChannel {
public:
    void send(const std::string& audience, const std::string& message,Severity severity) override;
};
