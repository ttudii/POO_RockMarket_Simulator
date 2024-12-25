#pragma once

#include "Produs.h"

class Disc: public Produs{
    protected:
    const string record_label;
    const string date;
    const string band;
    const string album;
    
    public:
    Disc() = default;
    Disc(string, const string, string, int, float,const string,const string, const string, const string);
    void afisare();
    float addShipmentTaxes();
};