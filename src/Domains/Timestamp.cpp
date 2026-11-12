#include "../../include/Domains/Timestamp.h"
#include <cctype>
#include <stdexcept>

namespace {
    const char* const MONTHS[12] = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
                                    "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};

    // Retorna 1 a 12 se a sigla for valida; 0 caso contrario.
    int monthFromAbbreviation(const std::string& abbreviation) {
        for (int i = 0; i < 12; ++i) {
            if (abbreviation == MONTHS[i]) return i + 1;
        }
        return 0;
    }

    // true se o texto nao e vazio e todos os caracteres sao digitos.
    bool allDigits(const std::string& text) {
        if (text.empty()) return false;
        for (size_t i = 0; i < text.length(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(text[i]))) return false;
        }
        return true;
    }
}

bool Timestamp::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Timestamp::getDaysInMonth(int month, int year) const {
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
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

void Timestamp::validate(std::string value) {
    // Formato esperado: DD-MMM-AAAA-HH:MM (ex.: 25-FEV-2026-14:30), 17 caracteres.
    if (value.length() != 17) {
        throw std::invalid_argument("Tamanho invalido. Use o formato DD-MMM-AAAA-HH:MM.");
    }

    if (value[2] != '-' || value[6] != '-' || value[11] != '-') {
        throw std::invalid_argument("Separador da data invalido. Use hifen (-).");
    }

    if (value[14] != ':') {
        throw std::invalid_argument("Separador do horario invalido. Use dois pontos (:).");
    }

    std::string sDay = value.substr(0, 2);
    std::string sMonth = value.substr(3, 3);
    std::string sYear = value.substr(7, 4);
    std::string sHour = value.substr(12, 2);
    std::string sMin = value.substr(15, 2);

    // Garante que so ha digitos antes de converter (stoi aceitaria sinais, espacos e lixo no fim).
    if (!allDigits(sDay) || !allDigits(sYear) || !allDigits(sHour) || !allDigits(sMin)) {
        throw std::invalid_argument("Dia, ano, hora e minuto devem conter apenas digitos.");
    }

    int day = std::stoi(sDay);
    int year = std::stoi(sYear);
    int hour = std::stoi(sHour);
    int minute = std::stoi(sMin);

    // Ano: 2000 a 2099.
    if (year < 2000 || year > 2099) {
        throw std::invalid_argument("Ano invalido. Deve estar entre 2000 e 2099.");
    }

    // Mes: JAN a DEZ.
    int monthNum = monthFromAbbreviation(sMonth);
    if (monthNum == 0) {
        throw std::invalid_argument("Sigla de mes invalida.");
    }

    // Dia: 1 a 31, conforme o mes e o ano (bissexto).
    int maxDays = getDaysInMonth(monthNum, year);
    if (day < 1 || day > maxDays) {
        throw std::invalid_argument("Dia invalido para o mes e ano informados.");
    }

    // Horario: 00:00 a 23:59.
    if (hour > 23 || minute > 59) {
        throw std::invalid_argument("Horario invalido. Horas de 00 a 23 e minutos de 00 a 59.");
    }
}

void Timestamp::setValue(std::string value) {
    validate(value);
    this->value = value;
}

std::string Timestamp::getValue() const {
    return value;
}

long long Timestamp::toMinutes() const {
    if (value.length() != 17) {
        throw std::logic_error("Timestamp nao definido.");
    }

    // value ja foi validado em setValue, entao o parse aqui e seguro.
    int day = std::stoi(value.substr(0, 2));
    int monthNum = monthFromAbbreviation(value.substr(3, 3));
    int year = std::stoi(value.substr(7, 4));
    int hour = std::stoi(value.substr(12, 2));
    int minute = std::stoi(value.substr(15, 2));

    long long totalDays = 0;

    // Dias dos anos completos de 2000 ate year - 1.
    for (int y = 2000; y < year; ++y) {
        totalDays += isLeapYear(y) ? 366 : 365;
    }

    // Dias dos meses completos do ano atual.
    for (int m = 1; m < monthNum; ++m) {
        totalDays += getDaysInMonth(m, year);
    }

    // Dias completos do mes atual (day - 1, porque o dia atual ainda nao fechou).
    totalDays += (day - 1);

    return totalDays * 24 * 60 + hour * 60 + minute;
}
