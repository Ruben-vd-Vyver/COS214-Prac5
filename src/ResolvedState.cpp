#include "ResolvedState.h"
#include "Incident.h"
#include <iostream>

void ResolvedState::dispatch(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << " -> Cannot dispatch: incident is resolved." << std::endl;
}

void ResolvedState::contain(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << " -> Already resolved." << std::endl;
}

void ResolvedState::resolve(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << " -> Already resolved." << std::endl;
}

void ResolvedState::cancel(Incident& incident) {
    std::cout << "Incident #" << incident.getId() << " -> Cannot cancel: incident is already resolved." << std::endl;
}

std::string ResolvedState::name() {
    return "Resolved";
}
