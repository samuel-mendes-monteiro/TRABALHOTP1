#ifndef TASK_CONTAINER_H
#define TASK_CONTAINER_H

#include <map>
#include <string>
#include <vector>
#include "../Entities/Task.h"

/**
 * @brief Contêiner que armazena objetos Task em memória, indexados por identificador.
 */
class TaskContainer {
private:
    std::map<std::string, Task> items;

public:
    bool insert(const Task& task) {
        return items.insert({task.getIdentifier().getValue(), task}).second;
    }

    bool find(const Identifier& id, Task& out) const {
        auto it = items.find(id.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    bool exists(const Identifier& id) const {
        return items.count(id.getValue()) > 0;
    }

    bool update(const Task& task) {
        auto it = items.find(task.getIdentifier().getValue());
        if (it == items.end()) return false;
        it->second = task;
        return true;
    }

    bool remove(const Identifier& id) {
        return items.erase(id.getValue()) > 0;
    }

    std::vector<Task> getAll() const {
        std::vector<Task> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }

    /** Cartões do quadro informado. */
    std::vector<Task> getByBoard(const Identifier& boardId) const {
        std::vector<Task> result;
        for (const auto& pair : items)
            if (pair.second.getBoardId().getValue() == boardId.getValue())
                result.push_back(pair.second);
        return result;
    }

    /** Cartões atribuídos ao desenvolvedor informado. */
    std::vector<Task> getByDeveloper(const Email& email) const {
        std::vector<Task> result;
        for (const auto& pair : items)
            if (pair.second.getDeveloperEmail().getValue() == email.getValue())
                result.push_back(pair.second);
        return result;
    }

    /** Quantidade de cartões do quadro em determinado estado (base do WIP). */
    int countByBoardAndState(const Identifier& boardId, const std::string& state) const {
        int count = 0;
        for (const auto& pair : items)
            if (pair.second.getBoardId().getValue() == boardId.getValue() &&
                pair.second.getState().getValue() == state)
                count++;
        return count;
    }
};

#endif