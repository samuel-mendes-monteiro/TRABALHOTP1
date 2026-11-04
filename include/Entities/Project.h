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
 * Um projeto é caracterizado por identificador (chave primária), nome, descrição,
 * data de início, data de término e e-mail do gestor (a pessoa que criou o projeto).
 */
class Project {
private:
    Identifier identifier;
    Name name;
    Text description;
    Timestamp start;
    Timestamp end;
    Email managerEmail;

public:
    /**
     * @brief Define o identificador do projeto.
     * @param identifier Instância da classe Identifier.
     */
    void setIdentifier(Identifier identifier);

    /**
     * @brief Obtém o identificador do projeto.
     * @return Identifier Instância de Identifier armazenada.
     */
    Identifier getIdentifier() const;

    /**
     * @brief Define o nome do projeto.
     * @param name Instância da classe Name.
     */
    void setName(Name name);

    /**
     * @brief Obtém o nome do projeto.
     * @return Name Instância de Name armazenada.
     */
    Name getName() const;

    /**
     * @brief Define a descrição do projeto.
     * @param description Instância da classe Text.
     */
    void setDescription(Text description);

    /**
     * @brief Obtém a descrição do projeto.
     * @return Text Instância de Text armazenada.
     */
    Text getDescription() const;

    /**
     * @brief Define a data de início do projeto.
     * @param start Instância da classe Timestamp.
     */
    void setStart(Timestamp start);

    /**
     * @brief Obtém a data de início do projeto.
     * @return Timestamp Instância de Timestamp armazenada.
     */
    Timestamp getStart() const;

    /**
     * @brief Define a data de término do projeto.
     * @param end Instância da classe Timestamp.
     */
    void setEnd(Timestamp end);

    /**
     * @brief Obtém a data de término do projeto.
     * @return Timestamp Instância de Timestamp armazenada.
     */
    Timestamp getEnd() const;

    /**
     * @brief Define o e-mail do gestor do projeto.
     * @param managerEmail Instância da classe Email.
     */
    void setManagerEmail(Email managerEmail);

    /**
     * @brief Obtém o e-mail do gestor do projeto.
     * @return Email Instância de Email armazenada.
     */
    Email getManagerEmail() const;
};

#endif
