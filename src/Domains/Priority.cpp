#include "../../include/Domains/Priority.h"
#include <stdexcept>

void Priority::validate(std::string value) {
    if (value != "ALTA" && value != "MEDIA" && value != "BAIXA") {
        throw std::invalid_argument("Invalid priority. Must be 'ALTA', 'MEDIA', or 'BAIXA'.");
    }
}

void Priority::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Priority::getValue() const {
    return value;
}