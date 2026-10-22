#include "../../include/Services/ProjectService.h"
#include <stdexcept>

ProjectService::ProjectService(ProjectContainer& projects, PersonContainer& persons,
                               BoardContainer& boards, TaskContainer& tasks)
    : projects(projects), persons(persons), boards(boards), tasks(tasks) {}

bool ProjectService::createProject(const Project& project) {
    Person manager;
    if (!persons.find(project.getManagerEmail(), manager))
        throw std::invalid_argument("Gestor nao encontrado.");
    if (manager.getRole().getValue() != "GESTOR")
        throw std::invalid_argument("O criador do projeto deve ter o papel GESTOR.");
    if (project.getEnd().toMinutes() < project.getStart().toMinutes())
        throw std::invalid_argument("Data de termino anterior a data de inicio.");

    return projects.insert(project);
}

Project ProjectService::readProject(const Identifier& identifier) {
    Project out;
    if (!projects.find(identifier, out)) throw std::invalid_argument("Projeto nao encontrado.");
    return out;
}

bool ProjectService::updateProject(const Project& project) {
    Project existing;
    if (!projects.find(project.getIdentifier(), existing)) return false;

    if (project.getEnd().toMinutes() < project.getStart().toMinutes())
        throw std::invalid_argument("Data de termino anterior a data de inicio.");

    // O gestor e quem criou o projeto: nao muda na atualizacao.
    Project updated = project;
    updated.setManagerEmail(existing.getManagerEmail());
    return projects.update(updated);
}

bool ProjectService::deleteProject(const Identifier& identifier) {
    if (!projects.exists(identifier)) return false;

    // Cascata: cartoes -> quadros -> projeto
    for (const auto& board : boards.getByProject(identifier)) {
        for (const auto& task : tasks.getByBoard(board.getIdentifier()))
            tasks.remove(task.getIdentifier());
        boards.remove(board.getIdentifier());
    }
    return projects.remove(identifier);
}

std::vector<Identifier> ProjectService::listProjects() {
    std::vector<Identifier> result;
    for (const auto& p : projects.getAll()) result.push_back(p.getIdentifier());
    return result;
}