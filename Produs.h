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
    static int stock; //trebuie sa fie valid
    float base_price;

    public:
    Produs() = default;
    Produs(const string, string, float);
    virtual void afisare();
    virtual void addShipmentTaxes() = 0;
};

