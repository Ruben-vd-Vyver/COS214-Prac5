#pragma once

#include "Command.h"
class AccessControlCentre;
enum class AccessLevel;
class SecureAreaCommand : public Command {
    AccessControlCentre& receiver;
    std::string zoneName;
    AccessLevel level;
    AccessLevel previousLevel;
public:
    SecureAreaCommand(AccessControlCentre& receiver, const std::string& zoneName,AccessLevel level);
    void execute() override;
    void undo() override;
    std::string describe() override;
};
