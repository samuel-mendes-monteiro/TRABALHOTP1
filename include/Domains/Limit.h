#ifndef LIMIT_H
#define LIMIT_H

#include <stdexcept>

/**
 * @brief Classe que representa o domínio Limit (Limite).
 * 
 * O limite designa o número máximo de atividades simultâneas na coluna FAZENDO 
 * e deve ser um valor inteiro entre 1 e 25.
 */
class Limit {
private:
    int value;
    void validate(int value);

public:
    /**
     * @brief Define o valor do limite após validação.
     * @param value O inteiro a ser validado e definido.
     * @throw std::invalid_argument se o valor estiver fora do intervalo de 1 a 25.
     */
    void setValue(int value);

    /**
     * @brief Obtém o valor do limite.
     * @return int O limite armazenado.
     */
    int getValue() const;
};

#endif