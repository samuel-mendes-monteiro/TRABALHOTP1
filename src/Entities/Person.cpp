#include "../../include/Entities/Person.h"

void Person::setEmail(Email email) {
    this->email = email;
}

Email Person::getEmail() const {
    return email;
}

void Person::setNome(Name name) {
    this->name = name;
}

Name Person::getNome() const {
    return name;
}

void Person::setSenha(Password senha) {
    this->password = password;
}

Password Person::getSenha() const {
    return password;
}

void Person::setPapel(Role papel) {
    this->role = role;
}

Role Person::getPapel() const {
    return role;
}