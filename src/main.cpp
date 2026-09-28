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

    AlertService alertService;
    alertService.addChannel(std::unique_ptr<AlertChannel>(new ConsoleAlertChannel()));
    alertService.addChannel(std::unique_ptr<AlertChannel>(new PagerAlertAdapter())); // Adapter

    SecurityTeam securityTeam(&responseCenter);
    MedicalTeam medicalTeam(&responseCenter);
    FacilitiesTeam facilitiesTeam(&responseCenter);

    responseCenter.addComponent(&securityTeam);
    responseCenter.addComponent(&medicalTeam);
    responseCenter.addComponent(&facilitiesTeam);
    responseCenter.addComponent(&accessControl);

    EmergencyResponseFacade facade(registry, responseCenter, accessControl, alertService); // Facade
    OperatorConsole console;                                                               // Invoker

    // SCENARIO 1: "Laboratory fire in the Science Building" (High severity)
    // A single Facade call hides registry, access control, mediator-driven
    // dispatch and alerting. 
    // Patterns: Facade, Mediator, Composite, State, Adapter.

    banner("SCENARIO 1: Fire in the Science Building (Facade workflow)");

    step("Operator calls ONE facade operation: handleBuildingEmergency");
    Incident& fire = facade.handleBuildingEmergency("Fire", "ScienceBuilding", Severity::High);
    showStatus(fire);

    step("Subsystems remain independently usable: lock one lab directly");
    accessControl.secureArea("ScienceBuilding-Lab1", AccessLevel::Locked);

    step("Failure case: securing a zone that does not exist");
    accessControl.secureArea("Gymnasium", AccessLevel::Locked);

    step("Fire brought under control: facade stands the response down");
    facade.standDown(fire.getId());
    showStatus(fire);

    // SCENARIO 2: "Intrusion at the Library archive" (Critical severity)
    // The operator drives the response with Command objects. A dispatch
    // command triggers the Mediator to coordinate the other colleagues.
    // Patterns: Command, Mediator, Composite, State, Adapter.
    banner("SCENARIO 2: Intrusion in the Library (Operator Command workflow)");

    Incident& intrusion = registry.registerIncident("Intrusion", "Library-ArchiveRoom",
                                                    Severity::Critical);
    showStatus(intrusion);

    step("Command 1: dispatch security (Mediator then coordinates the other colleagues)");
    console.submit(std::unique_ptr<Command>(
        new DispatchUnitCommand(responseCenter, UnitKind::Security, intrusion)));
    showStatus(intrusion);

    step("Command 2: lock the archive room");
    console.submit(std::unique_ptr<Command>(
        new SecureAreaCommand(accessControl, "Library-ArchiveRoom", AccessLevel::Locked)));

    step("Command 3: issue an alert (console channel + legacy pager via Adapter)");
    console.submit(std::unique_ptr<Command>(
        new IssueAlertCommand(alertService, "Library",
                              "Intruder in archive room. Stay clear of the Library.",
                              Severity::Critical)));

    step("Command 4: evacuate the whole Library (Composite cascades to every room)");
    console.submit(std::unique_ptr<Command>(
        new EvacuateCommand(accessControl, alertService, "Library")));

    step("Operator changes their mind: undo the evacuation");
    console.undoLast();

    step("Intrusion neutralised: State pattern walks the incident to Resolved");
    intrusion.contain();
    intrusion.resolve();
    showStatus(intrusion);

    // Failure & invalid-operation cases
    banner("FAILURE CASES");

    step("Invalid transition: dispatching an already resolved incident");
    intrusion.dispatch();

    step("False alarm: register, cancel, then try to dispatch to it");
    Incident& falseAlarm = registry.registerIncident("Suspicious package", "Library-MainFloor",
                                                     Severity::Low);
    falseAlarm.cancel();
    showStatus(falseAlarm);
    falseAlarm.dispatch();

    step("Undo on an empty console");
    OperatorConsole emptyConsole;
    emptyConsole.undoLast();

    step("Lookup of an unknown incident id");
    try {
        registry.find(999);
    } catch (const std::out_of_range& ex) {
        std::cout << "[main] Handled expected error: " << ex.what() << std::endl;
    }

    return 0;
}
