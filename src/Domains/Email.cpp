#include "../../include/Domains/Email.h"

std::string Email::getValue()const{ 
    return value;
}

void Email::setValue(std::string value){

    validate(value);

    this->value = value;
    
}

void Email::validate(std::string value){

    if(value.length() > 320 ){
        throw std::invalid_argument("Invalid email lenght.");
    }


    // Encontra a posição do '@' e garante que apenas um @ esteja no email

    size_t atPosition = value.find('@'); // size_t usado paa guardar posicao dentro da string
    if (atPosition == std::string::npos || value.find('@', atPosition + 1) != std::string::npos) { //std::string::npos significa que nao foi achado
        throw std::invalid_argument("Invalid email format. Must contain exactly one '@'.");
    }

    // separar email em parte local e dominio

    std::string localPart = value.substr(0, atPosition); /// ex: samuel.monteiro
    std::string domainPart = value.substr(atPosition + 1);  //// @aluno.unb.br

    // Validação parte local do email

    if (localPart.empty() || localPart.length() > 64)
    {
        throw std::invalid_argument("Invalid local part lenght.");

    }
    if (localPart.front() == '.' || localPart.front() == '-' || localPart.back() == '.' || localPart.back() == '-') {
        throw std::invalid_argument("Local part cannot start or end with dot or hyphen.");
    }

    for (size_t i = 0; i < localPart.length(); i++)
    {
        char c = localPart[i];
        bool isValidChar = std::islower(c) || std::isdigit(c) || c == '.' || c == '-';
        if (!isValidChar)
        {
            throw std::invalid_argument("Local part contains invalid characters.");
        }
    //ponto ou hífen deve ser seguido por letra ou digito
        if ((c == '.' || c == '.') && (i + 1 < localPart.length()))
        {
            char nextC = localPart[i+1];
            if (nextC == '.' || nextC == '-')
            {
                throw std::invalid_argument("Dot or hyphen cannot be followed by another dot or hyphen.");
            }
        }
    }

    //validação do dominio


    if(domainPart.empty() || domainPart.length() > 255){

        throw std::invalid_argument("Invalid domain part lenght.");
    }
    // O dominio tem partes separadas por .
    size_t domAt = 0;
    bool hasPart = false;

    while( domAt < domainPart.length())
    {

        size_t nextDot = domainPart.find('.', domAt);
        std::string subDomain;

        if(nextDot == std::string::npos){
            subDomain = domainPart.substr(domAt);
        }else
        {
            subDomain = domainPart.substr(domAt,nextDot - domAt);
        }
        if (subDomain.empty() || subDomain.length() > 63) {
            throw std::invalid_argument("Invalid subdomain length.");
        }
        if (subDomain.front() == '-' || subDomain.back() == '-') {
            throw std::invalid_argument("Subdomain cannot start or end with a hyphen.");
        }
        for (char c : subDomain) {
            if (!std::islower(c) && !std::isdigit(c) && c != '-') {
                throw std::invalid_argument("Subdomain contains invalid characters.");
            }
        }

        hasPart = true;

        if(nextDot == std::string::npos) break;
        domAt = nextDot +1;

        if(domAt >= domainPart.length()){
            throw std::invalid_argument("Domain cannot end with a dot.");
        }

        if(!hasPart) throw std::invalid_argument("Invalid domain structure.");

        }

}