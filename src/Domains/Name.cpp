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
        throw std::invalid_argument("Numero de caracteres invalida. O nome deve ter entre 1 a 15 caracteres.");
    }

    // primeiro e ultimo caracter nao pode ser um espaço em branco
    if (value.front() == ' '||value.back() == ' ')
    {
        throw std::invalid_argument("O nome não pode começar ou terminar com um espaço em branco");
    }
    
    for (size_t i = 0; i < value.length(); i++)
    {
        char c = value[i];
        if (!isalpha(c) && c != ' ')
        {
            throw std::invalid_argument("Caracter invalido no nome");
        
        // impede espacos duplos, imediatamente apos um espaco deve ser uma letra
            if (c == ' ' && !isalpha(value[i+1]))
            {

            throw std::invalid_argument("Não pode existir dois espaços seguidos no nome");
            }
        }
    }
}