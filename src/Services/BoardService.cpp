#include "../../include/Services/BoardService.h"
#include <stdexcept>

BoardService::BoardService(BoardContainer& boards)
    : boards(boards), projectService(nullptr), taskService(nullptr) {}

void BoardService::setProjectService(IProjectService* service) {
    projectService = service;
}

void BoardService::setTaskService(ITaskService* service) {
    taskService = service;
}

bool BoardService::createBoard(const Board& board) {
    if (!projectService) throw std::logic_error("Servico de projetos nao configurado.");

    // Valida o projeto pelo modulo Projetos (interface IProjectService).
    try {
        projectService->readProject(board.getProjectId());
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("Projeto nao encontrado.");
    }
    return boards.insert(board);
}

Board BoardService::readBoard(const Identifier& identifier) {
    Board out;
    if (!boards.find(identifier, out)) throw std::invalid_argument("Quadro nao encontrado.");
    return out;
}

bool BoardService::updateBoard(const Board& board) {
    Board existing;
    if (!boards.find(board.getIdentifier(), existing)) return false;
    if (!taskService) throw std::logic_error("Servico de cartoes nao configurado.");

    // Novo limite nao pode ficar abaixo do WIP atual (modulo Cartoes, interface ITaskService).
    int wip = taskService->readWip(board.getIdentifier());
    if (board.getLimit().getValue() < wip)
        throw std::invalid_argument("Novo limite menor que o WIP atual do quadro.");

    // O projeto do quadro nao muda na atualizacao.
    Board updated = board;
    updated.setProjectId(existing.getProjectId());
    return boards.update(updated);
}

bool BoardService::deleteBoard(const Identifier& identifier) {
    if (!boards.exists(identifier)) return false;
    if (!taskService) throw std::logic_error("Servico de cartoes nao configurado.");

    // Cascata pelo modulo Cartoes (interface ITaskService).
    for (const auto& taskId : taskService->listTasks())
        if (taskService->readTask(taskId).getBoardId().getValue() == identifier.getValue())
            taskService->deleteTask(taskId);

    return boards.remove(identifier);
}

std::vector<Identifier> BoardService::listBoards() {
    std::vector<Identifier> result;
    for (const auto& b : boards.getAll()) result.push_back(b.getIdentifier());
    return result;
}
