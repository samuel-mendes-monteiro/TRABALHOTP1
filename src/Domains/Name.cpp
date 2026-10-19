#include "../../include/Domains/Name.h"
#include <string.h>


void Name::setValue(std::string value){

    validate(value);

    this->value = value;
}

std::string Name::getValue()const{

    return value;
}

void Name::validate(std::string value){

    // deve ter de 1 a 15 caracteres
    if (value.empty() || value.length() > 15)
    {
        throw std::invalid_argument("Numero de caracteres invalido. O nome deve ter entre 1 e 15 caracteres.");
    }

    // primeiro e ultimo caractere nao podem ser espaco em branco
    if (value.front() == ' ' || value.back() == ' ')
    {
        throw std::invalid_argument("O nome nao pode comecar ou terminar com espaco em branco.");
    }

    for (size_t i = 0; i < value.length(); i++)
    {
        char c = value[i];

        // so letras ou espaco
        if (!std::isalpha(static_cast<unsigned char>(c)) && c != ' ')
        {
            throw std::invalid_argument("Caractere invalido no nome.");
        }

        // espaco deve ser seguido por letra
        // (value[i+1] e seguro: o ultimo caractere nunca e espaco)
        if (c == ' ' && !std::isalpha(static_cast<unsigned char>(value[i + 1])))
        {
            throw std::invalid_argument("Espaco em branco deve ser seguido por letra.");
        }
    }
}