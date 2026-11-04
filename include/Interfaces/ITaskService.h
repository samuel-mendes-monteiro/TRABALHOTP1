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

    /**
     * @brief Serviço 16: cria um cartão de atividade.
     * @param task Cartão a ser criado.
     * @return true se foi criado, false se já existe cartão com o mesmo identificador.
     * @throw std::invalid_argument se o quadro não existe, se o desenvolvedor não existe
     *        ou se ele não tem o papel DESENVOLVEDOR.
     */
    virtual bool createTask(const Task& task) = 0;

    /**
     * @brief Serviço 17: lê os dados de um cartão.
     * @param identifier Identificador do cartão.
     * @return Task O cartão encontrado.
     * @throw std::invalid_argument se o cartão não existe.
     */
    virtual Task readTask(const Identifier& identifier) = 0;

    /**
     * @brief Serviço 18: atualiza os dados de um cartão.
     * @param task Cartão com os novos dados, identificado pelo seu identificador.
     * @return true se foi atualizado, false se o cartão não existe.
     */
    virtual bool updateTask(const Task& task) = 0;

    /**
     * @brief Serviço 19: exclui um cartão.
     * @param identifier Identificador do cartão.
     * @return true se foi excluído, false se o cartão não existe.
     */
    virtual bool deleteTask(const Identifier& identifier) = 0;

    /**
     * @brief Serviço 21: move um cartão entre colunas do quadro (A FAZER -> FAZENDO ou FAZENDO -> FEITO).
     * @param identifier Identificador do cartão a ser movido.
     * @param newState Novo estado desejado.
     * @param moveTime Horário em que a movimentação ocorreu; gravado como
     *        startDate (entrada em FAZENDO) ou endDate (entrada em FEITO),
     *        conforme a transição.
     * @return true se a movimentação foi aplicada, false se a transição é
     *         inválida pelas regras do Kanban ou o cartão não existe.
     * @throw std::invalid_argument se o limite WIP do quadro foi atingido ou se
     *        moveTime é anterior à data anterior do cartão (entrada ou início).
     */
    virtual bool moveTask(const Identifier& identifier, const State& newState, const Timestamp& moveTime) = 0;

    /**
     * @brief Serviço 22: tempo de ciclo de um cartão (FAZENDO -> FEITO), em minutos.
     * @param taskId Identificador do cartão.
     * @return long long Tempo de ciclo em minutos.
     * @throw std::invalid_argument se o cartão não existe ou ainda não chegou em FEITO.
     */
    virtual long long readCycleTime(const Identifier& taskId) = 0;

    /**
     * @brief Serviço 23: média do tempo de ciclo dos cartões concluídos de um quadro, em minutos.
     * @param boardId Identificador do quadro.
     * @return long long Média do tempo de ciclo em minutos.
     * @throw std::invalid_argument se o quadro não existe ou não tem nenhum cartão concluído.
     */
    virtual long long readAverageCycleTime(const Identifier& boardId) = 0;

    /**
     * @brief Serviço 24: lead time de um cartão (A FAZER -> FEITO), em minutos.
     * @param taskId Identificador do cartão.
     * @return long long Lead time em minutos.
     * @throw std::invalid_argument se o cartão não existe ou ainda não chegou em FEITO.
     */
    virtual long long readLeadTime(const Identifier& taskId) = 0;

    /**
     * @brief Serviço 25: média do lead time dos cartões concluídos de um quadro, em minutos.
     * @param boardId Identificador do quadro.
     * @return long long Média do lead time em minutos.
     * @throw std::invalid_argument se o quadro não existe ou não tem nenhum cartão concluído.
     */
    virtual long long readAverageLeadTime(const Identifier& boardId) = 0;

    /**
     * @brief Serviço 26: WIP de um quadro — número de cartões atualmente em FAZENDO.
     * @param boardId Identificador do quadro.
     * @return int Quantidade de cartões em FAZENDO.
     * @throw std::invalid_argument se o quadro não existe.
     */
    virtual int readWip(const Identifier& boardId) = 0;

    /**
     * @brief Serviço 20: lista os identificadores de todos os cartões.
     * @return Lista de identificadores.
     */
    virtual std::vector<Identifier> listTasks() = 0;
};

#endif
