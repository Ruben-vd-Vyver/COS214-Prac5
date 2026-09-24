#pragma once

#include "ResponseComponent.h"
class FacilitiesTeam : public ResponseComponent {
public:
    using ResponseComponent::ResponseComponent;
    void handle(const IncidentEvent& event) override;
    bool isAvailable() override;
};
