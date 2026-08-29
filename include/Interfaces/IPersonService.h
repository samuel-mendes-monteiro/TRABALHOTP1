#ifndef IPERSON_SERVICE_H
#define IPERSON_SERVICE_H

#include "../Entities/Person.h"

/**
 * @brief Interface abstrata que define os serviços relacionados à entidade Person (Pessoa).
 * 
 * Contém o contrato de métodos virtuais puros para gerenciar pessoas no sistema.
 */
class IPersonService {
public:
    virtual ~IPersonService() {}

    virtual bool createPerson(const Person& person) = 0;
    virtual Person readPerson(const Email& email) = 0;
    virtual bool updatePerson(const Person& person) = 0;
    virtual bool deletePerson(const Email& email) = 0;
};

#endif