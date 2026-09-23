#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "../Interfaces/ITaskService.h"
#include <vector>

/**
 * @brief Classe que implementa os serviços da entidade Task (Cartão de Atividade).
 * 
 * Responsável pela lógica de negócio, movimentações e métricas (Cycle Time, Lead Time, WIP).
 */
class TaskService : public ITaskService {
private:
    std::vector<Task> tasks;

public:
    bool createTask(const Task& task) override;
    Task readTask(const Identifier& identifier) override;
    bool updateTask(const Task& task) override;
    bool deleteTask(const Identifier& identifier) override;
    bool moveTask(const Identifier& identifier, const State& newState, const Timestamp& moveTime) override;
};

#endif