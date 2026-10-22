#ifndef PERSON_SERVICE_H
#define PERSON_SERVICE_H

#include "../Interfaces/IPersonService.h"
#include "../Containers/PersonContainer.h"
#include "../Containers/ProjectContainer.h"
#include "../Containers/TaskContainer.h"

/**
 * @brief Implementa os serviços da entidade Person usando contêineres compartilhados.
 */
class PersonService : public IPersonService {
private:
    PersonContainer& persons;
    ProjectContainer& projects;
    TaskContainer& tasks;

public:
    PersonService(PersonContainer& persons, ProjectContainer& projects, TaskContainer& tasks);

    bool createPerson(const Person& person) override;
    Person readPerson(const Email& email) override;
    bool updatePerson(const Person& person) override;
    bool deletePerson(const Email& email) override;
    std::vector<Email> listPersons() override;
};

#endif