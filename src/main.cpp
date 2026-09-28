#include "IncidentRegistry.h"
#include "ResponseCenter.h"
#include "AccessControlCentre.h"
#include "AlertService.h"
#include "ConsoleAlertChannel.h"
#include "PagerAlertAdapter.h"
#include "EmergencyResponseFacade.h"
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "FacilitiesTeam.h"
#include "OperatorConsole.h"
#include "DispatchUnitCommand.h"
#include "IssueAlertCommand.h"
#include "SecureAreaCommand.h"
#include "EvacuateCommand.h"
#include "Incident.h"
#include "IncidentState.h"
#include "Severity.h"
#include "AccessLevel.h"
#include "UnitKind.h"

#include <iostream>
#include <memory>

int main() {
    // --- Core subsystems ---------------------------------------------
    IncidentRegistry registry;
    ResponseCenter responseCenter;                    // Mediator
    AccessControlCentre accessControl(&responseCenter); // Colleague + Composite root

    AlertService alertService;                          // uses Adapter + normal channel
    alertService.addChannel(std::unique_ptr<ConsoleAlertChannel>(new ConsoleAlertChannel()));
    alertService.addChannel(std::unique_ptr<PagerAlertAdapter>(new PagerAlertAdapter())); // Adapter

    SecurityTeam securityTeam(&responseCenter);
    MedicalTeam medicalTeam(&responseCenter);
    FacilitiesTeam facilitiesTeam(&responseCenter);

    responseCenter.addComponent(&securityTeam);
    responseCenter.addComponent(&medicalTeam);
    responseCenter.addComponent(&facilitiesTeam);
    responseCenter.addComponent(&accessControl);

    EmergencyResponseFacade facade(registry, responseCenter, accessControl, alertService);
    OperatorConsole console; // Invoker

    // ===================================================================
    // Scenario 1: Facade-driven building emergency (Facade, Mediator,
    // Composite, State, Adapter all appear in this single flow).
    // ===================================================================
    std::cout << "==================== SCENARIO 1 ====================" << std::endl;
    Incident& fire = facade.handleBuildingEmergency("Fire", "ScienceBuilding", Severity::High);
    std::cout << "Incident #" << fire.getId() << " status: " << fire.getState()->name() << std::endl;

    facade.standDown(fire.getId());
    std::cout << "Incident #" << fire.getId() << " status: " << fire.getState()->name() << std::endl;

    // ===================================================================
    // Scenario 2: Operator-driven response using Commands (Command,
    // Mediator, Adapter, Composite, State all appear here too).
    // ===================================================================
    std::cout << "\n==================== SCENARIO 2 ====================" << std::endl;
    Incident& intrusion = registry.registerIncident("Intrusion", "Library-ArchiveRoom", Severity::Critical);

    console.submit(std::unique_ptr<DispatchUnitCommand>(
        new DispatchUnitCommand(responseCenter, UnitKind::Security, intrusion)));

    console.submit(std::unique_ptr<SecureAreaCommand>(
        new SecureAreaCommand(accessControl, "Library-ArchiveRoom", AccessLevel::Locked)));

    console.submit(std::unique_ptr<IssueAlertCommand>(
        new IssueAlertCommand(alertService, "Library-ArchiveRoom",
                               "Intrusion detected, area locked down.", Severity::Critical)));

    std::cout << "Incident #" << intrusion.getId() << " status: " << intrusion.getState()->name()
               << std::endl;

    // Undo the last command to show Command's reversible-request behaviour.
    console.undoLast();

    // A full evacuation, combining two receivers in one command.
    console.submit(std::unique_ptr<EvacuateCommand>(
        new EvacuateCommand(accessControl, alertService, "Library")));

    // Demonstrate a failure / invalid-operation case handled sensibly.
    intrusion.contain();
    intrusion.resolve();
    intrusion.dispatch(); // invalid: already resolved - handled, not silently ignored.

    try {
        registry.find(999); // invalid: unknown incident id.
    } catch (const std::out_of_range& ex) {
        std::cout << "[main] Handled expected error: " << ex.what() << std::endl;
    }

    return 0;
}
