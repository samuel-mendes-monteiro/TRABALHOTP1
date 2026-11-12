#ifndef EMAIL_H
#define EMAIL_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Email.
 * 
 * Um email consiste em parte-local\@domínio. A parte local e o domínio possuem 
 * regras estritas de caracteres e comprimento máximo de acordo com a especificação.
 */
class Email {
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor do email após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o formato do email for inválido.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do email.
     * @return std::string O email armazenado.
     */
    std::string getValue() const;
};

#endif