#ifndef BOARD_H
#define BOARD_H

#include "../Domains/Identifier.h"
#include "../Domains/Name.h"
#include "../Domains/Limit.h"

/**
 * @brief Classe que representa a entidade Quadro.
 *
 * Um quadro Kanban é caracterizado por identificador (chave primária), nome, limite WIP
 * e identificador do projeto ao qual pertence.
 */
class Board {
private:
    Identifier identifier;
    Identifier projectId;
    Name name;
    Limit limit;

public:
    /**
     * @brief Define o identificador do quadro.
     * @param identifier Instância da classe Identifier.
     */
    void setIdentifier(Identifier identifier);

    /**
     * @brief Obtém o identificador do quadro.
     * @return Identifier Instância de Identifier armazenada.
     */
    Identifier getIdentifier() const;

    /**
     * @brief Define o nome do quadro.
     * @param name Instância da classe Name.
     */
    void setName(Name name);

    /**
     * @brief Obtém o nome do quadro.
     * @return Name Instância de Name armazenada.
     */
    Name getName() const;

    /**
     * @brief Define o limite WIP do quadro.
     * @param limit Instância da classe Limit.
     */
    void setLimit(Limit limit);

    /**
     * @brief Obtém o limite WIP do quadro.
     * @return Limit Instância de Limit armazenada.
     */
    Limit getLimit() const;

    /**
     * @brief Define o identificador do projeto ao qual o quadro pertence.
     * @param projectId Instância da classe Identifier.
     */
    void setProjectId(Identifier projectId);

    /**
     * @brief Obtém o identificador do projeto ao qual o quadro pertence.
     * @return Identifier Instância de Identifier armazenada.
     */
    Identifier getProjectId() const;
};

#endif
