#ifndef BOARD_SERVICE_H
#define BOARD_SERVICE_H

#include "../Interfaces/IBoardService.h"
#include "../Containers/ProjectContainer.h"
#include "../Containers/BoardContainer.h"
#include "../Containers/TaskContainer.h"

/**
 * @brief Implementa os serviços da entidade Board. Excluir um quadro exclui seus cartões.
 */
class BoardService : public IBoardService {
private:
    BoardContainer& boards;
    ProjectContainer& projects;
    TaskContainer& tasks;

public:
    BoardService(BoardContainer& boards, ProjectContainer& projects, TaskContainer& tasks);

    bool createBoard(const Board& board) override;
    Board readBoard(const Identifier& identifier) override;
    bool updateBoard(const Board& board) override;
    bool deleteBoard(const Identifier& identifier) override;
    std::vector<Identifier> listBoards() override;
};

#endif