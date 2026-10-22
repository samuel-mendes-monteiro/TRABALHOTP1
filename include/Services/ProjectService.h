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
    ProjectService(ProjectContainer& projects, PersonContainer& persons,
                   BoardContainer& boards, TaskContainer& tasks);

    bool createProject(const Project& project) override;
    Project readProject(const Identifier& identifier) override;
    bool updateProject(const Project& project) override;
    bool deleteProject(const Identifier& identifier) override;
    std::vector<Identifier> listProjects() override;
};

#endif