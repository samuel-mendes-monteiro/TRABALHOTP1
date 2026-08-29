#include "../../include/Domains/State.h"
#include <string.h>



void State::validate(std::string value){

    if(value != "A FAZER" && value != "FEITO" && value != "FAZENDO"){
        throw std::invalid_argument("Invalid state. Must be 'A FAZER', 'FAZENDO', or 'FEITO'.");
    }

}

void State::setValue(std::string value){

    validate(value);

}

std::string State::getValue()const{
    return value;
}