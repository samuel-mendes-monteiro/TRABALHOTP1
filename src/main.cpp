#include <iostream>
#include <stdexcept>

#include "../include/Containers/PersonContainer.h"
#include "../include/Containers/ProjectContainer.h"
#include "../include/Containers/BoardContainer.h"
#include "../include/Containers/TaskContainer.h"

#include "../include/Services/AuthenticationService.h"
#include "../include/Services/PersonService.h"
#include "../include/Services/ProjectService.h"
#include "../include/Services/BoardService.h"
#include "../include/Services/TaskService.h"

#include "../include/Presentation/Session.h"
#include "../include/Presentation/AuthController.h"
#include "../include/Presentation/PersonController.h"
#include "../include/Presentation/ProjectController.h"
#include "../include/Presentation/BoardController.h"
#include "../include/Presentation/TaskController.h"

using namespace std;

int main() {
    // Contêineres: cada um pertence a um único módulo da camada de serviço.
    PersonContainer  personContainer;   // módulo Pessoas
    ProjectContainer projectContainer;  // módulo Projetos
    BoardContainer   boardContainer;    // módulo Quadros
    TaskContainer    taskContainer;     // módulo Cartões de Atividades

    // Serviços (camada de serviço)
    AuthenticationService authService(personContainer);
    PersonService  personService(personContainer);
    ProjectService projectService(projectContainer);
    BoardService   boardService(boardContainer);
    TaskService    taskService(taskContainer);

    // Ligações entre os módulos de serviço, sempre por meio das interfaces.
    personService.setProjectService(&projectService);
    personService.setTaskService(&taskService);
    projectService.setPersonService(&personService);
    projectService.setBoardService(&boardService);
    boardService.setProjectService(&projectService);
    boardService.setTaskService(&taskService);
    taskService.setBoardService(&boardService);
    taskService.setPersonService(&personService);

    // Sessão e controladoras
    Session session;
    AuthController    authController(&authService, session);
    PersonController  personController(&personService, session);
    ProjectController projectController(&projectService, session);
    BoardController   boardController(&boardService, session);
    TaskController    taskController(&taskService, session);

    int option = -1;

    do {
        if (!session.isLoggedIn()) {
            cout << "\n========================================" << endl;
            cout << "      SISTEMA DE GESTAO KANBAN          " << endl;
            cout << "========================================" << endl;
            cout << " 1. Criar conta" << endl;
            cout << " 2. Login" << endl;
            cout << " 0. Sair" << endl;
            cout << "Escolha uma opcao: ";
        } else {
            cout << "\n========================================" << endl;
            cout << " Usuario: " << session.getEmail().getValue()
                 << (session.isManager() ? " (GESTOR)" : " (DESENVOLVEDOR)") << endl;
            cout << "========================================" << endl;
            cout << " PESSOAS:   1 Criar  2 Ler  3 Atualizar  4 Excluir  5 Listar" << endl;
            cout << " PROJETOS:  6 Criar  7 Ler  8 Atualizar  9 Excluir  10 Listar" << endl;
            cout << " QUADROS:   11 Criar 12 Ler 13 Atualizar 14 Excluir 15 Listar" << endl;
            cout << " CARTOES:   16 Criar 17 Ler 18 Atualizar 19 Excluir 20 Listar" << endl;
            cout << " 21 Mover cartao" << endl;
            cout << " 22 Tempo de ciclo   23 Tempo de ciclo medio" << endl;
            cout << " 24 Lead time        25 Lead time medio       26 WIP" << endl;
            cout << " 27 Logout    0 Sair" << endl;
            cout << "Escolha uma opcao: ";
        }

        if (!(cin >> option)) {
            if (cin.eof()) break;
            cout << "[ERRO] Entrada invalida. Tente novamente." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            option = -1;
            continue;
        }

        try {
            if (!session.isLoggedIn()) {
                switch (option) {
                    case 1: personController.handleCreatePerson(); break;
                    case 2: authController.handleLogin(); break;
                    case 0: cout << "Encerrando o sistema. Ate logo!" << endl; break;
                    default: cout << "[AVISO] Opcao desconhecida." << endl;
                }
            } else {
                switch (option) {
                    case 1:  personController.handleCreatePerson(); break;
                    case 2:  personController.handleReadPerson(); break;
                    case 3:  personController.handleUpdatePerson(); break;
                    case 4:  personController.handleDeletePerson(); break;
                    case 5:  personController.handleListPersons(); break;

                    case 6:  projectController.handleCreateProject(); break;
                    case 7:  projectController.handleReadProject(); break;
                    case 8:  projectController.handleUpdateProject(); break;
                    case 9:  projectController.handleDeleteProject(); break;
                    case 10: projectController.handleListProjects(); break;

                    case 11: boardController.handleCreateBoard(); break;
                    case 12: boardController.handleReadBoard(); break;
                    case 13: boardController.handleUpdateBoard(); break;
                    case 14: boardController.handleDeleteBoard(); break;
                    case 15: boardController.handleListBoards(); break;

                    case 16: taskController.handleCreateTask(); break;
                    case 17: taskController.handleReadTask(); break;
                    case 18: taskController.handleUpdateTask(); break;
                    case 19: taskController.handleDeleteTask(); break;
                    case 20: taskController.handleListTasks(); break;
                    case 21: taskController.handleMoveTask(); break;
                    case 22: taskController.handleReadMetrics(1); break; // tempo de ciclo
                    case 23: taskController.handleReadMetrics(2); break; // ciclo medio
                    case 24: taskController.handleReadMetrics(3); break; // lead time
                    case 25: taskController.handleReadMetrics(4); break; // lead time medio
                    case 26: taskController.handleReadMetrics(5); break; // WIP

                    case 27: authController.handleLogout(); break;
                    case 0:  cout << "Encerrando o sistema. Ate logo!" << endl; break;
                    default: cout << "[AVISO] Opcao desconhecida." << endl;
                }
            }
        } catch (const std::exception& e) {
            cerr << "[ERRO CRITICO]: " << e.what() << endl;
        }

    } while (option != 0);

    return 0;
}