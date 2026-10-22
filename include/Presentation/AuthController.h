#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include "../Interfaces/IAuthenticationService.h"
#include "Session.h"

/**
 * @brief Controladora de login e logout.
 */
class AuthController {
private:
    IAuthenticationService* authService;
    Session& session;

public:
    AuthController(IAuthenticationService* service, Session& session);
    void handleLogin();
    void handleLogout();
};

#endif