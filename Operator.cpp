#include "Operator.h"

void Operator::calculateSalary(){
    int month = stoi(CNP.substr(3,2));

    time_t now = time(0);

    tm *ltm = localtime(&now);

    salary = 3500 + calculateSeniority() * 100;

    if(month == ltm->tm_mon + 1){
        salary += 100;
    }
}

Operator::Operator(const string id, string prenume, string nume, const string cnp, const string data_angajare)
:Angajat(id, prenume, nume, cnp, data_angajare)
{
    numOrders = 0;
    calculateSalary();
    type = "operator";
}

void Operator::afisare(){
    Angajat::afisare();
}

void Operator::addOrder(Comanda order){
    numOrders++;
    orders.push_back(order);
    salary += 0.005 * order.getValueWithTaxes();

    if(order.getValueWithTaxes() > max_valueOrd){
        max_valueOrd = order.getValueWithTaxes();
    }
}

void Operator::resetNumOrders(){
    numOrders = 0;
}

void Operator::resetSalary(){
    calculateSalary();
}

void Operator::displayNumOrders(){
    cout << "Operatorul ";
    Angajat::displayID();
    cout << "a procesat " << numOrders << " comenzi" << endl;
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

float Operator::getMaxValueOrd(){
    return max_valueOrd;
}