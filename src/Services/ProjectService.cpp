#include "../../include/Services/ProjectService.h"
#include <stdexcept>

ProjectService::ProjectService(ProjectContainer& projects)
    : projects(projects), personService(nullptr), boardService(nullptr) {}

void ProjectService::setPersonService(IPersonService* service) {
    personService = service;
}

void ProjectService::setBoardService(IBoardService* service) {
    boardService = service;
}

bool ProjectService::createProject(const Project& project) {
    if (!personService) throw std::logic_error("Servico de pessoas nao configurado.");

    // Valida o gestor pelo modulo Pessoas (interface IPersonService).
    Person manager;
    try {
        manager = personService->readPerson(project.getManagerEmail());
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("Gestor nao encontrado.");
    }
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
    if (!boardService) throw std::logic_error("Servico de quadros nao configurado.");

    // Cascata pelo modulo Quadros (interface IBoardService): excluir o quadro
    // tambem exclui os cartoes dele.
    for (const auto& boardId : boardService->listBoards())
        if (boardService->readBoard(boardId).getProjectId().getValue() == identifier.getValue())
            boardService->deleteBoard(boardId);

    return projects.remove(identifier);
}

std::vector<Identifier> ProjectService::listProjects() {
    std::vector<Identifier> result;
    for (const auto& p : projects.getAll()) result.push_back(p.getIdentifier());
    return result;
}
