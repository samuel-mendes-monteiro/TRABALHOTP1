#include "../../include/Services/TaskService.h"
#include <stdexcept>

TaskService::TaskService(TaskContainer& tasks, BoardContainer& boards, PersonContainer& persons)
    : tasks(tasks), boards(boards), persons(persons) {}

bool TaskService::createTask(const Task& task) {
    if (!boards.exists(task.getBoardId()))
        throw std::invalid_argument("Quadro nao encontrado.");

    Person dev;
    if (!persons.find(task.getDeveloperEmail(), dev))
        throw std::invalid_argument("Desenvolvedor nao encontrado.");
    if (dev.getRole().getValue() != "DESENVOLVEDOR")
        throw std::invalid_argument("A pessoa atribuida ao cartao deve ter o papel DESENVOLVEDOR.");

    return tasks.insert(task);
}

Task TaskService::readTask(const Identifier& identifier) {
    Task out;
    if (!tasks.find(identifier, out)) throw std::invalid_argument("Cartao nao encontrado.");
    return out;
}

bool TaskService::updateTask(const Task& task) {
    return tasks.update(task);
}

bool TaskService::deleteTask(const Identifier& identifier) {
    return tasks.remove(identifier);
}

std::vector<Identifier> TaskService::listTasks() {
    std::vector<Identifier> result;
    for (const auto& t : tasks.getAll()) result.push_back(t.getIdentifier());
    return result;
}

bool TaskService::moveTask(const Identifier& identifier, const State& newState, const Timestamp& moveTime) {
    Task t;
    if (!tasks.find(identifier, t)) return false;

    std::string current = t.getState().getValue();
    std::string target = newState.getValue();

    if (current == "A FAZER" && target == "FAZENDO") {
        if (moveTime.toMinutes() < t.getEntryDate().toMinutes())
            throw std::invalid_argument("Horario da movimentacao anterior a data de entrada.");

        Board board;
        if (!boards.find(t.getBoardId(), board))
            throw std::invalid_argument("Quadro do cartao nao encontrado.");

        int wip = tasks.countByBoardAndState(t.getBoardId(), "FAZENDO");
        if (wip >= board.getLimit().getValue())
            throw std::invalid_argument("Limite WIP do quadro atingido.");

        t.setState(newState);
        t.setStartDate(moveTime);
        return tasks.update(t);
    }

    if (current == "FAZENDO" && target == "FEITO") {
        if (moveTime.toMinutes() < t.getStartDate().toMinutes())
            throw std::invalid_argument("Horario da movimentacao anterior ao inicio do trabalho.");

        t.setState(newState);
        t.setEndDate(moveTime);
        return tasks.update(t);
    }

    return false; // transicao invalida
}

long long TaskService::readCycleTime(const Identifier& taskId) {
    Task t = readTask(taskId);
    if (t.getState().getValue() != "FEITO")
        throw std::invalid_argument("Tempo de ciclo indisponivel: cartao ainda nao chegou em FEITO.");
    return t.getEndDate().toMinutes() - t.getStartDate().toMinutes();
}

long long TaskService::readAverageCycleTime(const Identifier& boardId) {
    long long soma = 0;
    int quantidade = 0;
    for (const auto& t : tasks.getByBoard(boardId)) {
        if (t.getState().getValue() == "FEITO") {
            soma += t.getEndDate().toMinutes() - t.getStartDate().toMinutes();
            quantidade++;
        }
    }
    if (quantidade == 0) throw std::invalid_argument("Nenhum cartao concluido neste quadro ainda.");
    return soma / quantidade;
}

long long TaskService::readLeadTime(const Identifier& taskId) {
    Task t = readTask(taskId);
    if (t.getState().getValue() != "FEITO")
        throw std::invalid_argument("Lead time indisponivel: cartao ainda nao chegou em FEITO.");
    return t.getEndDate().toMinutes() - t.getEntryDate().toMinutes();
}

long long TaskService::readAverageLeadTime(const Identifier& boardId) {
    long long soma = 0;
    int quantidade = 0;
    for (const auto& t : tasks.getByBoard(boardId)) {
        if (t.getState().getValue() == "FEITO") {
            soma += t.getEndDate().toMinutes() - t.getEntryDate().toMinutes();
            quantidade++;
        }
    }
    if (quantidade == 0) throw std::invalid_argument("Nenhum cartao concluido neste quadro ainda.");
    return soma / quantidade;
}

int TaskService::readWip(const Identifier& boardId) {
    return tasks.countByBoardAndState(boardId, "FAZENDO");
}