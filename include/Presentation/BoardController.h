#ifndef BOARD_CONTROLLER_H
#define BOARD_CONTROLLER_H

#include "../Interfaces/IBoardService.h"
#include "Session.h"


/**
 * @brief Classe controladora da camada de apresentação para gerenciar interações de Board (Quadro).
 * 
 * Responsável por receber dados do usuário via terminal, validar as entradas
 * e acionar os serviços através da interface IBoardService.
 */
class BoardController {
private:
    IBoardService* boardService;
    Session& session;


public:
    /**
     * @brief Construtor que recebe a referência para a interface de serviço de quadros.
     * @param service Ponteiro para uma implementação de IBoardService.
     */
    BoardController(IBoardService* service, Session& session);

    /**
     * @brief Executa o fluxo de interação para criar um novo quadro.
     */
    void handleCreateBoard();

    void handleListBoards();

    /**
     * @brief Executa o fluxo de interação para consultar os dados de um quadro.
     */
    void handleReadBoard();

    /**
     * @brief Executa o fluxo de interação para atualizar um quadro existente.
     */
    void handleUpdateBoard();

    /**
     * @brief Executa o fluxo de interação para excluir um quadro.
     */
    void handleDeleteBoard();
};

#endif