#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <string>
#include <stdexcept>

/**
 * @brief Classe que representa o domínio Timestamp.
 * 
 * Um timestamp consiste em uma string no formato DIA-MÊS-ANO-HORÁRIO, 
 * validando limites de dias, meses, anos (incluindo bissextos) e horários.
 */
class Timestamp {
private:
    std::string value;
    void validate(std::string value);
    bool isLeapYear(int year);// bisexto
    int getDaysInMonth(int month, int year);

public:
    /**
     * @brief Define o valor do timestamp após validação.
     * @param value A string a ser validada e definida.
     * @throw std::invalid_argument se o formato ou a data/hora forem inválidos.
     */
    void setValue(std::string value);

    /**
     * @brief Obtém o valor do timestamp.
     * @return std::string O timestamp armazenado.
     */
    std::string getValue() const;
};

#endif