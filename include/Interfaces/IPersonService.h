#ifndef IPERSON_SERVICE_H
#define IPERSON_SERVICE_H

#include <vector>
#include "../Entities/Person.h"

/**
 * @brief Interface abstrata que define os serviços relacionados à entidade Person (Pessoa).
 *
 * Contém o contrato de métodos virtuais puros para gerenciar pessoas no sistema.
 */
class IPersonService {
public:
    /**
     * @brief Destrutor virtual, garante a destruição correta das implementações.
     */
    virtual ~IPersonService() {}

    /**
     * @brief Serviço 1: cria uma pessoa.
     * @param person Pessoa a ser criada.
     * @return true se foi criada, false se já existe pessoa com o mesmo e-mail.
     */
    virtual bool createPerson(const Person& person) = 0;

    /**
     * @brief Serviço 2: lê os dados de uma pessoa.
     * @param email E-mail da pessoa.
     * @return Person A pessoa encontrada.
     * @throw std::invalid_argument se a pessoa não existe.
     */
    virtual Person readPerson(const Email& email) = 0;

    /**
     * @brief Serviço 3: atualiza nome, senha e papel de uma pessoa.
     *
     * O e-mail (chave primária) não é alterado.
     *
     * @param person Pessoa com os novos dados, identificada pelo seu e-mail.
     * @return true se foi atualizada, false se a pessoa não existe.
     * @throw std::invalid_argument se o papel mudou e a pessoa ainda é gestora de
     *        projetos ou responsável por cartões.
     */
    virtual bool updatePerson(const Person& person) = 0;

    /**
     * @brief Serviço 4: exclui uma pessoa.
     * @param email E-mail da pessoa.
     * @return true se foi excluída, false se a pessoa não existe.
     * @throw std::invalid_argument se a pessoa é gestora de projetos ou responsável por cartões.
     */
    virtual bool deletePerson(const Email& email) = 0;

    /**
     * @brief Serviço 5: lista os e-mails de todas as pessoas.
     * @return Lista de e-mails.
     */
    virtual std::vector<Email> listPersons() = 0;
};

#endif
