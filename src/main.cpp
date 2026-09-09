#include <iostream>
#include <stdexcept>

// Includes dos Serviços Concretos (Camada de Serviço)
#include "../include/Services/PersonService.h"
#include "../include/Services/ProjectService.h"
#include "../include/Services/BoardService.h"
#include "../include/Services/TaskService.h"

// Includes dos Controladores (Camada de Apresentação)
#include "../include/Presentation/PersonController.h"
#include "../include/Presentation/ProjectController.h"
#include "../include/Presentation/BoardController.h"
#include "../include/Presentation/TaskController.h"

using namespace std;

int main() {
    // 1. Instanciação dos Serviços Concretos (Armazenamento em memória)
    PersonService personService;
    ProjectService projectService;
    BoardService boardService;
    TaskService taskService;

    // 2. Instanciação dos Controladores com Injeção de Dependência das Interfaces/Serviços
    PersonController personController(&personService);
    ProjectController projectController(&projectService);
    BoardController boardController(&boardService);
    TaskController taskController(&taskService);

    int option = 0;

    do {
        cout << "\n========================================" << endl;
        cout << "      SISTEMA DE GESTAO KANBAN (TP1)    " << endl;
        cout << "========================================" << endl;
        cout << "--- GESTAO DE PESSOAS ---" << endl;
        cout << " 1. Cadastrar Pessoa" << endl;
        cout << " 2. Consultar Pessoa" << endl;
        cout << " 3. Atualizar Pessoa" << endl;
        cout << " 4. Excluir Pessoa" << endl;
        
        cout << "\n--- GESTAO DE PROJETOS ---" << endl;
        cout << " 5. Cadastrar Projeto" << endl;
        cout << " 6. Consultar Projeto" << endl;
        cout << " 7. Atualizar Projeto" << endl;
        cout << " 8. Excluir Projeto" << endl;
        
        cout << "\n--- GESTAO DE QUADROS ---" << endl;
        cout << " 9. Cadastrar Quadro" << endl;
        cout << "10. Consultar Quadro" << endl;
        cout << "11. Atualizar Quadro" << endl;
        cout << "12. Excluir Quadro" << endl;
        
        cout << "\n--- GESTAO DE CARTOES DE ATIVIDADE ---" << endl;
        cout << "13. Cadastrar Cartao" << endl;
        cout << "14. Consultar Cartao" << endl;
        cout << "15. Atualizar Cartao" << endl;
        cout << "16. Excluir Cartao" << endl;
        cout << "17. Mover Cartao (Colunas)" << endl;
        cout << "18. Consultar Metricas (WIP)" << endl;
        
        cout << "\n 0. Sair" << endl;
        cout << "========================================" << endl;
        cout << "Escolha uma opcao: ";
        
        if (!(cin >> option)) {
            cout << "[ERRO] Entrada invalida. Tente novamente." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        try {
            switch (option) {
                case 1: personController.handleCreatePerson(); break;
                case 2: personController.handleReadPerson(); break;
                case 3: personController.handleUpdatePerson(); break;
                case 4: personController.handleDeletePerson(); break;
                
                case 5: projectController.handleCreateProject(); break;
                case 6: projectController.handleReadProject(); break;
                case 7: projectController.handleUpdateProject(); break;
                case 8: projectController.handleDeleteProject(); break;
                
                case 9: boardController.handleCreateBoard(); break;
                case 10: boardController.handleReadBoard(); break;
                case 11: boardController.handleUpdateBoard(); break;
                case 12: boardController.handleDeleteBoard(); break;
                
                case 13: taskController.handleCreateTask(); break;
                case 14: taskController.handleReadTask(); break;
                case 15: taskController.handleUpdateTask(); break;
                case 16: taskController.handleDeleteTask(); break;
                case 17: taskController.handleMoveTask(); break;
                case 18: taskController.handleReadMetrics(); break;
                
                case 0:
                    cout << "Encerrando o sistema Kanban. Ate logo!" << endl;
                    break;
                default:
                    cout << "[AVISO] Opcao desconhecida. Tente novamente." << endl;
            }
        } catch (const std::exception& e) {
            cerr << "[ERRO CRITICO]: " << e.what() << endl;
        }

    } while (option != 0);

    return 0;
}