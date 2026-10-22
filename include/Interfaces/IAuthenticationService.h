#ifndef IAUTHENTICATION_SERVICE_H
#define IAUTHENTICATION_SERVICE_H

#include "../Domains/Email.h"
#include "../Domains/Password.h"
#include "../Domains/Role.h"

/**
 * @brief Interface abstrata do serviço de autenticação.
 */
class IAuthenticationService {
public:
    virtual ~IAuthenticationService() {}

    /**
     * @brief Autentica uma pessoa.
     * @param email E-mail informado.
     * @param password Senha informada.
     * @param role Recebe o papel da pessoa quando a autenticação tem sucesso.
     * @return true se e-mail e senha conferem, false caso contrário.
     */
    virtual bool authenticate(const Email& email, const Password& password, Role& role) = 0;
};

#endif