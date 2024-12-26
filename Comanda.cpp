#include "Comanda.h"

int Comanda::numOrders = 0;

Comanda::Comanda(const Comanda& order){
    id = order.id;
    date = order.date;
    value = order.value;
    requests = order.requests;
    packing_time = order.packing_time;
    isProcessed = order.isProcessed;
}

void Comanda::afisare(){

    cout << endl;

    cout << "Order ID: " << id << endl;
    cout << "Order date: " << ctime(&date);
    cout << "Order value: " << value << endl;
    cout << "Order requests: " << numRequests << endl;
    for(auto i : requests){
        cout << "Code: " << i.getCode() << " Quantity: " << i.getQuantity() << endl;
    }
    cout << "Packing time: " << packing_time << endl;
    cout << "Is processed: " << boolalpha << isProcessed << endl;
}

void Comanda::setFields(){
    id = "Order" + to_string(numOrders);
    numOrders++;
    time(&date);
    value = 0;
    for(auto i : requests){
        value += i.getQuantity();
    }
    packing_time = requests.size() * 2;
    isProcessed = false;
}

istream &operator>>(istream &in, Comanda &order){

    in >> order.numRequests;
    order.requests.clear();
    for (int i = 0; i < order.numRequests; ++i) {
        Request req;
        in >> req;
        order.requests.push_back(req);
    }

    return in;
}