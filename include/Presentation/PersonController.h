#ifndef PERSON_CONTROLLER_H
#define PERSON_CONTROLLER_H

#include "../Interfaces/IPersonService.h"
#include "Session.h"

/**
 * @brief Classe controladora da camada de apresentação para gerenciar interações de Person.
 *
 * Responsável por receber dados do usuário via interface de texto, validar as entradas
 * e acionar os serviços correspondentes através da interface IPersonService.
 */
class PersonController {
private:
    IPersonService* personService;
    Session& session;

public:
    /**
     * @brief Construtor.
     * @param service Ponteiro para uma implementação de IPersonService.
     * @param session Sessão do usuário autenticado.
     */
    PersonController(IPersonService* service, Session& session);

    /**
     * @brief Executa o fluxo de interação para criar uma nova pessoa (conta).
     */
    void handleCreatePerson();

    /**
     * @brief Lista os e-mails de todas as pessoas.
     */
    void handleListPersons();

    /**
     * @brief Executa o fluxo de interação para ler/consultar os dados de uma pessoa.
     */
    void handleReadPerson();

    /**
     * @brief Executa o fluxo de interação para atualizar os dados de uma pessoa.
     *
     * Só é permitido atualizar a própria conta.
     */
    void handleUpdatePerson();

    /**
     * @brief Executa o fluxo de interação para excluir uma pessoa.
     *
     * O GESTOR pode excluir qualquer pessoa; o DESENVOLVEDOR, apenas a própria conta.
     * Se a pessoa excluída é o próprio usuário autenticado, a sessão é encerrada.
     */
    void handleDeletePerson();
};

#endif
