#include "IssueAlertCommand.h"
#include "AlertService.h"
#include "Severity.h"

IssueAlertCommand::IssueAlertCommand(AlertService& receiver, const std::string& audience,
                                      const std::string& message, Severity severity)
    : receiver(receiver), audience(audience), message(message), severity(severity) {}

void IssueAlertCommand::execute() {
    receiver.broadcast(audience, message, severity);
}

void IssueAlertCommand::undo() {
    receiver.broadcast(audience, "RETRACTED: " + message, Severity::Low);
}

std::string IssueAlertCommand::describe() {
    return "Issue alert to " + audience + ": " + message;
}
