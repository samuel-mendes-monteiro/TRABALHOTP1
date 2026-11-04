#include "../../include/Domains/Limit.h"

void Limit::validate(int value) {
    if (value < 1 || value > 25) {
        throw std::invalid_argument("Limite invalido. Deve ser um inteiro entre 1 e 25.");
    }
}

void Limit::setValue(int value) {
    validate(value);
    this->value = value;
}

int Limit::getValue() const {
    return value;
}
