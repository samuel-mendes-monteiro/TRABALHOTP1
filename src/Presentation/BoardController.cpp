#include "../../include/Presentation/BoardController.h"
#include "../../include/Domains/Identifier.h"
#include "../../include/Domains/Name.h"
#include "../../include/Domains/Limit.h"
#include <iostream>
#include <stdexcept>

BoardController::BoardController(IBoardService* service, Session& session)
    : boardService(service), session(session) {}

void BoardController::handleListBoards() {
    std::cout << "\n--- LISTAR QUADROS ---" << std::endl;
    std::vector<Identifier> ids = boardService->listBoards();
    if (ids.empty()) { std::cout << "Nenhum quadro cadastrado." << std::endl; return; }
    for (const auto& id : ids) std::cout << id.getValue() << std::endl;
}

void BoardController::handleCreateBoard() {
    std::string idStr, nameStr, projStr;
    int limitInt = 0;

    if (!session.isManager()) {
    std::cout << "[ACESSO NEGADO] Servico restrito ao GESTOR." << std::endl;
    return;
}

    std::cout << "Digite o identificador do projeto do quadro: ";
    std::cin >> projStr;


    std::cout << "\n--- CADASTRAR QUADRO ---" << std::endl;
    std::cout << "Digite o identificador (6 caracteres, 3 letras e 3 digitos): ";
    std::cin >> idStr;
    std::cout << "Digite o nome do quadro (ate 15 caracteres): ";
    std::cin.ignore();
    std::getline(std::cin, nameStr);
    std::cout << "Digite o limite WIP (1 a 25): ";
    std::cin >> limitInt;

    try {
        Identifier identifier; identifier.setValue(idStr);
        Identifier projectId; projectId.setValue(projStr);

        Name name; name.setValue(nameStr);
        Limit limit; limit.setValue(limitInt);

        Board board;
        board.setProjectId(projectId);
        board.setIdentifier(identifier);
        board.setName(name);
        board.setLimit(limit);

        if (boardService->createBoard(board)) {
            std::cout << "[SUCESSO] Quadro cadastrado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Ja existe um quadro com este identificador." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void BoardController::handleReadBoard() {
    std::string idStr;
    std::cout << "\n--- CONSULTAR QUADRO ---" << std::endl;
    std::cout << "Digite o identificador do quadro: ";
    std::cin >> idStr;

    try {
        Identifier identifier;
        identifier.setValue(idStr);
        Board board = boardService->readBoard(identifier);

        std::cout << "[ENCONTRADO]" << std::endl;
        std::cout << "Projeto: " << board.getProjectId().getValue() << std::endl;
        std::cout << "Identificador: " << board.getIdentifier().getValue() << std::endl;
        std::cout << "Nome: " << board.getName().getValue() << std::endl;
        std::cout << "Limite WIP: " << board.getLimit().getValue() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}

void BoardController::handleUpdateBoard() {
    std::string idStr, nameStr;
    int limitInt;

    if (!session.isManager()) {
    std::cout << "[ACESSO NEGADO] Servico restrito ao GESTOR." << std::endl;
    return;
}

    std::cout << "\n--- ATUALIZAR QUADRO ---" << std::endl;
    std::cout << "Digite o identificador do quadro a ser atualizado: ";
    std::cin >> idStr;
    std::cout << "Digite o novo nome: ";
    std::cin.ignore();
    std::getline(std::cin, nameStr);
    std::cout << "Digite o novo limite WIP (1 a 25): ";
    std::cin >> limitInt;

    try {
        Identifier identifier; identifier.setValue(idStr);
        Name name; name.setValue(nameStr);
        Limit limit; limit.setValue(limitInt);

        Board board;
        board.setIdentifier(identifier);
        board.setName(name);
        board.setLimit(limit);

        if (boardService->updateBoard(board)) {
            std::cout << "[SUCESSO] Quadro atualizado com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Quadro nao encontrado para atualizacao." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO DE VALIDACAO]: " << e.what() << std::endl;
    }
}

void BoardController::handleDeleteBoard() {


    if (!session.isManager()) {
    std::cout << "[ACESSO NEGADO] Servico restrito ao GESTOR." << std::endl;
    return;
}
    std::string idStr;
    std::cout << "\n--- EXCLUIR QUADRO ---" << std::endl;
    std::cout << "Digite o identificador do quadro que deseja excluir: ";
    std::cin >> idStr;

    try {
        Identifier identifier;
        identifier.setValue(idStr);

        if (boardService->deleteBoard(identifier)) {
            std::cout << "[SUCESSO] Quadro excluido com sucesso!" << std::endl;
        } else {
            std::cout << "[ERRO] Quadro nao encontrado." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "[ERRO]: " << e.what() << std::endl;
    }
}