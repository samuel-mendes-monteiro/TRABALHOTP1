#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include "../Interfaces/IBoardService.h"
#include "Session.h"

/**
 * @brief Classe controladora da camada de apresentação para gerenciar interações de Board (Quadro).
 *
 * Responsável por receber dados do usuário via terminal, validar as entradas,
 * verificar permissões pelo papel da sessão e acionar os serviços através da
 * interface IBoardService.
 */
class BoardController {
private:
    IBoardService* boardService;
    Session& session;

public:
    /**
     * @brief Construtor.
     * @param service Ponteiro para uma implementação de IBoardService.
     * @param session Sessão do usuário autenticado.
     */
    BoardController(IBoardService* service, Session& session);

    /**
     * @brief Executa o fluxo de interação para criar um novo quadro (restrito ao GESTOR).
     */
    void handleCreateBoard();

    /**
     * @brief Lista os identificadores de todos os quadros.
     */
    void handleListBoards();

    /**
     * @brief Executa o fluxo de interação para consultar os dados de um quadro.
     */
    void handleReadBoard();

    /**
     * @brief Executa o fluxo de interação para atualizar um quadro existente (restrito ao GESTOR).
     */
    void handleUpdateBoard();

    /**
     * @brief Executa o fluxo de interação para excluir um quadro (restrito ao GESTOR).
     */
    void handleDeleteBoard();
};

#endif
