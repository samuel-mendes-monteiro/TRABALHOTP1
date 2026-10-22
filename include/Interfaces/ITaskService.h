#ifndef ITASK_SERVICE_H
#define ITASK_SERVICE_H
#include <vector>
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


    /**
     * @brief Move um cartão entre colunas do quadro (A FAZER -> FAZENDO ou FAZENDO -> FEITO).
     * @param identifier Identificador do cartão a ser movido.
     * @param newState Novo estado desejado.
     * @param moveTime Horário em que a movimentação ocorreu; gravado como
     *        startDate (entrada em FAZENDO) ou endDate (entrada em FEITO),
     *        conforme a transição.
     * @return true se a movimentação foi aplicada, false se a transição é
     *         inválida pelas regras do Kanban ou o cartão não existe.
     */
    
    virtual bool moveTask(const Identifier& identifier, const State& newState , const Timestamp& moveTime) = 0;
    /**
     * @brief Serviço 22: tempo de ciclo de um cartão (FAZENDO -> FEITO), em minutos.
     * @throw std::invalid_argument se o cartão não existe ou ainda não chegou em FEITO.
     */
    virtual long long readCycleTime(const Identifier& taskId) = 0;
    /**
     * @brief Serviço 23: média do tempo de ciclo dos cartões concluídos de um quadro, em minutos.
     * @throw std::invalid_argument se o quadro não tem nenhum cartão concluído.
     */
    virtual long long readAverageCycleTime(const Identifier& boardId) = 0;
 
    /**
     * @brief Serviço 24: lead time de um cartão (A FAZER -> FEITO), em minutos.
     * @throw std::invalid_argument se o cartão não existe ou ainda não chegou em FEITO.
     */
    virtual long long readLeadTime(const Identifier& taskId) = 0;
 
    /**
     * @brief Serviço 25: média do lead time dos cartões concluídos de um quadro, em minutos.
     * @throw std::invalid_argument se o quadro não tem nenhum cartão concluído.
     */
    virtual long long readAverageLeadTime(const Identifier& boardId) = 0;
 
    /**
     * @brief Serviço 26: WIP de um quadro — número de cartões atualmente em FAZENDO.
     */
    virtual int readWip(const Identifier& boardId) = 0;


    virtual std::vector<Identifier> listTasks() = 0;
};
 
#endif