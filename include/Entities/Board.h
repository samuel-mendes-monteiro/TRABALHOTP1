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
    Identifier identifier, projectId;
    Name name;
    Limit limit;

public:
    /**
     * @brief Define o identificador da pessoa.
     * @param identifier Instância da classe identifier.
     */

    void setIdentifier(Identifier identifier);
    /**
     * @brief Obtem o identificador do quadro.
     * @return identifier Instancica armazenada
     */

    Identifier getIdentifier() const;
    /**
     * @brief Define o nome da pessoa.
     * @param name Instância armazenada
     */

    void setName(Name nome);
    /**
     * @brief Obtem o nome do quadro.
     * @return name Instancica armaenada
     */
    Name getName() const;

    /**
     * @brief Define o limite do quadro
     * @param limit Instancia da classe limit.
     */
    void setLimit(Limit limit);

    /**
     * @brief Obtém o limite do quadro.
     * @return limite Instância de limit armazenada.
     */
    Limit getLimit() const;


    void setProjectId(Identifier projectId);
    Identifier getProjectId() const;
};

#endif