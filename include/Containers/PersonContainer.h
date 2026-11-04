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
    /**
     * @brief Insere uma pessoa.
     * @param person Pessoa a ser inserida.
     * @return false se já existe pessoa com o mesmo e-mail.
     */
    bool insert(const Person& person) {
        return items.insert({person.getEmail().getValue(), person}).second;
    }

    /**
     * @brief Busca uma pessoa pelo e-mail.
     * @param email E-mail da pessoa.
     * @param out Recebe uma cópia da pessoa encontrada.
     * @return true se encontrou.
     */
    bool find(const Email& email, Person& out) const {
        auto it = items.find(email.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    /**
     * @brief Verifica se existe uma pessoa com o e-mail informado.
     * @param email E-mail da pessoa.
     * @return true se existe.
     */
    bool exists(const Email& email) const {
        return items.count(email.getValue()) > 0;
    }

    /**
     * @brief Substitui os dados de uma pessoa existente.
     * @param person Pessoa com os novos dados (identificada pelo seu e-mail).
     * @return false se a pessoa não existe.
     */
    bool update(const Person& person) {
        auto it = items.find(person.getEmail().getValue());
        if (it == items.end()) return false;
        it->second = person;
        return true;
    }

    /**
     * @brief Remove uma pessoa.
     * @param email E-mail da pessoa.
     * @return false se a pessoa não existe.
     */
    bool remove(const Email& email) {
        return items.erase(email.getValue()) > 0;
    }

    /**
     * @brief Obtém todas as pessoas armazenadas.
     * @return Cópia das pessoas, ordenadas por e-mail.
     */
    std::vector<Person> getAll() const {
        std::vector<Person> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }
};

#endif
