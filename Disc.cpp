#include "Disc.h"

Disc::Disc(string tip, const string cod, string denumire, int stoc, float pret, const string casa_discuri, const string data, const string trupa, const string album)
:Produs(cod, denumire, stoc, pret), record_label(casa_discuri), date(data), band(trupa), album(album)
{
    type = tip;
}

float Disc::addShipmentTaxes(){
    return base_price + 5;
}

void Disc::afisare(){
    Produs::afisare();
    cout << "Casa de discuri: " << record_label << endl;
    cout << "Data: " << date << endl;
    cout << "Trupa: " << band << endl;
    cout << "Album: " << album << endl;
}