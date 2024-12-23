#pragma once

#include "Angajat.h"

class Operator : public Angajat{

    public:
    Operator() = default;
    Operator(const string, string, string, const string, const string);
    void afisare();
    float calculateSalary();
};
