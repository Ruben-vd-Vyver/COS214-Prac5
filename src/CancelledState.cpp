#include "CancelledState.h"
#include "Incident.h"
#include <iostream>

void CancelledState::dispatch(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Cannot dispatch: incident is cancelled." << std::endl;
}

void CancelledState::contain(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Cannot contain: incident is cancelled." << std::endl;
}

void CancelledState::resolve(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Cannot resolve: incident is cancelled." << std::endl;
}

void CancelledState::cancel(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Already cancelled." << std::endl;
}

std::string CancelledState::name() {
    return "Cancelled";
}
