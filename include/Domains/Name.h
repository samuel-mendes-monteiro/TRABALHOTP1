#ifndef NAME_H
#define NAME_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Name (Nome).
 * 
 * Um nome consiste em um texto com até 15 caracteres contendo letras maiúsculas, 
 * minúsculas ou espaços em branco. Não pode iniciar ou terminar com espaço, 
 * e espaços em branco devem ser seguidos por letras.
 */
class Name {
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor do nome após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o formato do nome for inválido.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do nome.
     * @return std::string O nome armazenado.
     */
    std::string getValue() const;
};

#endif