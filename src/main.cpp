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
        std::cout << "\n========================================" << std::endl;
        std::cout << "      SISTEMA DE GESTAO KANBAN (TP1)    " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "--- GESTAO DE PESSOAS ---" << std::endl;
        std::cout << " 1. Cadastrar Pessoa" << std::endl;
        std::cout << " 2. Consultar Pessoa" << std::endl;
        std::cout << " 3. Atualizar Pessoa" << std::endl;
        std::cout << " 4. Excluir Pessoa" << std::endl;
        
        std::cout << "\n--- GESTAO DE PROJETOS ---" << std::endl;
        std::cout << " 5. Cadastrar Projeto" << std::endl;
        std::cout << " 6. Consultar Projeto" << std::endl;
        std::cout << " 7. Atualizar Projeto" << std::endl;
        std::cout << " 8. Excluir Projeto" << std::endl;
        
        std::cout << "\n--- GESTAO DE QUADROS ---" << std::endl;
        std::cout << " 9. Cadastrar Quadro" << std::endl;
        std::cout << "10. Consultar Quadro" << std::endl;
        std::cout << "11. Atualizar Quadro" << std::endl;
        std::cout << "12. Excluir Quadro" << std::endl;
        
        std::cout << "\n--- GESTAO DE CARTOES DE ATIVIDADE ---" << std::endl;
        std::cout << "13. Cadastrar Cartao" << std::endl;
        std::cout << "14. Consultar Cartao" << std::endl;
        std::cout << "15. Atualizar Cartao" << std::endl;
        std::cout << "16. Excluir Cartao" << std::endl;
        std::cout << "17. Mover Cartao (Colunas)" << std::endl;
        std::cout << "18. Consultar Metricas (WIP)" << std::endl;
        
        std::cout << "\n 0. Sair" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Escolha uma opcao: ";
        
        if (!(std::cin >> option)) {
            std::cout << "[ERRO] Entrada invalida. Tente novamente." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
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
                    std::cout << "Encerrando o sistema Kanban. Ate logo!" << std::endl;
                    break;
                default:
                    std::cout << "[AVISO] Opcao desconhecida. Tente novamente." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERRO CRITICO]: " << e.what() << std::endl;
        }

    } while (option != 0);

    return 0;
}