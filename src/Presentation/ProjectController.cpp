#include "../../include/Presentation/ProjectController.h"
#include "../../include/Domains/Identifier.h"
#include "../../include/Domains/Name.h"
#include "../../include/Domains/Text.h"
#include "../../include/Domains/Timestamp.h"
#include <iostream>
#include <stdexcept>

ProjectController::ProjectController(IProjectService* service) {
    this->projectService = service;
}

void ProjectController::handleCreateProject() {
    std::string idStr, nameStr, descStr, startStr, endStr;

    std::cout << "\n--- CADASTRAR PROJETO ---" << std::endl;
    std::cout << "Digite o identificador (6 caracteres, 3 letras e 3 digitos): ";
    std::cin >> idStr;
    std::cout << "Digite o nome do projeto (ate 15 caracteres): ";
    std::cin.ignore();
    std::getline(std::cin, nameStr);
    std::cout << "Digite a descricao (ate 30 caracteres, terminada em ponto): ";
    std::getline(std::cin, descStr);
    std::cout << "Digite a data de inicio (DIA-MES-ANO-HORARIO, ex: 10-JAN-2026-08:00): ";
    std::cin >> startStr;
    std::cout << "Digite a data de termino (DIA-MES-ANO-HORARIO): ";
    std::cin >> endStr;

    try {
        Identifier identifier; identifier.setValue(idStr);
        Name name; name.setValue(nameStr);
        Text description; description.setValue(descStr);
        Timestamp startDate; startDate.setValue(startStr);
        Timestamp endDate; endDate.setValue(endStr);

        Project project;
        project.setIdentifier(identifier);
        project.setName(name);
        project.setDescription(description);
        project.setStart(startDate);
        project.setEnd(endDate);

        if (projectService->createProject(project)) {
            std::cout << "[SUCESSO] Projeto cadastrado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Ja existe um projeto com este identificador." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void ProjectController::handleReadProject() {
    std::string idStr;
    std::cout << "\n--- CONSULTAR PROJETO ---" << std::endl;
    std::cout << "Digite o identificador do projeto: ";
    std::cin >> idStr;

    try {
        Identifier identifier;
        identifier.setValue(idStr);
        Project project = projectService->readProject(identifier);

        std::cout << "[ENCONTRADO]" << std::endl;
        std::cout << "Identificador: " << project.getIdentifier().getValue() << std::endl;
        std::cout << "Nome: " << project.getName().getValue() << std::endl;
        std::cout << "Descricao: " << project.getDescription().getValue() << std::endl;
        std::cout << "Inicio: " << project.getStart().getValue() << std::endl;
        std::cout << "Termino: " << project.getEnd().getValue() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

void ProjectController::handleUpdateProject() {
    std::string idStr, nameStr, descStr, startStr, endStr;

    std::cout << "\n--- ATUALIZAR PROJETO ---" << std::endl;
    std::cout << "Digite o identificador do projeto a ser atualizado: ";
    std::cin >> idStr;
    std::cout << "Digite o novo nome: ";
    std::cin.ignore();
    std::getline(std::cin, nameStr);
    std::cout << "Digite a nova descricao: ";
    std::getline(std::cin, descStr);
    std::cout << "Digite a nova data de inicio: ";
    std::cin >> startStr;
    std::cout << "Digite a nova data de termino: ";
    std::cin >> endStr;

    try {
        Identifier identifier; identifier.setValue(idStr);
        Name name; name.setValue(nameStr);
        Text description; description.setValue(descStr);
        Timestamp startDate; startDate.setValue(startStr);
        Timestamp endDate; endDate.setValue(endStr);

        Project project;
        project.setIdentifier(identifier);
        project.setName(name);
        project.setDescription(description);
        project.setStart(startDate);
        project.setEnd(endDate);

        if (projectService->updateProject(project)) {
            std::cout << "[SUCESSO] Projeto atualizado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Projeto nao encontrado para atualizacao." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void ProjectController::handleDeleteProject() {
    std::string idStr;
    std::cout << "\n--- EXCLUIR PROJETO ---" << std::endl;
    std::cout << "Digite o identificador do projeto que deseja excluir: ";
    std::cin >> idStr;

    try {
        Identifier identifier;
        identifier.setValue(idStr);

        if (projectService->deleteProject(identifier)) {
            std::cout << "[SUCESSO] Projeto excluido com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Projeto nao encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}