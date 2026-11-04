#include "../../include/Domains/Email.h"
#include <cctype>

std::string Email::getValue() const {
    return value;
}

void Email::setValue(std::string value) {
    validate(value);
    this->value = value;
}

void Email::validate(std::string value) {
    // Limite total: 64 (parte local) + 1 (@) + 255 (dominio) = 320 caracteres.
    if (value.length() > 320) {
        throw std::invalid_argument("Tamanho do e-mail invalido.");
    }

    // Deve existir exatamente um '@'.
    size_t atPosition = value.find('@');
    if (atPosition == std::string::npos || value.find('@', atPosition + 1) != std::string::npos) {
        throw std::invalid_argument("Formato de e-mail invalido. Deve conter exatamente um '@'.");
    }

    std::string localPart = value.substr(0, atPosition);       // ex.: samuel.monteiro
    std::string domainPart = value.substr(atPosition + 1);     // ex.: aluno.unb.br

    // ---------- Parte local ----------
    if (localPart.empty() || localPart.length() > 64) {
        throw std::invalid_argument("Tamanho da parte local invalido.");
    }
    if (localPart.front() == '.' || localPart.front() == '-' ||
        localPart.back() == '.' || localPart.back() == '-') {
        throw std::invalid_argument("A parte local nao pode comecar ou terminar com ponto ou hifen.");
    }

    for (size_t i = 0; i < localPart.length(); i++) {
        unsigned char c = static_cast<unsigned char>(localPart[i]);

        bool validChar = std::islower(c) || std::isdigit(c) || c == '.' || c == '-';
        if (!validChar) {
            throw std::invalid_argument("A parte local contem caracteres invalidos.");
        }

        // Ponto ou hifen deve ser seguido por letra ou digito.
        // (o ultimo caractere nunca e ponto/hifen: ja foi verificado acima)
        if ((c == '.' || c == '-') && i + 1 < localPart.length()) {
            char next = localPart[i + 1];
            if (next == '.' || next == '-') {
                throw std::invalid_argument("Ponto ou hifen deve ser seguido por letra ou digito.");
            }
        }
    }

    // ---------- Dominio ----------
    if (domainPart.empty() || domainPart.length() > 255) {
        throw std::invalid_argument("Tamanho do dominio invalido.");
    }

    // O dominio e composto por uma ou mais partes separadas por ponto.
    size_t start = 0;
    while (true) {
        size_t dot = domainPart.find('.', start);
        std::string label = (dot == std::string::npos)
                                ? domainPart.substr(start)
                                : domainPart.substr(start, dot - start);

        if (label.empty()) {
            throw std::invalid_argument("Parte do dominio vazia.");
        }
        if (label.front() == '-' || label.back() == '-') {
            throw std::invalid_argument("Parte do dominio nao pode comecar ou terminar com hifen.");
        }
        for (size_t i = 0; i < label.length(); i++) {
            unsigned char c = static_cast<unsigned char>(label[i]);
            if (!std::islower(c) && !std::isdigit(c) && c != '-') {
                throw std::invalid_argument("Parte do dominio contem caracteres invalidos.");
            }
        }

        if (dot == std::string::npos) break;

        start = dot + 1;
        if (start >= domainPart.length()) {
            throw std::invalid_argument("O dominio nao pode terminar com ponto.");
        }
    }
}
