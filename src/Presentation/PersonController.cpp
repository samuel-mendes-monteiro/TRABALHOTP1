#include "../../include/Presentation/PersonController.h"
#include "../../include/Domains/Email.h"
#include "../../include/Domains/Name.h"
#include "../../include/Domains/Password.h"
#include "../../include/Domains/Role.h"
#include <iostream>
#include <stdexcept>

PersonController::PersonController(IPersonService* service, Session& session)
    : personService(service), session(session) {}

void PersonController::handleListPersons() {
    std::cout << "\n--- LISTAR PESSOAS ---" << std::endl;
    std::vector<Email> emails = personService->listPersons();
    if (emails.empty()) { std::cout << "Nenhuma pessoa cadastrada." << std::endl; return; }
    for (const auto& e : emails) std::cout << e.getValue() << std::endl;
}

void PersonController::handleCreatePerson() {
    std::string emailStr, nameStr, passStr, roleStr;

    std::cout << "\n--- CADASTRAR PESSOA ---" << std::endl;
    std::cout << "Digite o e-mail: ";
    std::cin >> emailStr;
    std::cout << "Digite o nome: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, nameStr);
    std::cout << "Digite a senha: ";
    std::cin >> passStr;
    std::cout << "Digite o papel (GESTOR ou DESENVOLVEDOR): ";
    std::cin >> roleStr;

    try {
        Email email; 
        email.setValue(emailStr);
        
        Name name; 
        name.setValue(nameStr);
        
        Password password; 
        password.setValue(passStr);
        
        Role role; 
        role.setValue(roleStr);

        Person person;
        person.setEmail(email);
        person.setName(name);
        person.setPassword(password);
        person.setRole(role);

        if (personService->createPerson(person)) {
            std::cout << "[SUCESSO] Pessoa cadastrada com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Ja existe uma pessoa cadastrada com este e-mail." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void PersonController::handleReadPerson() {
    std::string emailStr;
    std::cout << "\n--- CONSULTAR PESSOA ---" << std::endl;
    std::cout << "Digite o e-mail da pessoa: ";
    std::cin >> emailStr;

    try {
        Email email;
        email.setValue(emailStr);
        Person person = personService->readPerson(email);

        std::cout << "[ENCONTRADO]" << std::endl;
        std::cout << "E-mail: " << person.getEmail().getValue() << std::endl;
        std::cout << "Nome: " << person.getName().getValue() << std::endl;
        std::cout << "Papel: " << person.getRole().getValue() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

void PersonController::handleUpdatePerson() {
    std::string emailStr, nameStr, passStr, roleStr;

    std::cout << "\n--- ATUALIZAR PESSOA ---" << std::endl;
    std::cout << "Digite o e-mail da pessoa a ser atualizada: ";
    std::cin >> emailStr;
    if (emailStr != session.getEmail().getValue()) {
    std::cout << "[ACESSO NEGADO] So e possivel atualizar a propria conta." << std::endl;
    return;
}
    std::cout << "Digite o novo nome: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, nameStr);
    std::cout << "Digite a nova senha: ";
    std::cin >> passStr;
    std::cout << "Digite o novo papel: ";
    std::cin >> roleStr;

    try {
        Email email; email.setValue(emailStr);
        Name name; name.setValue(nameStr);
        Password password; password.setValue(passStr);
        Role role; role.setValue(roleStr);

        Person person;
        person.setEmail(email);
        person.setName(name);
        person.setPassword(password);
        person.setRole(role);

        if (personService->updatePerson(person)) {

            if (emailStr == session.getEmail().getValue()) session.login(email, role);

            std::cout << "[SUCESSO] Dados atualizados com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Pessoa nao encontrada para atualizacao." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void PersonController::handleDeletePerson() {
    std::string emailStr;
    std::cout << "\n--- EXCLUIR PESSOA ---" << std::endl;
    std::cout << "Digite o e-mail da pessoa que deseja excluir: ";
    std::cin >> emailStr;

    // O GESTOR pode excluir qualquer pessoa; o DESENVOLVEDOR, apenas a propria conta.
    if (!session.isManager() && emailStr != session.getEmail().getValue()) {
        std::cout << "[ACESSO NEGADO] Desenvolvedor so pode excluir a propria conta." << std::endl;
        return;
    }

    try {
        Email email;
        email.setValue(emailStr);

        if (personService->deletePerson(email)) {
            std::cout << "[SUCESSO] Pessoa excluida com sucesso!" << std::endl;

            if (emailStr == session.getEmail().getValue()) {
                session.logout();
                std::cout << "Sua conta foi excluida. Sessao encerrada." << std::endl;
            }
        } else {
            std::cout << "[ERRO] Pessoa nao encontrada." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}