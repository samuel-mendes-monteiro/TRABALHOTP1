#include "../../include/Entities/Project.h"

void Project::setIdentifier(Identifier identifier) {
    this->identifier = identifier;
}

Identifier Project::getIdentifier() const {
    return identifier;
}

void Project::setName(Name name) {
    this->name = name;
}

Name Project::getName() const {
    return name;
}

void Project::setDescription(Text description) {
    this->description = description;
}

Text Project::getDescription()const {
    return description;
}

void Project::setStart(Timestamp start) {
    this->start = start;
}

Timestamp Project::getStart() const {
    return start;
}

void Project::setEnd(Timestamp end) {
    this->end = end;
}

Timestamp Project::getEnd() const {
    return end;
}