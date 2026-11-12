#include "../../include/Services/PersonService.h"
#include <stdexcept>

PersonService::PersonService(PersonContainer& persons)
    : persons(persons), projectService(nullptr), taskService(nullptr) {}

void PersonService::setProjectService(IProjectService* service) {
    projectService = service;
}

void PersonService::setTaskService(ITaskService* service) {
    taskService = service;
}

// Vinculo de gestor: consulta o modulo Projetos pela interface IProjectService.
bool PersonService::managesProjects(const Email& email) {
    if (!projectService) throw std::logic_error("Servico de projetos nao configurado.");
    for (const auto& id : projectService->listProjects())
        if (projectService->readProject(id).getManagerEmail().getValue() == email.getValue())
            return true;
    return false;
}

// Vinculo de desenvolvedor: consulta o modulo Cartoes pela interface ITaskService.
bool PersonService::hasTasks(const Email& email) {
    if (!taskService) throw std::logic_error("Servico de cartoes nao configurado.");
    for (const auto& id : taskService->listTasks())
        if (taskService->readTask(id).getDeveloperEmail().getValue() == email.getValue())
            return true;
    return false;
}

bool PersonService::createPerson(const Person& person) {
    return persons.insert(person);
}

Person PersonService::readPerson(const Email& email) {
    Person out;
    if (!persons.find(email, out)) throw std::invalid_argument("Pessoa nao encontrada.");
    return out;
}

bool PersonService::updatePerson(const Person& person) {
    Person existing;
    if (!persons.find(person.getEmail(), existing)) return false;

    // Trocar o papel de quem ja tem vinculos deixaria projetos/cartoes inconsistentes.
    if (existing.getRole().getValue() != person.getRole().getValue()) {
        if (managesProjects(person.getEmail()))
            throw std::invalid_argument("Pessoa e gestora de projetos. Nao e possivel trocar o papel.");
        if (hasTasks(person.getEmail()))
            throw std::invalid_argument("Pessoa possui cartoes de atividade. Nao e possivel trocar o papel.");
    }

    return persons.update(person);
}

bool PersonService::deletePerson(const Email& email) {
    if (!persons.exists(email)) return false;

    // Bloqueio: pessoa com projetos (gestor) ou cartoes (desenvolvedor) nao pode sair.
    if (managesProjects(email))
        throw std::invalid_argument("Pessoa e gestora de projetos. Exclua os projetos antes.");
    if (hasTasks(email))
        throw std::invalid_argument("Pessoa possui cartoes de atividade. Exclua os cartoes antes.");

    return persons.remove(email);
}

std::vector<Email> PersonService::listPersons() {
    std::vector<Email> result;
    for (const auto& p : persons.getAll()) result.push_back(p.getEmail());
    return result;
}
