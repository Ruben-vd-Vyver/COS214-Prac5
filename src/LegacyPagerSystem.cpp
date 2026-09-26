#include "LegacyPagerSystem.h"
#include <cstdio>

// Simulates a pre-existing legacy paging system with a retro interface
// that CampusGuard cannot change
LegacyPagerSystem::~LegacyPagerSystem() = default;

int LegacyPagerSystem::transmitPage(int zoneCode, const char* text, int priority) {
    std::printf("LegacyPagerSystem -> PAGE zone=%d priority=%d text=\"%s\"\n",
                zoneCode, priority, text);
    if (zoneCode < 0 || text == nullptr) {
        return -1; // legacy failure code
    }
    return 0; // legacy success code
}
