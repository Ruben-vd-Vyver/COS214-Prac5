#include "DispatchedState.h"
#include "ContainedState.h"
#include "CancelledState.h"
#include "Incident.h"
#include <iostream>

void DispatchedState::dispatch(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Already dispatched." << std::endl;
}

void DispatchedState::contain(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Dispatched -> Contained." << std::endl;
    incident.changeState(new ContainedState());
}

void DispatchedState::resolve(Incident& incident) {
    std::cout << "Incident #" << incident.getId()
               << "-> Cannot resolve: incident has not been contained yet." << std::endl;
}

void DispatchedState::cancel(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Dispatched -> Cancelled." << std::endl;
    incident.changeState(new CancelledState());
}

std::string DispatchedState::name() {
    return "Dispatched";
}
