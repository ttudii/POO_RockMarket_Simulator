#include "Asistent.h"

float Asistent::calculateSalary(){
    int month = stoi(CNP.substr(3,2));

    time_t now = time(0);

    tm *ltm = localtime(&now);

    float salary = 0.75 * (3500 + calculateSeniority() * 100);

    if(month == ltm->tm_mon + 1){
        salary += 100;
    }

    return salary;
}

Asistent::Asistent(const string id, string prenume, string nume, const string cnp, const string data_angajare)
:Angajat(id, prenume, nume, cnp, data_angajare)
{
    type = "asistent";
}

void Asistent::afisare(){
    Angajat::afisare();
}
