#include "../../include/Domains/Identifier.h"
#include <cctype>

void Identifier::validate(std::string value) {

    // Verifica se a string tem 6 caracteres
    if (value.length() != 6) {
        throw std::invalid_argument("Invalid length. Must be 6 characters.");
    }

    // Verifica se os 3 primeiros caracteres são letras
    for (int i = 0; i < 3; ++i) {
        if (!std::isalpha(value[i])) {
            throw std::invalid_argument("Invalid format. First 3 characters must be letters.");
        }
    }
    
    // Verifica se os 3 últimos caracteres são dígitos
    for (int i = 3; i < 6; ++i) {
        if (!std::isdigit(value[i])) {
            throw std::invalid_argument("Invalid format. Last 3 characters must be digits.");
        }
    }
}

void Identifier::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Identifier::getValue() const {
    return value;
}