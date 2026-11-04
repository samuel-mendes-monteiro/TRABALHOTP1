#include "../../include/Domains/Text.h"
#include <cctype>

bool Text::isPunctuation(char c) const {
    return (c == ',' || c == ';' || c == '.' || c == ':' || c == '?' || c == '!');
}

void Text::validate(std::string value) {
    // Comprimento de 1 a 30 caracteres.
    if (value.empty() || value.length() > 30) {
        throw std::invalid_argument("Tamanho invalido. O texto deve ter de 1 a 30 caracteres.");
    }

    // Primeiro caractere deve ser letra maiuscula.
    if (!std::isupper(static_cast<unsigned char>(value.front()))) {
        throw std::invalid_argument("O texto deve comecar com letra maiuscula.");
    }

    // Ultimo caractere deve ser um ponto.
    if (value.back() != '.') {
        throw std::invalid_argument("O texto deve terminar com ponto.");
    }

    for (size_t i = 0; i < value.length(); ++i) {
        char c = value[i];
        unsigned char uc = static_cast<unsigned char>(c);

        // Caracteres permitidos: letra, digito, espaco ou pontuacao valida.
        bool valid = std::isalpha(uc) || std::isdigit(uc) || c == ' ' || isPunctuation(c);
        if (!valid) {
            throw std::invalid_argument("O texto contem caracteres invalidos.");
        }

        // Sinal de pontuacao nao pode ser seguido por outro sinal de pontuacao.
        if (isPunctuation(c) && i + 1 < value.length() && isPunctuation(value[i + 1])) {
            throw std::invalid_argument("Sinal de pontuacao nao pode ser seguido por outro sinal de pontuacao.");
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
