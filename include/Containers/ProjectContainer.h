#ifndef PROJECT_CONTAINER_H
#define PROJECT_CONTAINER_H

#include <map>
#include <string>
#include <vector>
#include "../Entities/Project.h"

/**
 * @brief Contêiner que armazena objetos Project em memória, indexados por identificador.
 */
class ProjectContainer {
private:
    std::map<std::string, Project> items;

public:
    /**
     * @brief Insere um projeto.
     * @param project Projeto a ser inserido.
     * @return false se já existe projeto com o mesmo identificador.
     */
    bool insert(const Project& project) {
        return items.insert({project.getIdentifier().getValue(), project}).second;
    }

    /**
     * @brief Busca um projeto pelo identificador.
     * @param id Identificador do projeto.
     * @param out Recebe uma cópia do projeto encontrado.
     * @return true se encontrou.
     */
    bool find(const Identifier& id, Project& out) const {
        auto it = items.find(id.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    /**
     * @brief Verifica se existe um projeto com o identificador informado.
     * @param id Identificador do projeto.
     * @return true se existe.
     */
    bool exists(const Identifier& id) const {
        return items.count(id.getValue()) > 0;
    }

    /**
     * @brief Substitui os dados de um projeto existente.
     * @param project Projeto com os novos dados (identificado pelo seu identificador).
     * @return false se o projeto não existe.
     */
    bool update(const Project& project) {
        auto it = items.find(project.getIdentifier().getValue());
        if (it == items.end()) return false;
        it->second = project;
        return true;
    }

    /**
     * @brief Remove um projeto.
     * @param id Identificador do projeto.
     * @return false se o projeto não existe.
     */
    bool remove(const Identifier& id) {
        return items.erase(id.getValue()) > 0;
    }

    /**
     * @brief Obtém todos os projetos armazenados.
     * @return Cópia dos projetos, ordenados por identificador.
     */
    std::vector<Project> getAll() const {
        std::vector<Project> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }

    /**
     * @brief Obtém os projetos cujo gestor é a pessoa informada.
     * @param email E-mail do gestor.
     * @return Cópia dos projetos do gestor.
     */
    std::vector<Project> getByManager(const Email& email) const {
        std::vector<Project> result;
        for (const auto& pair : items)
            if (pair.second.getManagerEmail().getValue() == email.getValue())
                result.push_back(pair.second);
        return result;
    }
};

#endif
