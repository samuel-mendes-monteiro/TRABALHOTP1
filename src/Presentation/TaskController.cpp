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
#include <string>

TaskController::TaskController(ITaskService* service) {
    this->taskService = service;
}

void TaskController::handleCreateTask() {
    std::string idStr, nameStr, descStr, prioStr, sizeStr, entryStr, boardIdStr,stateStr;

    std::cout << "\n--- CADASTRAR CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador (6 caracteres, 3 letras e 3 digitos): ";
    std::cin >> idStr;
    std::cout << "Digite o identificador do quadro ao qual este cartao pertence: ";
    std::cin >> boardIdStr;
    std::cout << "Digite o nome (ate 15 caracteres): ";
    std::cin.ignore();
    std::getline(std::cin, nameStr);
    std::cout << "Digite a descricao (ate 30 caracteres, terminada em ponto): ";
    std::getline(std::cin, descStr);
    std::cout << "Digite a prioridade (ALTA, MEDIA, BAIXA): ";
    std::cin >> prioStr;
    std::cout << "Digite o tamanho (GRANDE, MEDIO, PEQUENO): ";
    std::cin >> sizeStr;
    std::cout << "Digite a data de entrada (DIA-MES-ANO-HORARIO): ";
    std::cin >> entryStr;

            // Todo cartao novo nasce em A FAZER -- nao e uma escolha do usuario.

    stateStr = "A FAZER";

    try {
        Identifier identifier; identifier.setValue(idStr);
        Identifier boardId; boardId.setValue(boardIdStr);
        Name name; name.setValue(nameStr);
        Text description; description.setValue(descStr);
        Priority priority; priority.setValue(prioStr);
        Size size; size.setValue(sizeStr);
        Timestamp entryDate; entryDate.setValue(entryStr);
        State state; state.setValue(stateStr);
        

        Task task;
        task.setIdentifier(identifier);
        task.setBoardId(boardId);
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
        std::cout << "Descrição: " << task.getDescription().getValue() <<std::endl;
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
    std::string idStr, newStateStr, timeStr;
    std::cout << "\n--- MOVER CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador do cartao: ";
    std::cin >> idStr;
    std::cout << "Digite o novo estado (FAZENDO ou FEITO): ";
    std::cin.ignore();
    std::getline(std::cin, newStateStr);
    std::cout << "Digite o horario da movimentacao (DIA-MES-ANO-HORARIO): ";
    std::cin >> timeStr;

    try {
        Identifier identifier; identifier.setValue(idStr);
        State newState; newState.setValue(newStateStr);
        Timestamp moveTime; moveTime.setValue(timeStr);

        if (taskService->moveTask(identifier, newState, moveTime)) {
            std::cout << "[SUCESSO] Cartao movimentado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Movimentacao invalida pelas regras do Kanban ou cartao nao encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

namespace {
    // Formata minutos em algo legivel (dias/horas/minutos) so pra exibicao.
    std::string formatMinutes(long long totalMinutes) {
        long long dias = totalMinutes / (24 * 60);
        long long horas = (totalMinutes % (24 * 60)) / 60;
        long long minutos = totalMinutes % 60;
        return std::to_string(dias) + "d " + std::to_string(horas) + "h " + std::to_string(minutos) + "m";
    }
}

void TaskController::handleReadMetrics() {
    std::cout << "\n--- METRICAS KANBAN ---" << std::endl;
    std::cout << "1. Tempo de ciclo de um cartao" << std::endl;
    std::cout << "2. Tempo de ciclo medio de um quadro" << std::endl;
    std::cout << "3. Lead time de um cartao" << std::endl;
    std::cout << "4. Lead time medio de um quadro" << std::endl;
    std::cout << "5. WIP de um quadro" << std::endl;
    std::cout << "Escolha: ";

    int opcao;
    if (!(std::cin >> opcao)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "[ERRO] Opcao invalida." << std::endl;
        return;
    }

    try {
        switch (opcao) {
            case 1: {
                std::string idStr;
                std::cout << "Identificador do cartao: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                long long minutos = taskService->readCycleTime(id);
                std::cout << "Tempo de ciclo: " << formatMinutes(minutos) << std::endl;
                break;
            }
            case 2: {
                std::string idStr;
                std::cout << "Identificador do quadro: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                long long minutos = taskService->readAverageCycleTime(id);
                std::cout << "Tempo de ciclo medio: " << formatMinutes(minutos) << std::endl;
                break;
            }
            case 3: {
                std::string idStr;
                std::cout << "Identificador do cartao: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                long long minutos = taskService->readLeadTime(id);
                std::cout << "Lead time: " << formatMinutes(minutos) << std::endl;
                break;
            }
            case 4: {
                std::string idStr;
                std::cout << "Identificador do quadro: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                long long minutos = taskService->readAverageLeadTime(id);
                std::cout << "Lead time medio: " << formatMinutes(minutos) << std::endl;
                break;
            }
            case 5: {
                std::string idStr;
                std::cout << "Identificador do quadro: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                int wip = taskService->readWip(id);
                std::cout << "WIP atual: " << wip << " cartao(oes) em FAZENDO." << std::endl;
                break;
            }
            default:
                std::cout << "[AVISO] Opcao invalida." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}