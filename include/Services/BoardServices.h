#ifndef BOARD_SERVICE_H
#define BOARD_SERVICE_H

#include "../Interfaces/IBoardService.h"
#include <vector>

/**
 * @brief Classe que implementa os serviços da entidade Board.
 * 
 * Responsável pela lógica de negócio e armazenamento em memória dos quadros Kanban.
 */
class BoardService : public IBoardService {
private:
    std::vector<Board> boards;

public:
    bool createBoard(const Board& board) override;
    Board readBoard(const Identifier& identifier) override;
    bool updateBoard(const Board& board) override;
    bool deleteBoard(const Identifier& identifier) override;
};

#endif