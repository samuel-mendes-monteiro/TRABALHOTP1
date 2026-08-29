#ifndef ROLE_H
#define ROLE_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Role (Papel).
 * 
 * Um papel define a função de um membro no projeto e deve corresponder 
 * exatamente a GESTOR ou DESENVOLVEDOR.
 */
class Role {
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor do papel após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o papel for diferente dos permitidos.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do papel.
     * @return std::string O papel armazenado.
     */
    std::string getValue() const;
};

#endif