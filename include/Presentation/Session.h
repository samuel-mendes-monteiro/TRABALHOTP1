#ifndef SESSION_H
#define SESSION_H

#include "../Domains/Email.h"
#include "../Domains/Role.h"

/**
 * @brief Sessão do usuário autenticado: e-mail e papel.
 */
class Session {
private:
    Email email;
    Role role;
    bool logged = false;

public:
    /**
     * @brief Inicia a sessão de um usuário.
     * @param email E-mail do usuário autenticado.
     * @param role Papel do usuário autenticado.
     */
    void login(const Email& email, const Role& role) {
        this->email = email;
        this->role = role;
        logged = true;
    }

    /**
     * @brief Encerra a sessão e esquece os dados do usuário.
     */
    void logout() {
        logged = false;
        email = Email();
        role = Role();
    }

    /**
     * @brief Informa se há um usuário autenticado.
     * @return true se há sessão ativa.
     */
    bool isLoggedIn() const { return logged; }

    /**
     * @brief Informa se o usuário autenticado tem o papel GESTOR.
     * @return true se há sessão ativa e o papel é GESTOR.
     */
    bool isManager() const { return logged && role.getValue() == "GESTOR"; }

    /**
     * @brief Obtém o e-mail do usuário autenticado.
     * @return Email O e-mail da sessão (vazio se não há sessão ativa).
     */
    Email getEmail() const { return email; }
};

#endif
