#include "SecurityTeam.h"
#include "ResponseMediator.h"
#include "IncidentEvent.h"
#include <iostream>

void SecurityTeam::handle(const IncidentEvent& event) {
    if (event.type == "Dispatch") {
        std::cout << "SecurityTeam -> Deploying to " << event.detail
                   << " for incident #" << event.incidentId << "." << std::endl;
        // A dispatched security team needs the area locked down, call mediator
        IncidentEvent followUp{event.incidentId, "ContainmentRequired", event.detail};
        mediator->notify(this, followUp);
    } else if (event.type == "ContainmentRequired") {
        std::cout << "SecurityTeam -> Assisting with containment at " << event.detail << "." << std::endl;
    } else {
        std::cout << "SecurityTeam -> Acknowledged event '" << event.type << "'." << std::endl;
    }
}

bool SecurityTeam::isAvailable() {
    return true;
}
