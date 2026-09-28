#include "FacilitiesTeam.h"
#include "IncidentEvent.h"
#include <iostream>

void FacilitiesTeam::handle(const IncidentEvent& event) {
    if (event.type == "Dispatch") {
        std::cout << "FacilitiesTeam -> Preparing site support at " << event.detail
                   << " for incident #" << event.incidentId << "." << std::endl;
    } else if (event.type == "ContainmentRequired") {
        std::cout << "FacilitiesTeam -> Shutting down utilities near " << event.detail
                   << " to assist containment." << std::endl;
    } else {
        std::cout << "FacilitiesTeam -> Acknowledged event '" << event.type << "'." << std::endl;
    }
}

bool FacilitiesTeam::isAvailable() {
    return true;
}
