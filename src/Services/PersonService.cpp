#include "../../include/Services/PersonService.h"
#include <stdexcept>

PersonService::PersonService(PersonContainer& persons, ProjectContainer& projects, TaskContainer& tasks)
    : persons(persons), projects(projects), tasks(tasks) {}

bool PersonService::createPerson(const Person& person) {
    return persons.insert(person);
}

Person PersonService::readPerson(const Email& email) {
    Person out;
    if (!persons.find(email, out)) throw std::invalid_argument("Pessoa nao encontrada.");
    return out;
}

bool PersonService::updatePerson(const Person& person) {
    return persons.update(person);
}

bool PersonService::deletePerson(const Email& email) {
    if (!persons.exists(email)) return false;

    // Bloqueio: pessoa com projetos (gestor) ou cartoes (desenvolvedor) nao pode sair.
    if (!projects.getByManager(email).empty())
        throw std::invalid_argument("Pessoa e gestora de projetos. Exclua os projetos antes.");
    if (!tasks.getByDeveloper(email).empty())
        throw std::invalid_argument("Pessoa possui cartoes de atividade. Exclua os cartoes antes.");

    return persons.remove(email);
}

std::vector<Email> PersonService::listPersons() {
    std::vector<Email> result;
    for (const auto& p : persons.getAll()) result.push_back(p.getEmail());
    return result;
}