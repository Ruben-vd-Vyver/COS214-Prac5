#include "EvacuateCommand.h"
#include "AccessControlCentre.h"
#include "AlertService.h"
#include "AccessLevel.h"
#include "Severity.h"

EvacuateCommand::EvacuateCommand(AccessControlCentre& accessReceiver, AlertService& alertReceiver,
                                  const std::string& zoneName)
    : accessReceiver(accessReceiver), alertReceiver(alertReceiver), zoneName(zoneName) {}

void EvacuateCommand::execute() {
    accessReceiver.secureArea(zoneName, AccessLevel::Restricted);
    alertReceiver.broadcast(zoneName, "Evacuate immediately: " + zoneName, Severity::Critical);
}

void EvacuateCommand::undo() {
    accessReceiver.restoreArea(zoneName);
    alertReceiver.broadcast(zoneName, "Evacuation order for " + zoneName + " has been lifted.",
                             Severity::Medium);
}

std::string EvacuateCommand::describe() {
    return "Evacuate zone " + zoneName;
}
