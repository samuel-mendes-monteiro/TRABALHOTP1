#include "../../include/Services/BoardService.h"
#include <stdexcept>

BoardService::BoardService(BoardContainer& boards, ProjectContainer& projects, TaskContainer& tasks)
    : boards(boards), projects(projects), tasks(tasks) {}

bool BoardService::createBoard(const Board& board) {
    if (!projects.exists(board.getProjectId()))
        throw std::invalid_argument("Projeto nao encontrado.");
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

    // Novo limite nao pode ficar abaixo do WIP atual.
    int wip = tasks.countByBoardAndState(board.getIdentifier(), "FAZENDO");
    if (board.getLimit().getValue() < wip)
        throw std::invalid_argument("Novo limite menor que o WIP atual do quadro.");

    // O projeto do quadro nao muda na atualizacao.
    Board updated = board;
    updated.setProjectId(existing.getProjectId());
    return boards.update(updated);
}

bool BoardService::deleteBoard(const Identifier& identifier) {
    if (!boards.exists(identifier)) return false;

    for (const auto& task : tasks.getByBoard(identifier))
        tasks.remove(task.getIdentifier());
    return boards.remove(identifier);
}

std::vector<Identifier> BoardService::listBoards() {
    std::vector<Identifier> result;
    for (const auto& b : boards.getAll()) result.push_back(b.getIdentifier());
    return result;
}