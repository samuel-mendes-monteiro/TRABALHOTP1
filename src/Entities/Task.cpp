#include "../../include/Entities/Task.h"

void Task::setIdentifier(Identifier identifier) {
    this->identifier = identifier;
}

Identifier Task::getIdentifier() const {
    return identifier;
}

void Task::setName(Name name) {
    this->name = name;
}

Name Task::getName() const {
    return name;
}

void Task::setDescription(Text description) {
    this->description = description;
}

Text Task::getDescription() const {
    return description;
}

void Task::setPriority(Priority priority) {
    this->priority = priority;
}

Priority Task::getPriority() const {
    return priority;
}

void Task::setState(State state) {
    this->state = state;
}

State Task::getState() const {
    return state;
}

void Task::setSize(Size size) {
    this->size = size;
}

Size Task::getSize() const {
    return size;
}

void Task::setEntryDate(Timestamp entryDate) {
    this->entryDate = entryDate;
}

Timestamp Task::getEntryDate() const {
    return entryDate;
}

void Task::setStartDate(Timestamp startDate) {
    this->startDate = startDate;
}

Timestamp Task::getStartDate() const {
    return startDate;
}

void Task::setEndDate(Timestamp endDate) {
    this->endDate = endDate;
}

Timestamp Task::getEndDate() const {
    return endDate;
}

void Task::setBoardId(Identifier boardId) {
    this->boardId = boardId;
}
 
Identifier Task::getBoardId() const {
    return boardId;
}

void Task::setDeveloperEmail(Email developerEmail) {
    this->developerEmail = developerEmail;
}

Email Task::getDeveloperEmail() const {
    return developerEmail;
}