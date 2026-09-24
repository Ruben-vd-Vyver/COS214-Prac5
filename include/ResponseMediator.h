#pragma once

class ResponseComponent;
struct IncidentEvent;
class ResponseMediator {
public:
    virtual ~ResponseMediator() = default;
    virtual void notify(ResponseComponent* sender, const IncidentEvent& event) = 0;
};
