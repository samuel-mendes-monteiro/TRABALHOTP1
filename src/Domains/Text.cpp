#include "../../include/Domains/Text.h"
#include <cctype>

bool Text::isPunctuation(char c) {
    return (c == ',' || c == ';' || c == '.' || c == ':' || c == '?' || c == '!');
}

void Text::validate(std::string value) {
    // Comprimento de 1 a 30 caracteres
    if (value.empty() || value.length() > 30) {
        throw std::invalid_argument("Invalid length. Text must be between 1 and 30 characters.");
    }

    // Primeiro caractere deve ser letra maiúscula
    if (!std::isupper(value.front())) {
        throw std::invalid_argument("Text must start with an uppercase letter.");
    }

    // Último caractere deve ser um ponto
    if (value.back() != '.') {
        throw std::invalid_argument("Text must end with a period (dot).");
    }

    for (size_t i = 0; i < value.length(); ++i) {
        char c = value[i];

        // Verifica caracteres permitidos: letra, dígito, espaço ou pontuação válida
        bool isValid = std::isalpha(c) || std::isdigit(c) || c == ' ' || isPunctuation(c);
        if (!isValid) {
            throw std::invalid_argument("Text contains invalid characters.");
        }

        // Sinal de pontuação não pode ser seguido por outro sinal de pontuação
        if (isPunctuation(c)) {
            if (i + 1 < value.length() && isPunctuation(value[i + 1])) {
                throw std::invalid_argument("Punctuation cannot be followed by another punctuation.");
            }
        }
    }
}

void Text::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Text::getValue() const {
    return value;
}