#include "Comanda.h"

int Comanda::numOrders = 0;

Comanda::Comanda(int nbRequests, vector <Request> cereri, float valoare, float valoare_cu_taxe, float timp_impachetare)
:numRequests(nbRequests), requests(cereri), value(valoare), value_taxed(valoare_cu_taxe) , packing_time(timp_impachetare){
    id = "Order" + to_string(numOrders);
    numOrders++;
    time(&date);
}	

void Comanda::afisare(){

    cout << endl;

    cout << "Order ID: " << id << endl;
    cout << "Order date: " << ctime(&date);
    cout << "Order value: " << value << endl;
    cout << "Number of requests: " << numRequests << endl;
    cout << "Order requests: " << endl;
    for(vector <Request>::iterator it = requests.begin(); it != requests.end(); it++){
        cout << "Code: " << (*it).getCode() << " Quantity: " << (*it).getQuantity() << endl;
    }
    cout << "Packing time: " << packing_time << endl;
}

float Comanda::getPackingTime(){
    return packing_time;
}

string Comanda::getID(){
    return id;
}

float Comanda::getValueWithTaxes(){
    return value_taxed;
}

float Comanda::getTimeSimulator(){
    return timeSimulator;
}

void Comanda::resetNumOrders(){
    numOrders = 0;
}

void Comanda::setTimeSimulator(){
    timeSimulator += 0.1;
}

istream &operator>>(istream &in, Comanda &order){

    in >> order.numRequests;
    order.requests.clear();
    for (int i = 0; i < order.numRequests; ++i) {
        Request req;
        in >> req;
    }

    return in;
}