#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H

#include "../Interfaces/IProjectService.h"

/**
 * @brief Classe controladora da camada de apresentação para gerenciar interações de Project.
 * 
 * Responsável por receber dados do usuário via interface de texto, validar as entradas
 * e acionar os serviços correspondentes através da interface IProjectService.
 */
class ProjectController {
private:
    IProjectService* projectService;

public:
    /**
     * @brief Construtor que recebe a referência para a interface de serviço de projetos.
     * @param service Ponteiro para uma implementação de IProjectService.
     */
    ProjectController(IProjectService* service);

    /**
     * @brief Executa o fluxo de interação para criar um novo projeto.
     */
    void handleCreateProject();

    /**
     * @brief Executa o fluxo de interação para ler/consultar os dados de um projeto.
     */
    void handleReadProject();

    /**
     * @brief Executa o fluxo de interação para atualizar os dados de um projeto.
     */
    void handleUpdateProject();

    /**
     * @brief Executa o fluxo de interação para excluir um projeto.
     */
    void handleDeleteProject();
};

#endif