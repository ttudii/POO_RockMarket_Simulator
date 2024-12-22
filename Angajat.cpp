#include "Angajat.h"

Angajat::Angajat(const string id, string prenume, string nume, const string cnp, const string data_angajare)
:ID(id), first_name(prenume), second_name(nume), CNP(cnp), hire_date(data_angajare)
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
    cout << "Functie: " << type << endl;
    cout << "Id: " << ID << endl;
    cout << "Nume: " << first_name << endl;
    cout << "Prenume: " << second_name << endl;
    cout << "CNP: " << CNP << endl;
    cout << "Data angajarii: " << hire_date << endl;
}

string Angajat::getType(){
    return type;
}

