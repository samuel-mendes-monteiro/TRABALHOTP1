#include "../../include/Presentation/TaskController.h"
#include "../../include/Domains/Identifier.h"
#include "../../include/Domains/Name.h"
#include "../../include/Domains/Text.h"
#include "../../include/Domains/Priority.h"
#include "../../include/Domains/State.h"
#include "../../include/Domains/Size.h"
#include "../../include/Domains/Timestamp.h"
#include "../../include/Domains/Email.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

TaskController::TaskController(ITaskService* service, Session& session)
    : taskService(service), session(session) {}

void TaskController::handleCreateTask() {
    if (!session.isManager()) {
        std::cout << "[ACESSO NEGADO] Servico restrito ao GESTOR." << std::endl;
        return;
    }

    std::string idStr, boardIdStr, devStr, nameStr, descStr, prioStr, sizeStr, entryStr;

    std::cout << "\n--- CADASTRAR CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador (6 caracteres, 3 letras e 3 digitos): ";
    std::cin >> idStr;
    std::cout << "Digite o identificador do quadro ao qual este cartao pertence: ";
    std::cin >> boardIdStr;
    std::cout << "Digite o e-mail do desenvolvedor responsavel: ";
    std::cin >> devStr;
    std::cout << "Digite o nome (ate 15 caracteres): ";
    std::cin.ignore();
    std::getline(std::cin, nameStr);
    std::cout << "Digite a descricao (ate 30 caracteres, terminada em ponto): ";
    std::getline(std::cin, descStr);
    std::cout << "Digite a prioridade (ALTA, MEDIA, BAIXA): ";
    std::cin >> prioStr;
    std::cout << "Digite o tamanho (GRANDE, MEDIO, PEQUENO): ";
    std::cin >> sizeStr;
    std::cout << "Digite a data de entrada (DIA-MES-ANO-HORARIO, ex: 10-JAN-2026-08:00): ";
    std::cin >> entryStr;

    try {
        Identifier identifier;  identifier.setValue(idStr);
        Identifier boardId;     boardId.setValue(boardIdStr);
        Email developer;        developer.setValue(devStr);
        Name name;              name.setValue(nameStr);
        Text description;       description.setValue(descStr);
        Priority priority;      priority.setValue(prioStr);
        Size size;              size.setValue(sizeStr);
        Timestamp entryDate;    entryDate.setValue(entryStr);

        // Todo cartao novo nasce em A FAZER -- nao e escolha do usuario.
        State state;            state.setValue("A FAZER");

        Task task;
        task.setIdentifier(identifier);
        task.setBoardId(boardId);
        task.setDeveloperEmail(developer);
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
        std::cout << "Descricao: " << task.getDescription().getValue() << std::endl;
        std::cout << "Prioridade: " << task.getPriority().getValue() << std::endl;
        std::cout << "Estado atual: " << task.getState().getValue() << std::endl;
        std::cout << "Tamanho: " << task.getSize().getValue() << std::endl;
        std::cout << "Quadro: " << task.getBoardId().getValue() << std::endl;
        std::cout << "Desenvolvedor: " << task.getDeveloperEmail().getValue() << std::endl;
        std::cout << "Entrada: " << task.getEntryDate().getValue() << std::endl;

        // Evita imprimir datas ainda vazias.
        if (task.getState().getValue() != "A FAZER")
            std::cout << "Inicio: " << task.getStartDate().getValue() << std::endl;
        if (task.getState().getValue() == "FEITO")
            std::cout << "Termino: " << task.getEndDate().getValue() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

void TaskController::handleUpdateTask() {
    if (!session.isManager()) {
        std::cout << "[ACESSO NEGADO] Servico restrito ao GESTOR." << std::endl;
        return;
    }

    std::string idStr, nameStr, descStr, prioStr, sizeStr;

    std::cout << "\n--- ATUALIZAR CARTAO DE ATIVIDADE ---" << std::endl;
    std::cout << "Digite o identificador do cartao a ser atualizado: ";
    std::cin >> idStr;

    try {
        Identifier identifier;
        identifier.setValue(idStr);

        // Parte do cartao ja existente: estado, datas, quadro e desenvolvedor
        // permanecem. Estado e datas so mudam via handleMoveTask.
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

        Name name;          name.setValue(nameStr);
        Text description;   description.setValue(descStr);
        Priority priority;  priority.setValue(prioStr);
        Size size;          size.setValue(sizeStr);

        task.setName(name);
        task.setDescription(description);
        task.setPriority(priority);
        task.setSize(size);

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
    if (!session.isManager()) {
        std::cout << "[ACESSO NEGADO] Servico restrito ao GESTOR." << std::endl;
        return;
    }

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

void TaskController::handleListTasks() {
    std::cout << "\n--- LISTAR CARTOES ---" << std::endl;
    std::vector<Identifier> ids = taskService->listTasks();
    if (ids.empty()) {
        std::cout << "Nenhum cartao cadastrado." << std::endl;
        return;
    }
    for (const auto& id : ids) std::cout << id.getValue() << std::endl;
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
        Identifier identifier;  identifier.setValue(idStr);
        State newState;         newState.setValue(newStateStr);
        Timestamp moveTime;     moveTime.setValue(timeStr);

        if (taskService->moveTask(identifier, newState, moveTime)) {
            std::cout << "[SUCESSO] Cartao movimentado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Movimentacao invalida pelas regras do Kanban ou cartao nao encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        // Inclui limite WIP atingido e datas incoerentes.
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

namespace {
    // Formata minutos em dias/horas/minutos so para exibicao.
    std::string formatMinutes(long long totalMinutes) {
        long long dias = totalMinutes / (24 * 60);
        long long horas = (totalMinutes % (24 * 60)) / 60;
        long long minutos = totalMinutes % 60;
        return std::to_string(dias) + "d " + std::to_string(horas) + "h " + std::to_string(minutos) + "m";
    }
}

void TaskController::handleReadMetrics(int metric) {
    std::cout << "\n--- METRICAS KANBAN ---" << std::endl;

    try {
        switch (metric) {
            case 1: {
                std::string idStr;
                std::cout << "Identificador do cartao: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                std::cout << "Tempo de ciclo: " << formatMinutes(taskService->readCycleTime(id)) << std::endl;
                break;
            }
            case 2: {
                std::string idStr;
                std::cout << "Identificador do quadro: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                std::cout << "Tempo de ciclo medio: " << formatMinutes(taskService->readAverageCycleTime(id)) << std::endl;
                break;
            }
            case 3: {
                std::string idStr;
                std::cout << "Identificador do cartao: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                std::cout << "Lead time: " << formatMinutes(taskService->readLeadTime(id)) << std::endl;
                break;
            }
            case 4: {
                std::string idStr;
                std::cout << "Identificador do quadro: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                std::cout << "Lead time medio: " << formatMinutes(taskService->readAverageLeadTime(id)) << std::endl;
                break;
            }
            case 5: {
                std::string idStr;
                std::cout << "Identificador do quadro: ";
                std::cin >> idStr;
                Identifier id; id.setValue(idStr);
                std::cout << "WIP atual: " << taskService->readWip(id) << " cartao(oes) em FAZENDO." << std::endl;
                break;
            }
            default:
                std::cout << "[AVISO] Metrica invalida." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}