#ifndef TASK_CONTAINER_H
#define TASK_CONTAINER_H

#include <map>
#include <string>
#include <vector>
#include "../Entities/Task.h"

/**
 * @brief Contêiner que armazena objetos Task em memória, indexados por identificador.
 */
class TaskContainer {
private:
    std::map<std::string, Task> items;

public:
    /**
     * @brief Insere um cartão.
     * @param task Cartão a ser inserido.
     * @return false se já existe cartão com o mesmo identificador.
     */
    bool insert(const Task& task) {
        return items.insert({task.getIdentifier().getValue(), task}).second;
    }

    /**
     * @brief Busca um cartão pelo identificador.
     * @param id Identificador do cartão.
     * @param out Recebe uma cópia do cartão encontrado.
     * @return true se encontrou.
     */
    bool find(const Identifier& id, Task& out) const {
        auto it = items.find(id.getValue());
        if (it == items.end()) return false;
        out = it->second;
        return true;
    }

    /**
     * @brief Verifica se existe um cartão com o identificador informado.
     * @param id Identificador do cartão.
     * @return true se existe.
     */
    bool exists(const Identifier& id) const {
        return items.count(id.getValue()) > 0;
    }

    /**
     * @brief Substitui os dados de um cartão existente.
     * @param task Cartão com os novos dados (identificado pelo seu identificador).
     * @return false se o cartão não existe.
     */
    bool update(const Task& task) {
        auto it = items.find(task.getIdentifier().getValue());
        if (it == items.end()) return false;
        it->second = task;
        return true;
    }

    /**
     * @brief Remove um cartão.
     * @param id Identificador do cartão.
     * @return false se o cartão não existe.
     */
    bool remove(const Identifier& id) {
        return items.erase(id.getValue()) > 0;
    }

    /**
     * @brief Obtém todos os cartões armazenados.
     * @return Cópia dos cartões, ordenados por identificador.
     */
    std::vector<Task> getAll() const {
        std::vector<Task> result;
        for (const auto& pair : items) result.push_back(pair.second);
        return result;
    }

    /**
     * @brief Obtém os cartões de um quadro.
     * @param boardId Identificador do quadro.
     * @return Cópia dos cartões do quadro.
     */
    std::vector<Task> getByBoard(const Identifier& boardId) const {
        std::vector<Task> result;
        for (const auto& pair : items)
            if (pair.second.getBoardId().getValue() == boardId.getValue())
                result.push_back(pair.second);
        return result;
    }

    /**
     * @brief Obtém os cartões atribuídos a um desenvolvedor.
     * @param email E-mail do desenvolvedor.
     * @return Cópia dos cartões do desenvolvedor.
     */
    std::vector<Task> getByDeveloper(const Email& email) const {
        std::vector<Task> result;
        for (const auto& pair : items)
            if (pair.second.getDeveloperEmail().getValue() == email.getValue())
                result.push_back(pair.second);
        return result;
    }

    /**
     * @brief Conta os cartões de um quadro em determinado estado (base do WIP).
     * @param boardId Identificador do quadro.
     * @param state Estado a contar (A FAZER, FAZENDO ou FEITO).
     * @return Quantidade de cartões do quadro nesse estado.
     */
    int countByBoardAndState(const Identifier& boardId, const std::string& state) const {
        int count = 0;
        for (const auto& pair : items)
            if (pair.second.getBoardId().getValue() == boardId.getValue() &&
                pair.second.getState().getValue() == state)
                count++;
        return count;
    }
};

#endif
