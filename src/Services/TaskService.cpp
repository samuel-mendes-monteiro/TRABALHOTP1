#include "../../include/Services/TaskService.h"
#include <stdexcept>
#include <algorithm>

bool TaskService::createTask(const Task& task) {
    for (const auto& t : tasks) {
        if (t.getIdentifier().getValue() == task.getIdentifier().getValue()) {
            return false;
        }
    }
    tasks.push_back(task);
    return true;
}

Task TaskService::readTask(const Identifier& identifier) {
    for (const auto& t : tasks) {
        if (t.getIdentifier().getValue() == identifier.getValue()) {
            return t;
        }
    }
    throw std::invalid_argument("Task not found.");
}

bool TaskService::updateTask(const Task& task) {
    for (auto& t : tasks) {
        if (t.getIdentifier().getValue() == task.getIdentifier().getValue()) {
            t = task;
            return true;
        }
    }
    return false;
}

bool TaskService::deleteTask(const Identifier& identifier) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [&](const Task& t) {
        return t.getIdentifier().getValue() == identifier.getValue();
    });

    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return true;
    }
    return false;
}

bool TaskService::moveTask(const Identifier& identifier, const State& newState) {
    for (auto& t : tasks) {
        if (t.getIdentifier().getValue() == identifier.getValue()) {
            std::string currentState = t.getState().getValue();
            std::string targetState = newState.getValue();

            // Validação das regras de movimentação do Kanban: A FAZER -> FAZENDO e FAZENDO -> FEITO
            if ((currentState == "A FAZER" && targetState == "FAZENDO") ||
                (currentState == "FAZENDO" && targetState == "FEITO")) {
                t.setState(newState);
                return true;
            }
            return false; // Movimentação inválida pelas regras do negócio
        }
    }
    return false;
}