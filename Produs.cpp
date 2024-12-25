#include "Produs.h"

int Produs::stock = 0;

Produs::Produs(const string cod, string denumire, float pret)
:code(cod),name(denumire),base_price(pret)
{
    stock++;
}

void Produs::afisare(){
    cout << endl;

    cout << "Tip: " << type << endl;
    cout << "Cod: " << code << endl;
    cout << "Denumire: " << name << endl;
    cout << "Produse de acelasi tip in stoc: " << stock << endl;
    cout << "Pret: " << base_price << " RON" << endl;
}