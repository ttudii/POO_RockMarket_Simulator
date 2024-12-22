#pragma once

#include <iostream>
#include <string>
#include "Angajat.h"

using namespace std;

class Manager : public Angajat{

    public:
    Manager() = default;
    Manager(const string, string, string, const string, const string);
    void afisare();
    float calculateSalary();
};

