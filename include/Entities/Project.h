#ifndef PROJECT_H
#define PROJECT_H

#include "../Domains/Identifier.h"
#include "../Domains/Name.h"
#include "../Domains/Text.h"
#include "../Domains/Timestamp.h"
#include "../Domains/Email.h"

/**
 * @brief Classe que representa a entidade Projeto.
 * 
 * Um projeto é caracterizado por identificador (chave primária), nome, descrição, data de início e data de término.
 */
class Project {
private:
    Identifier identifier;
    Name name;
    Text description;
    Timestamp start;
    Timestamp end;
    // ...campos existentes...
    Email managerEmail;

public:
    // ...
    void setManagerEmail(Email managerEmail);
    Email getManagerEmail() const;

    void setIdentifier(Identifier identifier);
    Identifier getIdentifier() const;

    void setName(Name name);
    Name getName() const;

    void setDescription(Text description);
    Text getDescription() const;

    void setStart(Timestamp start);
    Timestamp getStart() const;

    void setEnd(Timestamp end);
    Timestamp getEnd() const;
};

#endif