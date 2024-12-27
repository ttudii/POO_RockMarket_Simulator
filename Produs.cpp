#include "Produs.h"

// int Produs::stock = 0;

Produs::Produs(const string cod, string denumire, int stoc, float pret)
:code(cod),name(denumire),stock(stoc), base_price(pret)
{}

void Produs::afisare(){
    cout << endl;

    cout << "Tip: " << type << endl;
    cout << "Cod: " << code << endl;
    cout << "Denumire: " << name << endl;
    cout << "Produse de acelasi tip in stoc: " << stock << endl;
    cout << "Pret initial: " << base_price << " RON" << endl;

    float price = addShipmentTaxes();

    cout << "Pret cu taxe de transport: " << price << " RON" << endl;
}

void Produs::displayCode(){
    cout << "Cod: " << code << " ";
    cout << "Denumire: " << name << endl;
}

const string Produs::getCode(){
    return code;
}

int Produs::getStock(){
    return stock;
}

void Produs::setStock(int new_stock){
    stock = new_stock;
}

int Produs::getBasePrice(){
    return base_price;
}

string Produs::getType(){
    return type;
}