#pragma once

#include "Disc.h"

class Vinil : public Disc{
    protected:
    bool mint;
    int coef_rarity;

    public:
    Vinil() = default;
    Vinil(const string, string, float,const string,const string, const string, const string, bool, int);
    void afisare();
    void addShipmentTaxes();
}