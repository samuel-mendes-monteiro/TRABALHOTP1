#ifndef PERSON_CONTROLLER_H
#define PERSON_CONTROLLER_H

#include "../Interfaces/IPersonService.h"

/**
 * @brief Classe controladora da camada de apresentação para gerenciar interações de Person.
 * 
 * Responsável por receber dados do usuário via interface de texto, validar as entradas
 * e acionar os serviços correspondentes através da interface IPersonService.
 */
class PersonController {
private:
    IPersonService* personService;

public:
    /**
     * @brief Construtor que recebe a referência para a interface de serviço de pessoas.
     * @param service Ponteiro para uma implementação de IPersonService.
     */
    PersonController(IPersonService* service);

    /**
     * @brief Executa o fluxo de interação para criar uma nova pessoa.
     */
    void handleCreatePerson();

    /**
     * @brief Executa o fluxo de interação para ler/consultar os dados de uma pessoa.
     */
    void handleReadPerson();

    /**
     * @brief Executa o fluxo de interação para atualizar os dados de uma pessoa.
     */
    void handleUpdatePerson();

    /**
     * @brief Executa o fluxo de interação para excluir uma pessoa.
     */
    void handleDeletePerson();
};

#endif