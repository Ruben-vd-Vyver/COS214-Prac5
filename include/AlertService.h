#pragma once

#include <memory>
#include <string>
#include <vector>
class AlertChannel;
enum class Severity;
class AlertService {
    std::vector<std::unique_ptr<AlertChannel>> channels;
public:
    ~AlertService();
    void addChannel(std::unique_ptr<AlertChannel> channel);
    void broadcast(const std::string& audience, const std::string& message,Severity severity);
};
