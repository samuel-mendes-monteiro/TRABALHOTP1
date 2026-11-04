#include "../../include/Domains/State.h"
#include <stdexcept>

void State::validate(std::string value) {
    if (value != "A FAZER" && value != "FAZENDO" && value != "FEITO") {
        throw std::invalid_argument("Estado invalido. Deve ser A FAZER, FAZENDO ou FEITO.");
    }
}

void State::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string State::getValue() const {
    return value;
}
