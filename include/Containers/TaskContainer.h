#ifndef PROJECT_CONTAINER_H
#define PROJECT_CONTAINER_H

#include <map>
#include <string>
#include <vector>
#include "../Entities/Project.h"

/**
 * @brief Contêiner que armazena objetos Project em memória, indexados por identificador.
 */
class ProjectContainer {
private:
    std::map<std::string, Project> items;

public:
    bool insert(const Project& project) {
        return items.insert({project.getIdentifier().getValue(), project}).second;
    }

    bool find(const Identifier& id, Project& out) const {
        auto it = items.find(id.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    bool exists(const Identifier& id) const {
        return items.count(id.getValue()) > 0;
    }

    bool update(const Project& project) {
        auto it = items.find(project.getIdentifier().getValue());
        if (it == items.end()) return false;
        it->second = project;
        return true;
    }

    bool remove(const Identifier& id) {
        return items.erase(id.getValue()) > 0;
    }

    std::vector<Project> getAll() const {
        std::vector<Project> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }

    /** Projetos cujo gestor é o e-mail informado. */
    std::vector<Project> getByManager(const Email& email) const {
        std::vector<Project> result;
        for (const auto& pair : items)
            if (pair.second.getManagerEmail().getValue() == email.getValue())
                result.push_back(pair.second);
        return result;
    }
};

#endif