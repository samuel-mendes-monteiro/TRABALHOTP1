#include "../../include/Presentation/TaskController.h"
#include "../../include/Domains/Identifier.h"
#include "../../include/Domains/Name.h"
#include "../../include/Domains/Text.h"
#include "../../include/Domains/Priority.h"
#include "../../include/Domains/State.h"
#include "../../include/Domains/Size.h"
#include "../../include/Domains/Timestamp.h"
#include <iostream>
#include <stdexcept>

TaskController::TaskController(ITaskService* service) {
    this->taskService = service;
}

void TaskController::handleCreateTask() {
    std::string idStr, nameStr, descStr, prioStr, stateStr, sizeStr, entryStr;

    std::cout << "\n--- CADASTRAR CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador (6 caracteres, 3 letras e 3 digitos): ";
    std::cin >> idStr;
    std::cout << "Digite o nome (ate 15 caracteres): ";
    std::cin.ignore();
    std::getline(std::cin, nameStr);
    std::cout << "Digite a descricao (ate 30 caracteres, terminada em ponto): ";
    std::getline(std::cin, descStr);
    std::cout << "Digite a prioridade (ALTA, MEDIA, BAIXA): ";
    std::cin >> prioStr;
    std::getline(std::cin, stateStr);
    std::cout << "Digite o tamanho (GRANDE, MEDIO, PEQUENO): ";
    std::cin >> sizeStr;
    std::cout << "Digite a data de entrada (DIA-MES-ANO-HORARIO): ";
    std::cin >> entryStr;

    try {
        Identifier identifier; identifier.setValue(idStr);
        Name name; name.setValue(nameStr);
        Text description; description.setValue(descStr);
        Priority priority; priority.setValue(prioStr);

        State state; state.setValue("A FAZER");
        // Todo cartao novo nasce em A FAZER -- nao e uma escolha do usuario.

        Size size; size.setValue(sizeStr);
        Timestamp entryDate; entryDate.setValue(entryStr);

        Task task;
        task.setIdentifier(identifier);
        task.setName(name);
        task.setDescription(description);
        task.setPriority(priority);
        task.setState(state);
        task.setSize(size);
        task.setEntryDate(entryDate);

        if (taskService->createTask(task)) {
            std::cout << "[SUCESSO] Cartao de atividade cadastrado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Ja existe um cartao com este identificador." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void TaskController::handleReadTask() {
    std::string idStr;
    std::cout << "\n--- CONSULTAR CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador do cartao: ";
    std::cin >> idStr;

    try {
        Identifier identifier;
        identifier.setValue(idStr);
        Task task = taskService->readTask(identifier);

        std::cout << "[ENCONTRADO]" << std::endl;
        std::cout << "Identificador: " << task.getIdentifier().getValue() << std::endl;
        std::cout << "Nome: " << task.getName().getValue() << std::endl;
        std::cout << "Estado atual: " << task.getState().getValue() << std::endl;
        std::cout << "Prioridade: " << task.getPriority().getValue() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

void TaskController::handleUpdateTask() {
    std::string idStr, nameStr, descStr, prioStr, sizeStr;
 
    std::cout << "\n--- ATUALIZAR CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador do cartao a ser atualizado: ";
    std::cin >> idStr;
 
    try {
        Identifier identifier;
        identifier.setValue(idStr);
 
        // Parte do cartao JA EXISTENTE em vez de um Task vazio. Assim
        // state, entryDate, startDate e endDate mantem o valor que ja
        // tinham -- so os campos abaixo sao sobrescritos.
        Task task = taskService->readTask(identifier);
 
        std::cout << "Digite o novo nome: ";
        std::cin.ignore();
        std::getline(std::cin, nameStr);
        std::cout << "Digite a nova descricao: ";
        std::getline(std::cin, descStr);
        std::cout << "Digite a nova prioridade (ALTA, MEDIA, BAIXA): ";
        std::cin >> prioStr;
        std::cout << "Digite o novo tamanho (GRANDE, MEDIO, PEQUENO): ";
        std::cin >> sizeStr;
 
        Name name; name.setValue(nameStr);
        Text description; description.setValue(descStr);
        Priority priority; priority.setValue(prioStr);
        Size size; size.setValue(sizeStr);
 
        task.setName(name);
        task.setDescription(description);
        task.setPriority(priority);
        task.setSize(size);
        // identifier, state, entryDate, startDate, endDate: sem alteracao.
        // Estado e datas de transicao sao responsabilidade exclusiva do
        // handleMoveTask, nunca de uma atualizacao generica de cadastro.
 
        if (taskService->updateTask(task)) {
            std::cout << "[SUCESSO] Cartao atualizado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Cartao nao encontrado para atualizacao." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void TaskController::handleDeleteTask() {
    std::string idStr;
    std::cout << "\n--- EXCLUIR CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador do cartao que deseja excluir: ";
    std::cin >> idStr;

    try {
        Identifier identifier;
        identifier.setValue(idStr);

        if (taskService->deleteTask(identifier)) {
            std::cout << "[SUCESSO] Cartao excluido com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Cartao nao encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

void TaskController::handleMoveTask() {
    std::string idStr, newStateStr;
    std::cout << "\n--- MOVER CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador do cartao: ";
    std::cin >> idStr;
    std::cout << "Digite o novo estado (FAZENDO ou FEITO): ";
    std::cin.ignore();
    std::getline(std::cin, newStateStr);

    try {
        Identifier identifier; identifier.setValue(idStr);
        State newState; newState.setValue(newStateStr);

        if (taskService->moveTask(identifier, newState)) {
            std::cout << "[SUCESSO] Cartao movimentado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Movimentacao invalida pelas regras do Kanban ou cartao nao encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

void TaskController::handleReadMetrics() {
    std::cout << "\n--- METRICAS KANBAN (WIP) ---" << std::endl;
    try {
        // Exemplo simples de chamada de WIP ou métricas gerais integradas
        std::cout << "Funcao de metricas e tempos de ciclo disponiveis via camada de servico." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}