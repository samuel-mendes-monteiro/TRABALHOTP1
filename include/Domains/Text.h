#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Texto.
 *
 * Um texto possui até 30 caracteres, iniciando com letra maiúscula, terminando com ponto,
 * contendo letras, dígitos, espaços ou pontuações permitidas, sem pontuações consecutivas.
 */
class Text {
private:
    std::string value;
    void validate(std::string value);
    bool isPunctuation(char c) const;

public:
    /**
     * @brief Define o valor do texto após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o formato do texto for inválido.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do texto.
     * @return std::string O texto armazenado.
     */
    std::string getValue() const;
};

#endif
