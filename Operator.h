#pragma once

#include "Angajat.h"
#include "Comanda.h"

class Operator : public Angajat{

    int numOrders;
    vector <Comanda> orders;
    float max_valueOrd = 0;

    public:
    Operator() = default;
    Operator(const string, string, string, const string, const string);
    void afisare();
    void calculateSalary();
    void addOrder(Comanda order);
    void resetNumOrders();
    void resetSalary();
    void displayNumOrders();
    void removeOrder();
    vector <Comanda>& getOrders();
    int getNumOrders();
    float getMaxValueOrd();
};
