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
    /**
     * @brief Construtor.
     * @param tasks Contêiner de cartões.
     * @param boards Contêiner de quadros (para validar o quadro e o limite WIP).
     * @param persons Contêiner de pessoas (para validar o desenvolvedor).
     */
    TaskService(TaskContainer& tasks, BoardContainer& boards, PersonContainer& persons);

    /** @copydoc ITaskService::createTask */
    bool createTask(const Task& task) override;

    /** @copydoc ITaskService::readTask */
    Task readTask(const Identifier& identifier) override;

    /** @copydoc ITaskService::updateTask */
    bool updateTask(const Task& task) override;

    /** @copydoc ITaskService::deleteTask */
    bool deleteTask(const Identifier& identifier) override;

    /** @copydoc ITaskService::listTasks */
    std::vector<Identifier> listTasks() override;

    /** @copydoc ITaskService::moveTask */
    bool moveTask(const Identifier& identifier, const State& newState, const Timestamp& moveTime) override;

    /** @copydoc ITaskService::readCycleTime */
    long long readCycleTime(const Identifier& taskId) override;

    /** @copydoc ITaskService::readAverageCycleTime */
    long long readAverageCycleTime(const Identifier& boardId) override;

    /** @copydoc ITaskService::readLeadTime */
    long long readLeadTime(const Identifier& taskId) override;

    /** @copydoc ITaskService::readAverageLeadTime */
    long long readAverageLeadTime(const Identifier& boardId) override;

    /** @copydoc ITaskService::readWip */
    int readWip(const Identifier& boardId) override;
};

#endif
