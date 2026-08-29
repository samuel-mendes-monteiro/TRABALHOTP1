#include "../../include/Domains/Role.h"
#include <stdexcept>

void Role::validate(std::string value) {
    if (value != "GESTOR" && value != "DESENVOLVEDOR") {
        throw std::invalid_argument("Invalid role. Must be 'GESTOR' or 'DESENVOLVEDOR'.");
    }
}

void Role::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Role::getValue() const {
    return value;
}