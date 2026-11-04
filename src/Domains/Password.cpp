#include "../../include/Domains/Password.h"
#include <cctype>

void Password::validate(std::string value) {
    if (value.length() != 5) {
        throw std::invalid_argument("Tamanho invalido. A senha deve ter exatamente 5 caracteres.");
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (size_t i = 0; i < value.length(); i++) {
        unsigned char c = static_cast<unsigned char>(value[i]);
        if (std::isalpha(c)) {
            hasLetter = true;
        } else if (std::isdigit(c)) {
            hasDigit = true;
        } else {
            throw std::invalid_argument("Caractere invalido. A senha aceita apenas letras e digitos.");
        }
    }

    if (!hasLetter || !hasDigit) {
        throw std::invalid_argument("A senha deve ter ao menos uma letra e um digito.");
    }
}

void Password::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Password::getValue() const {
    return value;
}
