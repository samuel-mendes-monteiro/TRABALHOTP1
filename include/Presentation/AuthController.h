#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include "../Interfaces/IAuthenticationService.h"
#include "Session.h"

/**
 * @brief Controladora de login e logout.
 *
 * Recebe e-mail e senha pelo terminal, valida os formatos e aciona o serviço
 * através da interface IAuthenticationService.
 */
class AuthController {
private:
    IAuthenticationService* authService;
    Session& session;

public:
    /**
     * @brief Construtor.
     * @param service Ponteiro para uma implementação de IAuthenticationService.
     * @param session Sessão que receberá os dados do usuário autenticado.
     */
    AuthController(IAuthenticationService* service, Session& session);

    /**
     * @brief Executa o fluxo de login: pede e-mail e senha e, se conferem, inicia a sessão.
     */
    void handleLogin();

    /**
     * @brief Encerra a sessão do usuário.
     */
    void handleLogout();
};

#endif
