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
    bool insert(const Board& board) {
        return items.insert({board.getIdentifier().getValue(), board}).second;
    }

    bool find(const Identifier& id, Board& out) const {
        auto it = items.find(id.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    bool exists(const Identifier& id) const {
        return items.count(id.getValue()) > 0;
    }

    bool update(const Board& board) {
        auto it = items.find(board.getIdentifier().getValue());
        if (it == items.end()) return false;
        it->second = board;
        return true;
    }

    bool remove(const Identifier& id) {
        return items.erase(id.getValue()) > 0;
    }

    std::vector<Board> getAll() const {
        std::vector<Board> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }

    /** Quadros pertencentes ao projeto informado. */
    std::vector<Board> getByProject(const Identifier& projectId) const {
        std::vector<Board> result;
        for (const auto& pair : items)
            if (pair.second.getProjectId().getValue() == projectId.getValue())
                result.push_back(pair.second);
        return result;
    }
};

#endif