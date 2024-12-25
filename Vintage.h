#pragma once

#include "Disc.h"

class Vintage : public Disc{
    protected:
    bool mint;
    int coef_rarity;

    public:
    Vintage() = default;
    Vintage(const string, string, int, float, const string,const string, const string, const string, bool, int);
    void afisare();
    float addShipmentTaxes();
};