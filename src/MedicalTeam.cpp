#include "MedicalTeam.h"
#include "IncidentEvent.h"
#include <iostream>

void MedicalTeam::handle(const IncidentEvent& event) {
    if (event.type == "Dispatch") {
        std::cout << "MedicalTeam -> Responding to " << event.detail
                   << " for incident #" << event.incidentId << "." << std::endl;
    } else if (event.type == "ContainmentRequired") {
        std::cout << "MedicalTeam -> Standing by near " << event.detail
                   << " in case of casualties." << std::endl;
    } else {
        std::cout << "MedicalTeam -> Acknowledged event '" << event.type << "'." << std::endl;
    }
}

bool MedicalTeam::isAvailable() {
    return true;
}
