#ifndef BOARD_H
#define BOARD_H

#include "../Domains/Identifier.h"
#include "../Domains/Name.h"
#include "../Domains/Limit.h"

/**
 * @brief Classe que representa a entidade Quadro.
 * 
 * Um quadro Kanban é caracterizado por identificador (chave primária), nome e limite WIP.
 */
class Board {
private:
    Identifier identifier;
    Name name;
    Limit limit;

public:
    void setIdentifier(Identifier identifier);
    Identifier getIdentifier() const;

    void setName(Name nome);
    Name getName() const;

    void setLimit(Limit limit);
    Limit getLimit() const;
};

#endif