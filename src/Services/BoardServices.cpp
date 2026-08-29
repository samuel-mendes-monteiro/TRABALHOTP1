#include "../../include/Services/BoardService.h"
#include <stdexcept>
#include <algorithm>

bool BoardService::createBoard(const Board& board) {
    for (const auto& b : boards) {
        if (b.getIdentifier().getValue() == board.getIdentifier().getValue()) {
            return false;
        }
    }
    boards.push_back(board);
    return true;
}

Board BoardService::readBoard(const Identifier& identifier) {
    for (const auto& b : boards) {
        if (b.getIdentifier().getValue() == identifier.getValue()) {
            return b;
        }
    }
    throw std::invalid_argument("Board not found.");
}

bool BoardService::updateBoard(const Board& board) {
    for (auto& b : boards) {
        if (b.getIdentifier().getValue() == board.getIdentifier().getValue()) {
            b = board;
            return true;
        }
    }
    return false;
}

bool BoardService::deleteBoard(const Identifier& identifier) {
    auto it = std::remove_if(boards.begin(), boards.end(), [&](const Board& b) {
        return b.getIdentifier().getValue() == identifier.getValue();
    });

    if (it != boards.end()) {
        boards.erase(it, boards.end());
        return true;
    }
    return false;
}