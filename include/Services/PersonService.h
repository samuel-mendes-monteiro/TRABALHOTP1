#ifndef PERSON_SERVICE_H
#define PERSON_SERVICE_H

#include "../Interfaces/IPersonService.h"
#include "../Containers/PersonContainer.h"
#include "../Containers/ProjectContainer.h"
#include "../Containers/TaskContainer.h"

/**
 * @brief Implementa os serviços da entidade Person usando contêineres compartilhados.
 *
 * Uma pessoa que é gestora de projetos ou responsável por cartões não pode ser excluída
 * nem trocar de papel.
 */
class PersonService : public IPersonService {
private:
    PersonContainer& persons;
    ProjectContainer& projects;
    TaskContainer& tasks;

public:
    /**
     * @brief Construtor.
     * @param persons Contêiner de pessoas.
     * @param projects Contêiner de projetos (para verificar vínculos de gestor).
     * @param tasks Contêiner de cartões (para verificar vínculos de desenvolvedor).
     */
    PersonService(PersonContainer& persons, ProjectContainer& projects, TaskContainer& tasks);

    /** @copydoc IPersonService::createPerson */
    bool createPerson(const Person& person) override;

    /** @copydoc IPersonService::readPerson */
    Person readPerson(const Email& email) override;

    /** @copydoc IPersonService::updatePerson */
    bool updatePerson(const Person& person) override;

    /** @copydoc IPersonService::deletePerson */
    bool deletePerson(const Email& email) override;

    /** @copydoc IPersonService::listPersons */
    std::vector<Email> listPersons() override;
};

#endif
