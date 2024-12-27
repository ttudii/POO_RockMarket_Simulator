#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class Produs{
    protected:
    string type = "";
    const string code; //unic, asignat la angajare, nu se modifica pe perioada angajarii
    string name;
    int stock; //trebuie sa fie valid
    float base_price = 0;

    public:
    Produs() = default;
    Produs(const string, string, int, float);
    virtual void afisare();
    virtual float addShipmentTaxes() = 0;
    const string getCode();
    void displayCode();
    void setStock(int);
    int getStock();
    int getBasePrice();
    string getType();
};

