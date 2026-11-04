#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

#include "../Interfaces/ITaskService.h"
#include "Session.h"

/**
 * @brief Controladora da camada de apresentação para Task (Cartão de Atividade).
 *
 * Recebe dados do usuário via terminal, valida as entradas, verifica permissões
 * pelo papel da sessão e aciona os serviços através de ITaskService.
 */
class TaskController {
private:
    ITaskService* taskService;
    Session& session;

public:
    /**
     * @brief Construtor.
     * @param service Ponteiro para uma implementação de ITaskService.
     * @param session Sessão do usuário autenticado.
     */
    TaskController(ITaskService* service, Session& session);

    /**
     * @brief Executa o fluxo de interação para criar um cartão (restrito ao GESTOR).
     *
     * Todo cartão novo nasce na coluna A FAZER.
     */
    void handleCreateTask();

    /**
     * @brief Executa o fluxo de interação para consultar os dados de um cartão.
     */
    void handleReadTask();

    /**
     * @brief Executa o fluxo de interação para atualizar nome, descrição, prioridade
     *        e tamanho de um cartão (restrito ao GESTOR).
     *
     * Estado e datas só mudam por handleMoveTask.
     */
    void handleUpdateTask();

    /**
     * @brief Executa o fluxo de interação para excluir um cartão (restrito ao GESTOR).
     */
    void handleDeleteTask();

    /**
     * @brief Lista os identificadores de todos os cartões.
     */
    void handleListTasks();

    /**
     * @brief Executa o fluxo de interação para mover um cartão entre colunas
     *        (A FAZER -> FAZENDO ou FAZENDO -> FEITO).
     */
    void handleMoveTask();

    /**
     * @brief Exibe uma métrica Kanban.
     * @param metric 1 = tempo de ciclo, 2 = tempo de ciclo médio, 3 = lead time,
     *        4 = lead time médio, 5 = WIP.
     */
    void handleReadMetrics(int metric);
};

#endif
