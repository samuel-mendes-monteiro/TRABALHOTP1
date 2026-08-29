#include "../../include/Services/ProjectService.h"
#include <stdexcept>
#include <algorithm>

bool ProjectService::createProject(const Project& project) {
    for (const auto& p : projects) {
        if (p.getIdentifier().getValue() == project.getIdentifier().getValue()) {
            return false; // Chave primária duplicada
        }
    }
    projects.push_back(project);
    return true;
}

Project ProjectService::readProject(const Identifier& identifier) {
    for (const auto& p : projects) {
        if (p.getIdentifier().getValue() == identifier.getValue()) {
            return p;
        }
    }
    throw std::invalid_argument("Project not found.");
}

bool ProjectService::updateProject(const Project& project) {
    for (auto& p : projects) {
        if (p.getIdentifier().getValue() == project.getIdentifier().getValue()) {
            p = project;
            return true;
        }
    }
    return false;
}

bool ProjectService::deleteProject(const Identifier& identifier) {
    auto it = std::remove_if(projects.begin(), projects.end(), [&](const Project& p) {
        return p.getIdentifier().getValue() == identifier.getValue();
    });

    if (it != projects.end()) {
        projects.erase(it, projects.end());
        return true;
    }
    return false;
}