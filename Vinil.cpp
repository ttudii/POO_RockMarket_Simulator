#include "Vinil.h"

Vinil::Vinil(const string cod, string denumire, float pret, const string casa_discuri, const string data, const string trupa, const string album, bool utilizat, int raritate)
:Disc("vinil", cod, denumire, pret, casa_discuri, data, trupa, album), mint(utilizat), coef_rarity(raritate)
{
    addShipmentTaxes();
}

Vinil::addShipmentTaxes(){
    Disc::addShipmentTaxes();
    base_price += (15 * coef_rarity);
}

Vinil::afisare(){
    Disc::afisare();
    cout << "Mint: " << endl;
    cout << "Coeficient de raritate" << endl;
}
