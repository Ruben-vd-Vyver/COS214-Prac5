#include "DispatchUnitCommand.h"
#include "ResponseCenter.h"
#include "Incident.h"
#include "UnitKind.h"
#include <sstream>

namespace {
std::string unitKindName(UnitKind kind) {
    switch (kind) {
        case UnitKind::Security: return "Security";
        case UnitKind::Medical: return "Medical";
        case UnitKind::Facilities: return "Facilities";
    }
    return "Unknown";
}
} // namespace

DispatchUnitCommand::DispatchUnitCommand(ResponseCenter& receiver, UnitKind kind, Incident& incident)
    : receiver(receiver), kind(kind), incident(incident) {}

void DispatchUnitCommand::execute() {
    receiver.dispatchUnit(kind, incident);
    incident.dispatch();
}

void DispatchUnitCommand::undo() {
    incident.cancel();
}

std::string DispatchUnitCommand::describe() {
    std::ostringstream oss;
    oss << "Dispatch " << unitKindName(kind) << " unit to incident #" << incident.getId();
    return oss.str();
}
