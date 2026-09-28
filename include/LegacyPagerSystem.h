#pragma once

class LegacyPagerSystem {
public:
    ~LegacyPagerSystem();
    int transmitPage(int zoneCode, const char* text, int priority);
};
