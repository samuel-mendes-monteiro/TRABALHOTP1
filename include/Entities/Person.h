#ifndef PERSON_H
#define PERSON_H

#include "../Domains/Email.h"
#include "../Domains/Name.h"
#include "../Domains/Password.h"
#include "../Domains/Role.h"

/**
 * @brief Classe que representa a entidade Pessoa.
 * 
 * Uma pessoa é caracterizada por e-mail (chave primária), nome, senha e papel.
 */
class Person{
private:
    Email email;
    Name name;
    Password password;
    Role role;

public:
    /**
     * @brief Define o e-mail da pessoa.
     * @param email Instância da classe Email.
     */
    void setEmail(Email email);
    
    /**
     * @brief Obtém o e-mail da pessoa.
     * @return Email Instância de Email armazenada.
     */
    Email getEmail() const;

    /**
     * @brief Define o nome da pessoa.
     * @param name Instância da classe Name.
     */
    void setName(Name name);
    
    /**
     * @brief Obtém o nome da pessoa.
     * @return Name Instância de Name armazenada.
     */
    Name getName() const;

    /**
     * @brief Define a senha da pessoa.
     * @param password Instância da classe Password.
     */
    void setPassword(Password password);
    
    /**
     * @brief Obtém a senha da pessoa.
     * @return Password Instância de Password armazenada.
     */
    Password getPassword() const;

    /**
     * @brief Define o papel da pessoa.
     * @param role Instância da classe Role.
     */
    void setRole(Role role);
    
    /**
     * @brief Obtém o papel da pessoa.
     * @return Role Instância de Role armazenada.
     */
    Role getRole() const;
};

#endif