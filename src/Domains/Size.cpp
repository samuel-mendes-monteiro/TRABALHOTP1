#include "../../include/Domains/Size.h"
#include <stdexcept>

void Size::validate(std::string value) {
    if (value != "GRANDE" && value != "MEDIO" && value != "PEQUENO") {
        throw std::invalid_argument("Invalid size. Must be 'GRANDE', 'MEDIO', or 'PEQUENO'.");
    }
}

void Size::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Size::getValue() const {
    return value;
}