#include "AccessControlCentre.h"
#include "AccessZone.h"
#include "ZoneGroup.h"
#include "Room.h"
#include "AccessLevel.h"
#include "IncidentEvent.h"
#include <iostream>

AccessControlCentre::AccessControlCentre(ResponseMediator* mediator)
    : ResponseComponent(mediator) {
    // Build the campus access hierarchy
    auto* campus = new ZoneGroup("Campus");

    auto* scienceBuilding = new ZoneGroup("ScienceBuilding");
    scienceBuilding->add(new Room("ScienceBuilding-Lab1"));
    scienceBuilding->add(new Room("ScienceBuilding-Lab2"));
    scienceBuilding->add(new Room("ScienceBuilding-LectureHall"));

    auto* library = new ZoneGroup("Library");
    library->add(new Room("Library-MainFloor"));
    library->add(new Room("Library-ArchiveRoom"));

    campus->add(scienceBuilding);
    campus->add(library);

    campusRoot.reset(campus);
}

AccessControlCentre::~AccessControlCentre() = default;

void AccessControlCentre::handle(const IncidentEvent& event) {
    std::cout << "[AccessControlCentre] Coordinating on '" << event.type
              << "' for incident #" << event.incidentId << " (" << event.detail << ")."
              << std::endl;

    if (event.type == "ContainmentRequired") {
        // A colleague has asked, through the mediator,
        // for the affected area to be restricted.
        secureArea(event.detail, AccessLevel::Restricted);
    }
}

bool AccessControlCentre::isAvailable() {
    return true;
}

void AccessControlCentre::secureArea(const std::string& zoneName, AccessLevel level) {
    AccessZone* zone = campusRoot->find(zoneName);
    if (zone == nullptr) {
        std::cout << "AccessControlCentre -> Unknown zone '" << zoneName
                   << "' - cannot secure it." << std::endl;
        return;
    }

    switch (level) {
        case AccessLevel::Locked:
            zone->lock();
            break;
        case AccessLevel::Restricted:
            zone->restrict();
            break;
        case AccessLevel::Normal:
            zone->unlock();
            break;
    }
}

void AccessControlCentre::restoreArea(const std::string& zoneName) {
    AccessZone* zone = campusRoot->find(zoneName);
    if (zone == nullptr) {
        std::cout << "AccessControlCentre-> Unknown zone '" << zoneName
                   << "' - cannot restore it." << std::endl;
        return;
    }
    zone->unlock();
}
