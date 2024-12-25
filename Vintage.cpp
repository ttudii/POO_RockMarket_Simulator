#include "Vintage.h"

Vintage::Vintage(const string cod, string denumire, int stoc, float pret, const string casa_discuri, const string data, const string trupa, const string album, bool utilizat, int raritate)
:Disc("vintage", cod, denumire, stoc, pret, casa_discuri, data, trupa, album), mint(utilizat), coef_rarity(raritate)
{}

float Vintage::addShipmentTaxes(){
    float price = Disc::addShipmentTaxes();
    return price + (15 * coef_rarity);
}

void Vintage::afisare(){
    Disc::afisare();
    cout << "Mint: " << boolalpha << mint << endl;
    cout << "Coeficient de raritate: " << coef_rarity << endl;
}
