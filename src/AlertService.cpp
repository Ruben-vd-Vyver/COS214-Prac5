#include "AlertService.h"
#include "AlertChannel.h"

AlertService::~AlertService() = default;

void AlertService::addChannel(std::unique_ptr<AlertChannel> channel) {
    channels.push_back(std::move(channel));
}

void AlertService::broadcast(const std::string& audience, const std::string& message,
                              Severity severity) {
    for (auto& channel : channels) {
        channel->send(audience, message, severity);
    }
}
