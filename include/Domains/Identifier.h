#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Identificador.
 * 
 * Um identificador consiste em 6 caracteres: os 3 primeiros são letras (a-z, A-Z) 
 * e os 3 últimos são dígitos (0-9).
 */
class Identifier {
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor do identificador após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o formato for inválido.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do identificador.
     * @return std::string O identificador armazenado.
     */
    std::string getValue() const;
};

#endif