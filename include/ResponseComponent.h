#pragma once

class ResponseMediator;
struct IncidentEvent;
class ResponseComponent {
protected:
    ResponseMediator* mediator; // Non-owning; mediator must outlive this component.
public:
    explicit ResponseComponent(ResponseMediator* mediator);
    virtual ~ResponseComponent() = default;
    virtual void handle(const IncidentEvent& event) = 0;
    virtual bool isAvailable() = 0;
};
