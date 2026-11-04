#ifndef BOARD_CONTAINER_H
#define BOARD_CONTAINER_H

#include <map>
#include <string>
#include <vector>
#include "../Entities/Board.h"

/**
 * @brief Contêiner que armazena objetos Board em memória, indexados por identificador.
 */
class BoardContainer {
private:
    std::map<std::string, Board> items;

public:
    /**
     * @brief Insere um quadro.
     * @param board Quadro a ser inserido.
     * @return false se já existe quadro com o mesmo identificador.
     */
    bool insert(const Board& board) {
        return items.insert({board.getIdentifier().getValue(), board}).second;
    }

    /**
     * @brief Busca um quadro pelo identificador.
     * @param id Identificador do quadro.
     * @param out Recebe uma cópia do quadro encontrado.
     * @return true se encontrou.
     */
    bool find(const Identifier& id, Board& out) const {
        auto it = items.find(id.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    /**
     * @brief Verifica se existe um quadro com o identificador informado.
     * @param id Identificador do quadro.
     * @return true se existe.
     */
    bool exists(const Identifier& id) const {
        return items.count(id.getValue()) > 0;
    }

    /**
     * @brief Substitui os dados de um quadro existente.
     * @param board Quadro com os novos dados (identificado pelo seu identificador).
     * @return false se o quadro não existe.
     */
    bool update(const Board& board) {
        auto it = items.find(board.getIdentifier().getValue());
        if (it == items.end()) return false;
        it->second = board;
        return true;
    }

    /**
     * @brief Remove um quadro.
     * @param id Identificador do quadro.
     * @return false se o quadro não existe.
     */
    bool remove(const Identifier& id) {
        return items.erase(id.getValue()) > 0;
    }

    /**
     * @brief Obtém todos os quadros armazenados.
     * @return Cópia dos quadros, ordenados por identificador.
     */
    std::vector<Board> getAll() const {
        std::vector<Board> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }

    /**
     * @brief Obtém os quadros pertencentes a um projeto.
     * @param projectId Identificador do projeto.
     * @return Cópia dos quadros do projeto.
     */
    std::vector<Board> getByProject(const Identifier& projectId) const {
        std::vector<Board> result;
        for (const auto& pair : items)
            if (pair.second.getProjectId().getValue() == projectId.getValue())
                result.push_back(pair.second);
        return result;
    }
};

#endif
