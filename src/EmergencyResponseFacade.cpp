#include "EmergencyResponseFacade.h"
#include "IncidentRegistry.h"
#include "ResponseCenter.h"
#include "AccessControlCentre.h"
#include "AlertService.h"
#include "Incident.h"
#include "Severity.h"
#include "AccessLevel.h"
#include "UnitKind.h"
#include <iostream>

EmergencyResponseFacade::EmergencyResponseFacade(IncidentRegistry& registry,
                                                   ResponseCenter& responseCenter,
                                                   AccessControlCentre& accessControl,
                                                   AlertService& alertService)
    : registry(registry), responseCenter(responseCenter),
      accessControl(accessControl), alertService(alertService) {}

EmergencyResponseFacade::~EmergencyResponseFacade() = default;

// A single, realistic entry point that hides the several subsystem calls a
// client would otherwise have to sequence correctly by hand: registering
// the incident, locking the area, dispatching the right units and alerting
// people, all in one controlled workflow.
Incident& EmergencyResponseFacade::handleBuildingEmergency(const std::string& type,
                                                             const std::string& building,
                                                             Severity severity) {
    std::cout << "\nEmergencyResponseFacade - Coordinating response for '" << type
               << "' at " << building << " - " << std::endl;

    Incident& incident = registry.registerIncident(type, building, severity);

    accessControl.secureArea(building, AccessLevel::Restricted);

    responseCenter.dispatchUnit(UnitKind::Security, incident);
    if (severity == Severity::High || severity == Severity::Critical) {
        responseCenter.dispatchUnit(UnitKind::Medical, incident);
    }
    responseCenter.dispatchUnit(UnitKind::Facilities, incident);

    // Keep the incident's State in step with the fact that units have now
    // actually been dispatched (bug found via GDB: dispatchUnit() moves the
    // response units but does not itself drive the Incident's State).
    incident.dispatch();

    alertService.broadcast(building, type + " reported at " + building + ". Follow staff instructions.",
                            severity);

    std::cout << "EmergencyResponseFacade - Coordination complete for incident #"
               << incident.getId() << " - \n" << std::endl;
    return incident;
}

void EmergencyResponseFacade::standDown(int incidentId) {
    Incident& incident = registry.find(incidentId);

    std::cout << "\nEmergencyResponseFacade -> Standing down incident #" << incidentId << std::endl;

    incident.contain();
    incident.resolve();
    accessControl.restoreArea(incident.getLocation());
    alertService.broadcast(incident.getLocation(), "Incident resolved. Normal operations resuming.",
                            Severity::Low);
}
