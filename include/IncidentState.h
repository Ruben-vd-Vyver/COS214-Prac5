#pragma once

#include <string>
class Incident;
class IncidentState {
public:
    virtual ~IncidentState() = default;
    virtual void dispatch(Incident& incident) = 0;
    virtual void contain(Incident& incident) = 0;
    virtual void resolve(Incident& incident) = 0;
    virtual void cancel(Incident& incident) = 0;
    virtual std::string name() = 0;
};
