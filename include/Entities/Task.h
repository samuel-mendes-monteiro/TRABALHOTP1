#ifndef TASK_H
#define TASK_H

#include "../Domains/Identifier.h"
#include "../Domains/Name.h"
#include "../Domains/Text.h"
#include "../Domains/Priority.h"
#include "../Domains/State.h"
#include "../Domains/Size.h"
#include "../Domains/Timestamp.h"
#include "../Domains/Email.h"

/**
 * @brief Classe que representa a entidade Cartão de Atividade (Task).
 *
 * Um cartão é caracterizado por identificador (chave primária), nome, descrição,
 * prioridade, estado, tamanho, datas de entrada, início e término, identificador do
 * quadro ao qual pertence e e-mail do desenvolvedor responsável.
 */
class Task {
private:
    Identifier identifier;
    Name name;
    Text description;
    Priority priority;
    State state;
    Size size;
    Timestamp entryDate;
    Timestamp startDate;
    Timestamp endDate;
    Identifier boardId;
    Email developerEmail;

public:
    /**
     * @brief Define o identificador do cartão.
     * @param identifier Instância da classe Identifier.
     */
    void setIdentifier(Identifier identifier);

    /**
     * @brief Obtém o identificador do cartão.
     * @return Identifier Instância de Identifier armazenada.
     */
    Identifier getIdentifier() const;

    /**
     * @brief Define o nome do cartão.
     * @param name Instância da classe Name.
     */
    void setName(Name name);

    /**
     * @brief Obtém o nome do cartão.
     * @return Name Instância de Name armazenada.
     */
    Name getName() const;

    /**
     * @brief Define a descrição do cartão.
     * @param description Instância da classe Text.
     */
    void setDescription(Text description);

    /**
     * @brief Obtém a descrição do cartão.
     * @return Text Instância de Text armazenada.
     */
    Text getDescription() const;

    /**
     * @brief Define a prioridade do cartão.
     * @param priority Instância da classe Priority.
     */
    void setPriority(Priority priority);

    /**
     * @brief Obtém a prioridade do cartão.
     * @return Priority Instância de Priority armazenada.
     */
    Priority getPriority() const;

    /**
     * @brief Define o estado (coluna) do cartão.
     * @param state Instância da classe State.
     */
    void setState(State state);

    /**
     * @brief Obtém o estado (coluna) do cartão.
     * @return State Instância de State armazenada.
     */
    State getState() const;

    /**
     * @brief Define o tamanho do cartão.
     * @param size Instância da classe Size.
     */
    void setSize(Size size);

    /**
     * @brief Obtém o tamanho do cartão.
     * @return Size Instância de Size armazenada.
     */
    Size getSize() const;

    /**
     * @brief Define a data de entrada do cartão na coluna A FAZER.
     * @param entryDate Instância da classe Timestamp.
     */
    void setEntryDate(Timestamp entryDate);

    /**
     * @brief Obtém a data de entrada do cartão na coluna A FAZER.
     * @return Timestamp Instância de Timestamp armazenada.
     */
    Timestamp getEntryDate() const;

    /**
     * @brief Define a data em que o cartão entrou na coluna FAZENDO.
     * @param startDate Instância da classe Timestamp.
     */
    void setStartDate(Timestamp startDate);

    /**
     * @brief Obtém a data em que o cartão entrou na coluna FAZENDO.
     * @return Timestamp Instância de Timestamp armazenada.
     */
    Timestamp getStartDate() const;

    /**
     * @brief Define a data em que o cartão chegou à coluna FEITO.
     * @param endDate Instância da classe Timestamp.
     */
    void setEndDate(Timestamp endDate);

    /**
     * @brief Obtém a data em que o cartão chegou à coluna FEITO.
     * @return Timestamp Instância de Timestamp armazenada.
     */
    Timestamp getEndDate() const;

    /**
     * @brief Define o identificador do quadro ao qual o cartão pertence.
     * @param boardId Instância da classe Identifier.
     */
    void setBoardId(Identifier boardId);

    /**
     * @brief Obtém o identificador do quadro ao qual o cartão pertence.
     * @return Identifier Instância de Identifier armazenada.
     */
    Identifier getBoardId() const;

    /**
     * @brief Define o e-mail do desenvolvedor responsável pelo cartão.
     * @param developerEmail Instância da classe Email.
     */
    void setDeveloperEmail(Email developerEmail);

    /**
     * @brief Obtém o e-mail do desenvolvedor responsável pelo cartão.
     * @return Email Instância de Email armazenada.
     */
    Email getDeveloperEmail() const;
};

#endif
