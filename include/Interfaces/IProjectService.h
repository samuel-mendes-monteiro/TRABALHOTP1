
#ifndef IPROJECT_SERVICE_H
#define IPROJECT_SERVICE_H

#include "../Entities/Project.h"

/**
 * @brief Interface abstrata que define os serviços relacionados à entidade Project (Projeto).
 * 
 * Contém o contrato de métodos virtuais puros para gerenciar projetos no sistema.
 */
class IProjectService {
public:
    virtual ~IProjectService() {}

    virtual bool createProject(const Project& project) = 0;
    virtual Project readProject(const Identifier& identifier) = 0;
    virtual bool updateProject(const Project& project) = 0;
    virtual bool deleteProject(const Identifier& identifier) = 0;
};

#endif