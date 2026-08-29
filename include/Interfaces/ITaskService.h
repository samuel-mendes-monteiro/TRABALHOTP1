#ifndef ITASK_SERVICE_H
#define ITASK_SERVICE_H

#include "../Entities/Task.h"

/**
 * @brief Interface abstrata que define os serviços relacionados à entidade Task (Cartão de Atividade).
 * 
 * Contém o contrato de métodos virtuais puros para gerenciar cartões de atividade, 
 * incluindo movimentações entre colunas e métricas de tempo (Cycle Time, Lead Time e WIP).
 */
class ITaskService {
public:
    virtual ~ITaskService() {}

    virtual bool createTask(const Task& task) = 0;
    virtual Task readTask(const Identifier& identifier) = 0;
    virtual bool updateTask(const Task& task) = 0;
    virtual bool deleteTask(const Identifier& identifier) = 0;
    virtual bool moveTask(const Identifier& identifier, const State& newState) = 0;
};

#endif