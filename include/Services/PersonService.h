#ifndef PERSON_SERVICE_H
#define PERSON_SERVICE_H

#include "../Interfaces/IPersonService.h"
#include "../Interfaces/IProjectService.h"
#include "../Interfaces/ITaskService.h"
#include "../Containers/PersonContainer.h"

/**
 * @brief Implementa os serviços da entidade Person (módulo Pessoas).
 *
 * Armazena as pessoas no próprio contêiner. Para saber se uma pessoa tem vínculos,
 * consulta os módulos Projetos e Cartões de Atividades apenas por meio das interfaces
 * IProjectService e ITaskService.
 *
 * Uma pessoa que é gestora de projetos ou responsável por cartões não pode ser excluída
 * nem trocar de papel.
 */
class PersonService : public IPersonService {
private:
    PersonContainer& persons;
    IProjectService* projectService;
    ITaskService* taskService;

    bool managesProjects(const Email& email);
    bool hasTasks(const Email& email);

public:
    /**
     * @brief Construtor.
     * @param persons Contêiner de pessoas, de uso exclusivo deste módulo.
     */
    explicit PersonService(PersonContainer& persons);

    /**
     * @brief Define o serviço de projetos usado para verificar se a pessoa é gestora de algum projeto.
     * @param service Ponteiro para a interface IProjectService (deve ser definido antes do uso).
     */
    void setProjectService(IProjectService* service);

    /**
     * @brief Define o serviço de cartões usado para verificar se a pessoa é responsável por algum cartão.
     * @param service Ponteiro para a interface ITaskService (deve ser definido antes do uso).
     */
    void setTaskService(ITaskService* service);

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
