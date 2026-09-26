#include "IncidentRegistry.h"
#include "Incident.h"
#include "Severity.h"
#include <stdexcept>
#include <sstream>

IncidentRegistry::~IncidentRegistry() = default;

Incident& IncidentRegistry::registerIncident(const std::string& type, const std::string& location,
                                              Severity severity) {
    int newId = static_cast<int>(incidents.size()) + 1;
    incidents.push_back(std::unique_ptr<Incident>(new Incident(newId, type, location, severity)));
    return *incidents.back();
}

Incident& IncidentRegistry::find(int id) {
    for (auto& incident : incidents) {
        if (incident->getId() == id) {
            return *incident;
        }
    }
    std::ostringstream oss;
    oss << "IncidentRegistry: no incident with id " << id;
    throw std::out_of_range(oss.str());
}
