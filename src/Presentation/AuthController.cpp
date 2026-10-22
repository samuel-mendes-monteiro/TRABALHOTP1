#include "../../include/Presentation/AuthController.h"
#include <iostream>
#include <stdexcept>

AuthController::AuthController(IAuthenticationService* service, Session& session)
    : authService(service), session(session) {}

void AuthController::handleLogin() {
    std::string emailStr, passStr;
    std::cout << "\n--- LOGIN ---" << std::endl;
    std::cout << "E-mail: ";
    std::cin >> emailStr;
    std::cout << "Senha: ";
    std::cin >> passStr;

    try {
        Email email;       email.setValue(emailStr);
        Password password; password.setValue(passStr);
        Role role;

        if (authService->authenticate(email, password, role)) {
            session.login(email, role);
            std::cout << "[SUCESSO] Autenticado como " << role.getValue() << "." << std::endl;
        } else {
            std::cout << "[ERRO] E-mail ou senha incorretos." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void AuthController::handleLogout() {
    session.logout();
    std::cout << "[SUCESSO] Sessao encerrada." << std::endl;
}