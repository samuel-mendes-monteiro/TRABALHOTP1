#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "../Interfaces/ITaskService.h"
#include "../Interfaces/IBoardService.h"
#include "../Interfaces/IPersonService.h"
#include "../Containers/TaskContainer.h"

/**
 * @brief Implementa os serviços de Task (módulo Cartões de Atividades): CRUD,
 * movimentação (com limite WIP) e métricas.
 *
 * Armazena os cartões no próprio contêiner. Valida o quadro e o limite WIP por meio da
 * interface IBoardService e valida o desenvolvedor responsável por meio da interface
 * IPersonService.
 */
class TaskService : public ITaskService {
private:
    TaskContainer& tasks;
    IBoardService* boardService;
    IPersonService* personService;

    Board findBoard(const Identifier& boardId, const char* notFoundMessage);

public:
    /**
     * @brief Construtor.
     * @param tasks Contêiner de cartões, de uso exclusivo deste módulo.
     */
    explicit TaskService(TaskContainer& tasks);

    /**
     * @brief Define o serviço de quadros usado para validar o quadro e o limite WIP.
     * @param service Ponteiro para a interface IBoardService (deve ser definido antes do uso).
     */
    void setBoardService(IBoardService* service);

    /**
     * @brief Define o serviço de pessoas usado para validar o desenvolvedor responsável.
     * @param service Ponteiro para a interface IPersonService (deve ser definido antes do uso).
     */
    void setPersonService(IPersonService* service);

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
