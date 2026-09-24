#pragma once

#include "IncidentState.h"
class CancelledState : public IncidentState {
public:
    void dispatch(Incident& incident) override;
    void contain(Incident& incident) override;
    void resolve(Incident& incident) override;
    void cancel(Incident& incident) override;
    std::string name() override;
};
