#pragma once

#include <string>
class IncidentState;
enum class Severity;
class Incident {
    int id;
    std::string type;
    std::string location;
    Severity severity;
public:
    Incident(int id, const std::string& type, const std::string& location,Severity severity);
    ~Incident();
    void dispatch();
    void contain();
    void resolve();
    void cancel();
    void changeState(IncidentState* newState); // Takes ownership.
    IncidentState* getState(); // Non-owning view.
    int getId();
    const std::string& getType();
    const std::string& getLocation();
    Severity getSeverity();
};
