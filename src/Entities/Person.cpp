#include "../../include/Entities/Person.h"

void Person::setEmail(Email email) {
    this->email = email;
}

Email Person::getEmail() const {
    return email;
}

void Person::setName(Name name) {
    this->name = name;
}

Name Person::getName() const {
    return name;
}

void Person::setPassword(Password senha) {
    this->password = password;
}

Password Person::getPassword() const {
    return password;
}

void Person::setRole(Role papel) {
    this->role = role;
}

Role Person::getRole() const {
    return role;
}