#include "ResponseCenter.h"
#include "ResponseComponent.h"
#include "SecurityTeam.h"
#include "MedicalTeam.h"
#include "FacilitiesTeam.h"
#include "IncidentEvent.h"
#include "Incident.h"
#include "UnitKind.h"
#include <iostream>

ResponseCenter::~ResponseCenter() {
    // components is a non-owning list; ResponseCenter does not delete
    // its colleagues.
}

void ResponseCenter::addComponent(ResponseComponent* component) {
    components.push_back(component);
}

void ResponseCenter::dispatchUnit(UnitKind kind, Incident& incident) {
    for (auto* component : components) {
        bool matches = false;
        switch (kind) {
            case UnitKind::Security:
                matches = (dynamic_cast<SecurityTeam*>(component) != nullptr);
                break;
            case UnitKind::Medical:
                matches = (dynamic_cast<MedicalTeam*>(component) != nullptr);
                break;
            case UnitKind::Facilities:
                matches = (dynamic_cast<FacilitiesTeam*>(component) != nullptr);
                break;
        }

        if (!matches) {
            continue;
        }

        if (!component->isAvailable()) {
            std::cout << "ResponseCenter -> Requested unit is not available for incident #"
                       << incident.getId() << "." << std::endl;
            return;
        }

        IncidentEvent event{incident.getId(), "Dispatch", incident.getLocation()};
        component->handle(event);
        return;
    }

    std::cout << "ResponseCenter -> No matching response unit is registered for this request."
               << std::endl;
}

void ResponseCenter::notify(ResponseComponent* sender, const IncidentEvent& event) {
    std::cout << "ResponseCenter -> Mediating '" << event.type
               << "' for incident #" << event.incidentId << "." << std::endl;

    for (auto* component : components) {
        if (component == sender) {
            continue; // Colleagues do not need to be told about their own action.
        }
        if (component->isAvailable()) {
            component->handle(event);
        }
    }
}
