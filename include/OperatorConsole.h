#pragma once

#include <memory>
#include <vector>
class Command;
class OperatorConsole {
    std::vector<std::unique_ptr<Command>> history;
public:
    ~OperatorConsole();
    void submit(std::unique_ptr<Command> command);
    void undoLast();
};
