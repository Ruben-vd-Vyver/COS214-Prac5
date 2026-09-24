#pragma once

#include "Command.h"
class AlertService;
enum class Severity;
class IssueAlertCommand : public Command {
    AlertService& receiver;
    std::string audience;
    std::string message;
    Severity severity;
public:
    IssueAlertCommand(AlertService& receiver, const std::string& audience,const std::string& message, Severity severity);
    void execute() override;
    void undo() override;
    std::string describe() override;
};
