#include "OperatorConsole.h"
#include "Command.h"
#include <iostream>

OperatorConsole::~OperatorConsole() = default;

void OperatorConsole::submit(std::unique_ptr<Command> command) {
    std::cout << "OperatorConsole -> Executing: " << command->describe() << std::endl;
    command->execute();
    history.push_back(std::move(command));
}

void OperatorConsole::undoLast() {
    if (history.empty()) {
        std::cout << "OperatorConsole -> No command to undo." << std::endl;
        return;
    }
    std::cout << "OperatorConsole -> Undoing: " << history.back()->describe() << std::endl;
    history.back()->undo();
    history.pop_back();
}
