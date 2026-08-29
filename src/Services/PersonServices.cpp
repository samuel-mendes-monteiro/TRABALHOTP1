#include "../../include/Services/PersonService.h"
#include <stdexcept>
#include <algorithm>

bool PersonService::createPerson(const Person& person) {
    for (const auto& p : persons) {
        if (p.getEmail().getValue() == person.getEmail().getValue()) {
            return false; // Já cadastrado
        }
    }
    persons.push_back(person);
    return true;
}

Person PersonService::readPerson(const Email& email) {
    for (const auto& p : persons) {
        if (p.getEmail().getValue() == email.getValue()) {
            return p;
        }
    }
    throw std::invalid_argument("Person not found.");
}

bool PersonService::updatePerson(const Person& person) {
    for (auto& p : persons) {
        if (p.getEmail().getValue() == person.getEmail().getValue()) {
            p = person;
            return true;
        }
    }
    return false;
}

bool PersonService::deletePerson(const Email& email) {
    auto it = std::remove_if(persons.begin(), persons.end(), [&](const Person& p) {
        return p.getEmail().getValue() == email.getValue();
    });

    if (it != persons.end()) {
        persons.erase(it, persons.end());
        return true;
    }
    return false;
}