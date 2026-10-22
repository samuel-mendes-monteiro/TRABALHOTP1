#include "../../include/Services/AuthenticationService.h"

AuthenticationService::AuthenticationService(PersonContainer& persons) : persons(persons) {}

bool AuthenticationService::authenticate(const Email& email, const Password& password, Role& role) {
    Person person;
    if (!persons.find(email, person)) return false;
    if (person.getPassword().getValue() != password.getValue()) return false;
    role = person.getRole();
    return true;
}