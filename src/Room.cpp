#include "Room.h"
#include "AccessLevel.h"
#include <iostream>

Room::Room(const std::string& name)
    : AccessZone(name), currentLevel(AccessLevel::Normal) {}

void Room::lock() {
    currentLevel = AccessLevel::Locked;
    std::cout << "Room -> " << getName() << " is now LOCKED." << std::endl;
}

void Room::unlock() {
    currentLevel = AccessLevel::Normal;
    std::cout << "Room -> " << getName() << " is now UNLOCKED." << std::endl;
}

void Room::restrict() {
    currentLevel = AccessLevel::Restricted;
    std::cout << "Room -> " << getName() << " is now RESTRICTED." << std::endl;
}

AccessLevel Room::level() {
    return currentLevel;
}
