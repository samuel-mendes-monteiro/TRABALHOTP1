#ifndef IBOARD_SERVICE_H
#define IBOARD_SERVICE_H

#include "../Entities/Board.h"

/**
 * @brief Interface abstrata que define os serviços relacionados à entidade Board (Quadro).
 * 
 * Contém o contrato de métodos virtuais puros para gerenciar quadros Kanban no sistema.
 */
class IBoardService {
public:
    virtual ~IBoardService() {}

    virtual bool createBoard(const Board& board) = 0;
    virtual Board readBoard(const Identifier& identifier) = 0;
    virtual bool updateBoard(const Board& board) = 0;
    virtual bool deleteBoard(const Identifier& identifier) = 0;
};

#endif