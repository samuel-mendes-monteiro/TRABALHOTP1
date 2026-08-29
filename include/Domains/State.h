#ifndef STATE_H
#define STATE_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio State (Estado).
 * 
 * Um estado deve corresponder exatamente a um dos três valores permitidos 
 * no método Kanban: A FAZER, FAZENDO ou FEITO.
 */
class State {
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor do estado após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o estado for diferente dos permitidos.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do estado.
     * @return std::string O estado armazenado.
     */
    std::string getValue() const;
};

#endif