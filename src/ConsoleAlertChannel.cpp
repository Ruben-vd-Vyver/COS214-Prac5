#include "ConsoleAlertChannel.h"
#include "Severity.h"
#include <iostream>

namespace {
std::string severityLabel(Severity severity) {
    switch (severity) {
        case Severity::Low: return "LOW";
        case Severity::Medium: return "MEDIUM";
        case Severity::High: return "HIGH";
        case Severity::Critical: return "CRITICAL";
    }
    return "UNKNOWN";
}
} // namespace

void ConsoleAlertChannel::send(const std::string& audience, const std::string& message,
                                Severity severity) {
    std::cout << "[ConsoleAlert]" << severityLabel(severity) << "-> To " << audience
               << ": " << message << std::endl;
}
