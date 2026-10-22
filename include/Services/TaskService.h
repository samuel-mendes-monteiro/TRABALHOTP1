#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "../Interfaces/ITaskService.h"
#include "../Containers/TaskContainer.h"
#include "../Containers/BoardContainer.h"
#include "../Containers/PersonContainer.h"

/**
 * @brief Implementa os serviços de Task: CRUD, movimentação (com limite WIP) e métricas.
 */
class TaskService : public ITaskService {
private:
    TaskContainer& tasks;
    BoardContainer& boards;
    PersonContainer& persons;

public:
    TaskService(TaskContainer& tasks, BoardContainer& boards, PersonContainer& persons);

    bool createTask(const Task& task) override;
    Task readTask(const Identifier& identifier) override;
    bool updateTask(const Task& task) override;
    bool deleteTask(const Identifier& identifier) override;
    std::vector<Identifier> listTasks() override;
    bool moveTask(const Identifier& identifier, const State& newState, const Timestamp& moveTime) override;

    long long readCycleTime(const Identifier& taskId) override;
    long long readAverageCycleTime(const Identifier& boardId) override;
    long long readLeadTime(const Identifier& taskId) override;
    long long readAverageLeadTime(const Identifier& boardId) override;
    int readWip(const Identifier& boardId) override;
};

#endif