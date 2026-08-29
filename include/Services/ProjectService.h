#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H

#include "../Interfaces/IProjectService.h"
#include <vector>

/**
 * @brief Classe que implementa os serviços da entidade Project.
 * 
 * Responsável pela lógica de negócio e armazenamento em memória dos projetos.
 */
class ProjectService : public IProjectService {
private:
    std::vector<Project> projects;

public:
    bool createProject(const Project& project) override;
    Project readProject(const Identifier& identifier) override;
    bool updateProject(const Project& project) override;
    bool deleteProject(const Identifier& identifier) override;
};

#endif