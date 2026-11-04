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
    /**
     * @brief Construtor.
     * @param boards Contêiner de quadros.
     * @param projects Contêiner de projetos (para validar o projeto do quadro).
     * @param tasks Contêiner de cartões (para o WIP e a exclusão em cascata).
     */
    BoardService(BoardContainer& boards, ProjectContainer& projects, TaskContainer& tasks);

    /** @copydoc IBoardService::createBoard */
    bool createBoard(const Board& board) override;

    /** @copydoc IBoardService::readBoard */
    Board readBoard(const Identifier& identifier) override;

    /** @copydoc IBoardService::updateBoard */
    bool updateBoard(const Board& board) override;

    /** @copydoc IBoardService::deleteBoard */
    bool deleteBoard(const Identifier& identifier) override;

    /** @copydoc IBoardService::listBoards */
    std::vector<Identifier> listBoards() override;
};

#endif
