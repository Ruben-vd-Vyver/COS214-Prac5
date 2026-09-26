#include "PagerAlertAdapter.h"
#include "Severity.h"
#include <functional>
#include <iostream>

// Adapter translates the CampusGuard AlertChannel interface
// into the incompatible LegacyPagerSystem interface

PagerAlertAdapter::PagerAlertAdapter() = default;
PagerAlertAdapter::~PagerAlertAdapter() = default;

void PagerAlertAdapter::send(const std::string& audience, const std::string& message,
                              Severity severity) {
    int zoneCode = audienceToZoneCode(audience);
    int priority = severityToPriority(severity);

    int result = pager.transmitPage(zoneCode, message.c_str(), priority);
    if (result != 0) {
        std::cout << "PagerAlertAdapter -> Legacy pager system failed to deliver to '"
                   << audience << "'." << std::endl;
    }
}

int PagerAlertAdapter::audienceToZoneCode(const std::string& audience) {
    // The legacy system only understands numeric zone codes, so derive a
    // stable code from the audience name.
    std::hash<std::string> hasher;
    return static_cast<int>(hasher(audience) % 1000);
}

int PagerAlertAdapter::severityToPriority(Severity severity) {
    switch (severity) {
        case Severity::Low: return 1;
        case Severity::Medium: return 2;
        case Severity::High: return 3;
        case Severity::Critical: return 4;
    }
    return 0;
}
