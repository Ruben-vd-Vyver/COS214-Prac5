#pragma once

#include "ResponseMediator.h"
#include <vector>
class Incident;
enum class UnitKind;
class ResponseCenter : public ResponseMediator {
    std::vector<ResponseComponent*> components; // Non-owning colleagues.
public:
    ~ResponseCenter() override;
    void addComponent(ResponseComponent* component);
    void dispatchUnit(UnitKind kind, Incident& incident);
    void notify(ResponseComponent* sender, const IncidentEvent& event) override;
};
