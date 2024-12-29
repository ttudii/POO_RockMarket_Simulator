#pragma once

#include "Angajat.h"
#include "Comanda.h"

class Operator : public Angajat{

    int numOrders;
    vector <Comanda> orders;

    public:
    Operator() = default;
    Operator(const string, string, string, const string, const string);
    void afisare();
    float calculateSalary();
    void addOrder(Comanda order);
    void resetNumOrders();
    void displayNumOrders();
    void removeOrder();
    vector <Comanda>& getOrders();
    int getNumOrders();
};
