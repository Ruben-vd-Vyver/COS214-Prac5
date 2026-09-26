#include "SecureAreaCommand.h"
#include "AccessControlCentre.h"
#include "AccessLevel.h"

SecureAreaCommand::SecureAreaCommand(AccessControlCentre& receiver, const std::string& zoneName,
                                      AccessLevel level)
    : receiver(receiver), zoneName(zoneName), level(level), previousLevel(AccessLevel::Normal) {}

void SecureAreaCommand::execute() {
    receiver.secureArea(zoneName, level);
}

void SecureAreaCommand::undo() {
    receiver.restoreArea(zoneName);
}

std::string SecureAreaCommand::describe() {
    return "Secure zone " + zoneName;
}
