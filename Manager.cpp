#include "Manager.h"

void Manager::calculateSalary(){
    salary = 1.25 * (3500 + calculateSeniority() * 100);
}

Manager::Manager(const string id, string prenume, string nume, const string cnp, const string data_angajare)
:Angajat(id, prenume, nume, cnp, data_angajare)
{
    type = "manager";
    calculateSalary();
}

void Manager::afisare(){
    Angajat::afisare();
}
