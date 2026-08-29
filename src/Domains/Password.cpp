#include "../../include/Domains/Password.h"
#include <cctype>

void Password::validate(std::string value){
    bool hasletter = false;
    bool hasdigit = false;
    bool invalidcharacter = false;

    if (value.length() != 5) {
        throw std::invalid_argument("Invalid length. Password must have exactly 5 characters.");
    }

    for (size_t i = 0; i < value.length(); i++)
    {
        if (std::isalpha(value[i])) hasletter = true;
        else if (std::isdigit(value[i])) hasdigit = true;
        else invalidcharacter = true;
    }
    
    if (!hasletter|| !hasdigit || invalidcharacter)
    {
        throw std::invalid_argument("Invalid password format.");
    }
    


}
void Password::setValue(std::string value){

    validate(value);

    this->value = value;

}
std::string Password::getValue()const{

    return value;
}