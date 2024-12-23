#include "Angajat.h"

Angajat::Angajat(const string id, string prenume, string nume, const string cnp, const string data_angajare)
:ID(id), first_name(prenume), last_name(nume), CNP(cnp), hire_date(data_angajare)
{}

int Angajat::calculateSeniority(){
    int day = stoi(hire_date.substr(0,2));
    int month = stoi(hire_date.substr(3,2));
    int year = stoi(hire_date.substr(6,4));

    time_t now = time(0);

    tm *ltm = localtime(&now);

    if(ltm->tm_year + 1900 == year){
        return 0;
    }

    int seniority = ltm->tm_year + 1900 - year;

    if (month > ltm->tm_mon + 1) {
        return seniority - 1;
    } else if (month == ltm->tm_mon + 1) {
        if(day > ltm->tm_mday) {
            return seniority - 1;
        }
    }

    return seniority;
}

void Angajat::afisare(){
    cout << endl;

    cout << "Functie: " << type << endl;
    cout << "Id: " << ID << endl;
    cout << "Nume: " << first_name << endl;
    cout << "Prenume: " << last_name << endl;
    cout << "CNP: " << CNP << endl;
    cout << "Data angajarii: " << hire_date << endl;

    float salary = calculateSalary();

    time_t now = time(0);

    tm *ltm = localtime(&now);

    cout << "Salariu luna " << ltm->tm_mon + 1 << ", " << ltm->tm_year + 1900 << ": " << salary << endl;
}

const string Angajat::getID(){
    return ID;
}

void Angajat::setLastName(const string nume){
    last_name = nume;
}

