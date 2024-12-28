#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class Angajat{
    protected:
    string type = "";
    const string ID; //unic, asignat la angajare, nu se modifica pe perioada angajarii
    string first_name; //prenume, min 3 caractere, max 30
    string last_name; //nume, min 3 caractere, max 30
    const string CNP; //trebuie sa fie valid
    const string hire_date;
    // float salary = 3500; //salariu de baza

    public:
    Angajat() = default;
    Angajat(const string, string, string, const string, const string);
    virtual void afisare();
    void displayID();
    virtual float calculateSalary() = 0;
    void validCNP();
    void validHireDate();
    int calculateSeniority();
    const string getID();
    string getName();
    string getType();
    void setLastName(const string nume);
};

