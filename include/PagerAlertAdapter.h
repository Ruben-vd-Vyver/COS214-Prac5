#pragma once

#include "AlertChannel.h"
#include "LegacyPagerSystem.h"
class PagerAlertAdapter : public AlertChannel {
    LegacyPagerSystem pager;
public:
    PagerAlertAdapter();
    ~PagerAlertAdapter() override;
    void send(const std::string& audience, const std::string& message,Severity severity) override;
private:
    int audienceToZoneCode(const std::string& audience);
    int severityToPriority(Severity severity);
};
