#include "../../include/Domains/Identifier.h"
#include <cctype>

void Identifier::validate(std::string value) {
    // O identificador tem exatamente 6 caracteres.
    if (value.length() != 6) {
        throw std::invalid_argument("Tamanho invalido. O identificador deve ter 6 caracteres.");
    }

    // Os 3 primeiros caracteres sao letras.
    for (int i = 0; i < 3; ++i) {
        if (!std::isalpha(static_cast<unsigned char>(value[i]))) {
            throw std::invalid_argument("Formato invalido. Os 3 primeiros caracteres devem ser letras.");
        }
    }

    // Os 3 ultimos caracteres sao digitos.
    for (int i = 3; i < 6; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(value[i]))) {
            throw std::invalid_argument("Formato invalido. Os 3 ultimos caracteres devem ser digitos.");
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
