#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

#include "../Interfaces/ITaskService.h"

/**
 * @brief Classe controladora da camada de apresentação para gerenciar interações de Task (Cartão de Atividade).
 * 
 * Responsável por receber dados do usuário via terminal, validar as entradas
 * e acionar os serviços através da interface ITaskService.
 */
class TaskController {
private:
    ITaskService* taskService;

public:
    /**
     * @brief Construtor que recebe a referência para a interface de serviço de tarefas.
     * @param service Ponteiro para uma implementação de ITaskService.
     */
    TaskController(ITaskService* service);

    void handleCreateTask();
    void handleReadTask();
    void handleUpdateTask();
    void handleDeleteTask();
    void handleMoveTask();
    void handleReadMetrics();
};

#endif