#pragma once

#include "ResponseComponent.h"
class SecurityTeam : public ResponseComponent {
public:
    using ResponseComponent::ResponseComponent;
    void handle(const IncidentEvent& event) override;
    bool isAvailable() override;
};
