#ifndef BOARD_SERVICE_H
#define BOARD_SERVICE_H

#include "../Interfaces/IBoardService.h"
#include "../Interfaces/IProjectService.h"
#include "../Interfaces/ITaskService.h"
#include "../Containers/BoardContainer.h"

/**
 * @brief Implementa os serviços da entidade Board (módulo Quadros).
 *
 * Armazena os quadros no próprio contêiner. Valida o projeto do quadro por meio da
 * interface IProjectService e usa a interface ITaskService para obter o WIP atual e
 * para excluir os cartões de um quadro excluído.
 */
class BoardService : public IBoardService {
private:
    BoardContainer& boards;
    IProjectService* projectService;
    ITaskService* taskService;

public:
    /**
     * @brief Construtor.
     * @param boards Contêiner de quadros, de uso exclusivo deste módulo.
     */
    explicit BoardService(BoardContainer& boards);

    /**
     * @brief Define o serviço de projetos usado para validar o projeto do quadro.
     * @param service Ponteiro para a interface IProjectService (deve ser definido antes do uso).
     */
    void setProjectService(IProjectService* service);

    /**
     * @brief Define o serviço de cartões usado para obter o WIP e para a exclusão em cascata.
     * @param service Ponteiro para a interface ITaskService (deve ser definido antes do uso).
     */
    void setTaskService(ITaskService* service);

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
