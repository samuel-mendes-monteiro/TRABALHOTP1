#ifndef IBOARD_SERVICE_H
#define IBOARD_SERVICE_H

#include <vector>
#include "../Entities/Board.h"

/**
 * @brief Interface abstrata que define os serviços relacionados à entidade Board (Quadro).
 *
 * Contém o contrato de métodos virtuais puros para gerenciar quadros Kanban no sistema.
 */
class IBoardService {
public:
    virtual ~IBoardService() {}

    /**
     * @brief Serviço 11: cria um quadro.
     * @param board Quadro a ser criado.
     * @return true se foi criado, false se já existe quadro com o mesmo identificador.
     * @throw std::invalid_argument se o projeto do quadro não existe.
     */
    virtual bool createBoard(const Board& board) = 0;

    /**
     * @brief Serviço 12: lê os dados de um quadro.
     * @param identifier Identificador do quadro.
     * @return Board O quadro encontrado.
     * @throw std::invalid_argument se o quadro não existe.
     */
    virtual Board readBoard(const Identifier& identifier) = 0;

    /**
     * @brief Serviço 13: atualiza nome e limite de um quadro.
     *
     * O identificador do quadro e o projeto ao qual ele pertence não são alterados.
     *
     * @param board Quadro com os novos dados, identificado pelo seu identificador.
     * @return true se foi atualizado, false se o quadro não existe.
     * @throw std::invalid_argument se o novo limite for menor que o WIP atual do quadro.
     */
    virtual bool updateBoard(const Board& board) = 0;

    /**
     * @brief Serviço 14: exclui um quadro e todos os seus cartões.
     * @param identifier Identificador do quadro.
     * @return true se foi excluído, false se o quadro não existe.
     */
    virtual bool deleteBoard(const Identifier& identifier) = 0;

    /**
     * @brief Serviço 15: lista os identificadores de todos os quadros.
     * @return Lista de identificadores.
     */
    virtual std::vector<Identifier> listBoards() = 0;
};

#endif
