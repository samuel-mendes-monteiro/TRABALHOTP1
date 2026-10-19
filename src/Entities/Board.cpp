#include "../../include/Entities/Board.h"

void Board::setIdentifier(Identifier identifier) {
    this->identifier = identifier;
}

Identifier Board::getIdentifier() const {
    return identifier;
}

void Board::setName(Name name) {
    this->name = name;
}

Name Board::getName() const {
    return name;
}

void Board::setLimit(Limit limit) {
    this->limit = limit;
}

Limit Board::getLimit() const {
    return limit;
}
void Board::setProjectId(Identifier projectId) {
    this->projectId = projectId;
}

Identifier Board::getProjectId() const {
    return projectId;
}