#pragma once

#include "Angajat.h"

class Manager : public Angajat{

    public:
    Manager() = default;
    Manager(const string, string, string, const string, const string);
    void afisare();
    float calculateSalary();
};
