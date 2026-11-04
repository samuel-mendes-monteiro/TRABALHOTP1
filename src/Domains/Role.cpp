#include "../../include/Domains/Role.h"
#include <stdexcept>

void Role::validate(std::string value) {
    if (value != "GESTOR" && value != "DESENVOLVEDOR") {
        throw std::invalid_argument("Papel invalido. Deve ser GESTOR ou DESENVOLVEDOR.");
    }
}

void Role::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Role::getValue() const {
    return value;
}