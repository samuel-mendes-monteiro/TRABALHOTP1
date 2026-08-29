#ifndef PERSON_SERVICE_H
#define PERSON_SERVICE_H

#include "../Interfaces/IPersonService.h"
#include <vector>

/**
 * @brief Classe que implementa os serviços da entidade Person.
 * 
 * Responsável pela lógica de negócio e armazenamento em memória das pessoas.
 */
class PersonService : public IPersonService {
private:
    std::vector<Person> persons; // Armazenamento temporário em memória

public:
    bool createPerson(const Person& person) override;
    Person readPerson(const Email& email) override;
    bool updatePerson(const Person& person) override;
    bool deletePerson(const Email& email) override;
};

#endif