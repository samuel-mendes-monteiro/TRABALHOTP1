#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H

#include "../Interfaces/IProjectService.h"
#include "../Interfaces/IPersonService.h"
#include "../Interfaces/IBoardService.h"
#include "../Containers/ProjectContainer.h"

/**
 * @brief Implementa os serviços da entidade Project (módulo Projetos).
 *
 * Armazena os projetos no próprio contêiner. Valida o gestor por meio da interface
 * IPersonService e, ao excluir um projeto, exclui seus quadros por meio da interface
 * IBoardService (que, por sua vez, exclui os cartões de cada quadro).
 */
class ProjectService : public IProjectService {
private:
    ProjectContainer& projects;
    IPersonService* personService;
    IBoardService* boardService;

public:
    /**
     * @brief Construtor.
     * @param projects Contêiner de projetos, de uso exclusivo deste módulo.
     */
    explicit ProjectService(ProjectContainer& projects);

    /**
     * @brief Define o serviço de pessoas usado para validar o gestor do projeto.
     * @param service Ponteiro para a interface IPersonService (deve ser definido antes do uso).
     */
    void setPersonService(IPersonService* service);

    /**
     * @brief Define o serviço de quadros usado na exclusão em cascata.
     * @param service Ponteiro para a interface IBoardService (deve ser definido antes do uso).
     */
    void setBoardService(IBoardService* service);

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
