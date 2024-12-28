#include "Operator.h"

float Operator::calculateSalary(){
    int month = stoi(CNP.substr(3,2));

    time_t now = time(0);

    tm *ltm = localtime(&now);

    float salary = 3500 + calculateSeniority() * 100;

    if(month == ltm->tm_mon + 1){
        salary += 100;
    }

    return salary;
}

Operator::Operator(const string id, string prenume, string nume, const string cnp, const string data_angajare)
:Angajat(id, prenume, nume, cnp, data_angajare)
{
    numOrders = 0;
    type = "operator";
}

void Operator::afisare(){
    Angajat::afisare();
}

void Operator::addOrder(Comanda order){
    numOrders++;
    orders.push_back(order);
}

void Operator::removeOrder(){
    orders.pop_back();
}

vector <Comanda>& Operator::getOrders(){
    return orders;
}

int Operator::getNumOrders(){
    return numOrders;
}