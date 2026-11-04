#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H

#include "../Interfaces/IProjectService.h"
#include "../Containers/PersonContainer.h"
#include "../Containers/ProjectContainer.h"
#include "../Containers/BoardContainer.h"
#include "../Containers/TaskContainer.h"

/**
 * @brief Implementa os serviços da entidade Project. Excluir um projeto exclui seus quadros e cartões.
 */
class ProjectService : public IProjectService {
private:
    ProjectContainer& projects;
    PersonContainer& persons;
    BoardContainer& boards;
    TaskContainer& tasks;

public:
    /**
     * @brief Construtor.
     * @param projects Contêiner de projetos.
     * @param persons Contêiner de pessoas (para validar o gestor).
     * @param boards Contêiner de quadros (para a exclusão em cascata).
     * @param tasks Contêiner de cartões (para a exclusão em cascata).
     */
    ProjectService(ProjectContainer& projects, PersonContainer& persons,
                   BoardContainer& boards, TaskContainer& tasks);

    /** @copydoc IProjectService::createProject */
    bool createProject(const Project& project) override;

    /** @copydoc IProjectService::readProject */
    Project readProject(const Identifier& identifier) override;

    /** @copydoc IProjectService::updateProject */
    bool updateProject(const Project& project) override;

    /** @copydoc IProjectService::deleteProject */
    bool deleteProject(const Identifier& identifier) override;

    /** @copydoc IProjectService::listProjects */
    std::vector<Identifier> listProjects() override;
};

#endif
