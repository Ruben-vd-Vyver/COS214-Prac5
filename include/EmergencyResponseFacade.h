#pragma once

#include <string>
class AccessControlCentre;
class AlertService;
class Incident;
class IncidentRegistry;
class ResponseCenter;
enum class Severity;
class EmergencyResponseFacade {
    IncidentRegistry& registry;
    ResponseCenter& responseCenter;
    AccessControlCentre& accessControl;
    AlertService& alertService;

public:
    EmergencyResponseFacade(IncidentRegistry& registry, ResponseCenter& responseCenter,AccessControlCentre& accessControl, AlertService& alertService);
    ~EmergencyResponseFacade();
    Incident& handleBuildingEmergency(const std::string& type,const std::string& building, Severity severity);
    void standDown(int incidentId);
};
