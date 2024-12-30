#include "Asistent.h"

void Asistent::calculateSalary(){
    int month = stoi(CNP.substr(3,2));

    time_t now = time(0);

    tm *ltm = localtime(&now);

    salary = 0.75 * (3500 + calculateSeniority() * 100);

    if(month == ltm->tm_mon + 1){
        salary += 100;
    }
}

Asistent::Asistent(const string id, string prenume, string nume, const string cnp, const string data_angajare)
:Angajat(id, prenume, nume, cnp, data_angajare)
{
    type = "asistent";
    calculateSalary();
}

void Asistent::afisare(){
    Angajat::afisare();
}
