#include "Incident.h"
#include "IncidentState.h"
#include "ReportedState.h"
#include "Severity.h"

Incident::Incident(int id, const std::string& type, const std::string& location, Severity severity)
    : id(id), type(type), location(location), severity(severity), state(new ReportedState()) {}

Incident::~Incident() {
    delete state;
}

void Incident::dispatch() {
    state->dispatch(*this);
}

void Incident::contain() {
    state->contain(*this);
}

void Incident::resolve() {
    state->resolve(*this);
}

void Incident::cancel() {
    state->cancel(*this);
}

void Incident::changeState(IncidentState* newState) {
    delete state;
    state = newState;
}

IncidentState* Incident::getState() {
    return state;
}

int Incident::getId() {
    return id;
}

const std::string& Incident::getType() {
    return type;
}

const std::string& Incident::getLocation() {
    return location;
}

Severity Incident::getSeverity() {
    return severity;
}
