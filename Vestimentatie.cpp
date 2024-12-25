#include "Vestimentatie.h"

Vestimentatie::Vestimentatie(const string cod, string denumire, int stoc, float pret, string culoare, string marca)
:Produs(cod, denumire, stoc, pret), colour(culoare), brand(marca) {
    type = "vestimentatie";
}

float Vestimentatie::addShipmentTaxes(){
    return base_price + 20;
}

void Vestimentatie::afisare(){
    Produs::afisare();
    cout << "Culoare: " << colour << endl;
    cout << "Marca: " << brand << endl;
}