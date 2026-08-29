#ifndef PRIORITY_H
#define PRIORITY_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Priority (Prioridade).
 * 
 * Uma prioridade define o nível de importância de uma atividade e deve 
 * corresponder exatamente a ALTA, MEDIA ou BAIXA.
 */
class Priority {
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor da prioridade após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se a prioridade for diferente das permitidas.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor da prioridade.
     * @return std::string A prioridade armazenada.
     */
    std::string getValue() const;
};

#endif