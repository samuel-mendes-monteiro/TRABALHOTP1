#include "../../include/Domains/Timestamp.h"
#include <stdexcept>

bool Timestamp::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Timestamp::getDaysInMonth(int month, int year) {
    switch (month) {
        case 1:  // JAN
        case 3:  // MAR
        case 5:  // MAI
        case 7:  // JUL
        case 8:  // AGO
        case 10: // OUT
        case 12: // DEZ
            return 31;
        case 4:  // ABR
        case 6:  // JUN
        case 9:  // SET
        case 11: // NOV
            return 30;
        case 2:  // FEV
            return isLeapYear(year) ? 29 : 28; //if isLeapYear == true return 29 else return 28
        default:
            return 0;
    }
}

void Timestamp::validate(std::string value) {
    // Formato esperado: DD-MMM-AAAA-HH:MM (Ex: 25-FEV-2026-14:30 -> 19 caracteres)
    if (value.length() != 17) {
        throw std::invalid_argument("Tamanho invalido das datas.");
    }

    if (value[2] != '-' || value[6] != '-' || value[11] != '-') {
        throw std::invalid_argument("Separador de datas deve ser um hífen ( - ).");
    }

    if (value[16] != ':') {
        throw std::invalid_argument("Separador de horas deve ser um dois pontos ( : ).");
    }

    std::string sDay = value.substr(0, 2);
    std::string sMonth = value.substr(3, 3);
    std::string sYear = value.substr(7, 4);
    std::string sHour = value.substr(12, 2);
    std::string sMin = value.substr(15, 2);

    int day, year, hour, minute;
    try {
        day = std::stoi(sDay);
        year = std::stoi(sYear);
        hour = std::stoi(sHour);
        minute = std::stoi(sMin);
    } catch (...) {
        throw std::invalid_argument("Timestamp contains non-numeric characters.");
    }

    // Validação do Ano (2000 a 2099)
    if (year < 2000 || year > 2099) {
        throw std::invalid_argument("Invalid year. Must be between 2000 and 2099.");
    }

    // Validação do Mês (JAN a DEZ)[cite: 1]
    int monthNum = 0;
    std::string months[12] = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN", "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
    for (int i = 0; i < 12; ++i) {
        if (sMonth == months[i]) {
            monthNum = i + 1;
            break;
        }
    }
    if (monthNum == 0) {
        throw std::invalid_argument("Invalid month abbreviation.");
    }

    // Validação do Dia (1 a 31, considerando o mês e ano bissexto)[cite: 1]
    int maxDays = getDaysInMonth(monthNum, year);
    if (day < 1 || day > maxDays) {
        throw std::invalid_argument("Invalid day for the specified month/year.");
    }

    // Validação do Horário (00:00 a 23:59)[cite: 1]
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        throw std::invalid_argument("Invalid time value. Hours 00-23 and minutes 00-59.");
    }
}

void Timestamp::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Timestamp::getValue() const {
    return value;
}