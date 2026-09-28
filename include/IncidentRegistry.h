#pragma once

#include <memory>
#include <string>
#include <vector>
class Incident;
enum class Severity;
class IncidentRegistry {
    std::vector<std::unique_ptr<Incident>> incidents;
public:
    ~IncidentRegistry();
    Incident& registerIncident(const std::string& type, const std::string& location,Severity severity);
    Incident& find(int id);
};
