#pragma once

#include "Produs.h"

class Vestimentatie: public Produs{
    protected:
    string colour;
    string brand;
    public:
    
    Vestimentatie() = default;
    Vestimentatie(const string, string, float, string, string);
    void afisare();
    void addShipmentTaxes();
}