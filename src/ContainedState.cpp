#include "ContainedState.h"
#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

void ContainedState::dispatch(Incident& incident) {
    std::cout << "Incident #" << incident.getId()
               << "-> Already dispatched and contained." << std::endl;
}

void ContainedState::contain(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Already contained." << std::endl;
}

void ContainedState::resolve(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << "-> Contained -> Resolved." << std::endl;
    incident.changeState(new ResolvedState());
}

void ContainedState::cancel(Incident& incident) {
    std::cout << "Incident #" << incident.getId()
               << "_> Cannot cancel: incident is already contained. Resolve it instead." << std::endl;
}

std::string ContainedState::name() {
    return "Contained";
}
