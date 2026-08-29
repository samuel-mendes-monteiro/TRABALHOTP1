#ifndef SIZE_H
#define SIZE_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Tamanho.
 * 
 * Um tamanho deve corresponder exatamente a um dos três valores permitidos:
 * GRANDE, MEDIO ou PEQUENO.
 */
class Size{
private:
    std::string value;
    void validate(std::string value);

public:
    /**
     * @brief Define o valor do tamanho após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o tamanho for diferente dos permitidos.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do tamanho.
     * @return std::string O tamanho armazenado.
     */
    std::string getValue() const;
};

#endif