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
    void login(const Email& email, const Role& role) { this->email = email; this->role = role; logged = true; }
    void logout() { logged = false; }
    bool isLoggedIn() const { return logged; }
    bool isManager() const { return logged && role.getValue() == "GESTOR"; }
    Email getEmail() const { return email; }
};

#endif