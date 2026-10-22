#ifndef AUTHENTICATION_SERVICE_H
#define AUTHENTICATION_SERVICE_H

#include "../Interfaces/IAuthenticationService.h"
#include "../Containers/PersonContainer.h"

/**
 * @brief Implementa a autenticação consultando o contêiner de pessoas.
 */
class AuthenticationService : public IAuthenticationService {
private:
    PersonContainer& persons;

public:
    AuthenticationService(PersonContainer& persons);
    bool authenticate(const Email& email, const Password& password, Role& role) override;
};

#endif