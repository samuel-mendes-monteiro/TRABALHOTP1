#ifndef IPROJECT_SERVICE_H
#define IPROJECT_SERVICE_H

#include <vector>
#include "../Entities/Project.h"

/**
 * @brief Interface abstrata que define os serviços relacionados à entidade Project (Projeto).
 *
 * Contém o contrato de métodos virtuais puros para gerenciar projetos no sistema.
 */
class IProjectService {
public:
    virtual ~IProjectService() {}

    /**
     * @brief Serviço 6: cria um projeto.
     * @param project Projeto a ser criado; o e-mail do gestor deve estar preenchido.
     * @return true se foi criado, false se já existe projeto com o mesmo identificador.
     * @throw std::invalid_argument se o gestor não existe, se ele não tem o papel GESTOR
     *        ou se a data de término é anterior à de início.
     */
    virtual bool createProject(const Project& project) = 0;

    /**
     * @brief Serviço 7: lê os dados de um projeto.
     * @param identifier Identificador do projeto.
     * @return Project O projeto encontrado.
     * @throw std::invalid_argument se o projeto não existe.
     */
    virtual Project readProject(const Identifier& identifier) = 0;

    /**
     * @brief Serviço 8: atualiza nome, descrição e datas de um projeto.
     *
     * O identificador e o gestor do projeto não são alterados.
     *
     * @param project Projeto com os novos dados, identificado pelo seu identificador.
     * @return true se foi atualizado, false se o projeto não existe.
     * @throw std::invalid_argument se a data de término é anterior à de início.
     */
    virtual bool updateProject(const Project& project) = 0;

    /**
     * @brief Serviço 9: exclui um projeto, seus quadros e os cartões desses quadros.
     * @param identifier Identificador do projeto.
     * @return true se foi excluído, false se o projeto não existe.
     */
    virtual bool deleteProject(const Identifier& identifier) = 0;

    /**
     * @brief Serviço 10: lista os identificadores de todos os projetos.
     * @return Lista de identificadores.
     */
    virtual std::vector<Identifier> listProjects() = 0;
};

#endif
