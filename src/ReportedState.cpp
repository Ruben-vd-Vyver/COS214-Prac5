#include "ReportedState.h"
#include "DispatchedState.h"
#include "CancelledState.h"
#include "Incident.h"
#include <iostream>

void ReportedState::dispatch(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << " -> Reported -> Dispatched." << std::endl;
    incident.changeState(new DispatchedState());
}

void ReportedState::contain(Incident& incident) {
    std::cout << "Incident #" << incident.getId()
               << " -> Cannot contain: incident has not been dispatched yet." << std::endl;
}

void ReportedState::resolve(Incident& incident) {
    std::cout << "Incident #" << incident.getId()
               << " -> Cannot resolve: incident has not been dispatched yet." << std::endl;
}

void ReportedState::cancel(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << " -> Reported -> Cancelled." << std::endl;
    incident.changeState(new CancelledState());
}

std::string ReportedState::name() {
    return "Reported";
}
