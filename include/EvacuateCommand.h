#pragma once

#include "Command.h"
class AccessControlCentre;
class AlertService;
class EvacuateCommand : public Command {
    AccessControlCentre& accessReceiver;
    AlertService& alertReceiver;
    std::string zoneName;
public:
    EvacuateCommand(AccessControlCentre& accessReceiver, AlertService& alertReceiver,const std::string& zoneName);
    void execute() override;
    void undo() override;
    std::string describe() override;
};
