#ifndef TASK_H
#define TASK_H

#include "../Domains/Identifier.h"
#include "../Domains/Name.h"
#include "../Domains/Text.h"
#include "../Domains/Priority.h"
#include "../Domains/State.h"
#include "../Domains/Size.h"
#include "../Domains/Timestamp.h"

/**
 * @brief Classe que representa a entidade Cartão de Atividade (Task).
 * 
 * Contém identificador, nome, descrição, prioridade, estado, tamanho e timestamps de controle.
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

public:
    void setIdentifier(Identifier identifier);
    Identifier getIdentifier() const;

    void setName(Name name);
    Name getName() const;

    void setDescription(Text description);
    Text getDescription() const;

    void setPriority(Priority priority);
    Priority getPriority() const;

    void setState(State state);
    State getState() const;

    void setSize(Size size);
    Size getSize() const;

    void setEntryDate(Timestamp entryDate);
    Timestamp getEntryDate() const;

    void setStartDate(Timestamp startDate);
    Timestamp getStartDate() const;

    void setEndDate(Timestamp endDate);
    Timestamp getEndDate() const;

    void setBoardId(Identifier boardId);
    Identifier getBoardId() const;

};

#endif