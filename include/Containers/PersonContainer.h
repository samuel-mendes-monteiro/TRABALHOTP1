#ifndef PERSON_CONTAINER_H
#define PERSON_CONTAINER_H

#include <map>
#include <string>
#include <vector>
#include "../Entities/Person.h"

/**
 * @brief Contêiner que armazena objetos Person em memória, indexados por e-mail.
 */
class PersonContainer {
private:
    std::map<std::string, Person> items;

public:
    /** @return false se já existe pessoa com o mesmo e-mail. */
    bool insert(const Person& person) {
        return items.insert({person.getEmail().getValue(), person}).second;
    }

    /** @return true se encontrou; o resultado é copiado para out. */
    bool find(const Email& email, Person& out) const {
        auto it = items.find(email.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    bool exists(const Email& email) const {
        return items.count(email.getValue()) > 0;
    }

    /** @return false se a pessoa não existe. */
    bool update(const Person& person) {
        auto it = items.find(person.getEmail().getValue());
        if (it == items.end()) return false;
        it->second = person;
        return true;
    }

    /** @return false se a pessoa não existe. */
    bool remove(const Email& email) {
        return items.erase(email.getValue()) > 0;
    }

    std::vector<Person> getAll() const {
        std::vector<Person> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }
};

#endif