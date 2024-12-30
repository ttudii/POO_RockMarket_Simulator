#pragma once

#include "Angajat.h"

class Asistent : public Angajat{

    public:
    Asistent() = default;
    Asistent(const string, string, string, const string, const string);
    void afisare();
    void calculateSalary();
};
