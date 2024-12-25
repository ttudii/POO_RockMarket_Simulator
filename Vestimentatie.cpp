#include "Vestimentatie.h"

Vestimentatie::Vestimentatie(const string cod, string denumire, float pret, string culoare, string marca)
:Produs(cod, denumire, pret), colour(culoare), brand(marca) {
    type = "vestimentatie";
    addShipmentTaxes();
}

void Vestimentatie::addShipmentTaxes(){
    base_price += 20;
}

void Vestimentatie::afisare(){
    Produs::afisare();
    cout << "Culoare: " << colour << endl;
    cout << "Marca: " << brand << endl;
}