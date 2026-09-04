#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Password (Senha).
 * 
 * Uma senha consiste exatamente em 5 caracteres, podendo conter letras (a-z, A-Z) 
 * ou dígitos (0-9), devendo obrigatoriamente possuir pelo menos uma letra e um dígito.
 */
class Password {
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor da senha após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o formato da senha for inválido.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor da senha.
     * @return std::string A senha armazenada.
     */
    std::string getValue() const;
};

#endif