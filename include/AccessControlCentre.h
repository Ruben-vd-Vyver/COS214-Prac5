#pragma once

#include "ResponseComponent.h"
#include <memory>
#include <string>
class AccessZone;
enum class AccessLevel;

class AccessControlCentre : public ResponseComponent {

    std::unique_ptr<AccessZone> campusRoot;
    
public:
    explicit AccessControlCentre(ResponseMediator* mediator);
    ~AccessControlCentre() override;
    void handle(const IncidentEvent& event) override;
    bool isAvailable() override;
    void secureArea(const std::string& zoneName, AccessLevel level);
    void restoreArea(const std::string& zoneName);
};
