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

    void handleCreateTask();
    void handleReadTask();
    void handleUpdateTask();
    void handleDeleteTask();
    void handleListTasks();
    void handleMoveTask();

    /**
     * @brief Exibe uma métrica Kanban.
     * @param metric 1 = tempo de ciclo, 2 = tempo de ciclo médio, 3 = lead time,
     *        4 = lead time médio, 5 = WIP.
     */
    void handleReadMetrics(int metric);
};

#endif