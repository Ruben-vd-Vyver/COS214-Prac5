#pragma once

#include "Command.h"
class Incident;
class ResponseCenter;
enum class UnitKind;
class DispatchUnitCommand : public Command {
    ResponseCenter& receiver;
    UnitKind kind;
    Incident& incident;
public:
    DispatchUnitCommand(ResponseCenter& receiver, UnitKind kind, Incident& incident);
    void execute() override;
    void undo() override;
    std::string describe() override;
};
