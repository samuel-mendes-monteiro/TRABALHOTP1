#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H

#include "../Interfaces/IProjectService.h"
#include "Session.h"

/**
 * @brief Classe controladora da camada de apresentação para gerenciar interações de Project.
 *
 * Responsável por receber dados do usuário via interface de texto, validar as entradas,
 * verificar permissões pelo papel da sessão e acionar os serviços correspondentes
 * através da interface IProjectService.
 */
class ProjectController {
private:
    IProjectService* projectService;
    Session& session;

public:
    /**
     * @brief Construtor.
     * @param service Ponteiro para uma implementação de IProjectService.
     * @param session Sessão do usuário autenticado.
     */
    ProjectController(IProjectService* service, Session& session);

    /**
     * @brief Executa o fluxo de interação para criar um novo projeto (restrito ao GESTOR).
     *
     * O usuário autenticado passa a ser o gestor do projeto.
     */
    void handleCreateProject();

    /**
     * @brief Lista os identificadores de todos os projetos.
     */
    void handleListProjects();

    /**
     * @brief Executa o fluxo de interação para ler/consultar os dados de um projeto.
     */
    void handleReadProject();

    /**
     * @brief Executa o fluxo de interação para atualizar os dados de um projeto.
     *
     * Restrito ao gestor que criou o projeto.
     */
    void handleUpdateProject();

    /**
     * @brief Executa o fluxo de interação para excluir um projeto.
     *
     * Restrito ao gestor que criou o projeto.
     */
    void handleDeleteProject();
};

#endif
