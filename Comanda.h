#pragma once

#include "Request.h"
#include <ctime>

class Comanda{
    static int numOrders;
    int numRequests;
    vector <Request> requests;
    string id;
    time_t date;
    float value = 0;
    float value_taxed = 0;
    float packing_time;
    float timeSimulator = 0;

    public:
    Comanda() = default;
    Comanda(int, vector <Request>, float, float ,float);
    void afisare();
    float getPackingTime();
    string getID();
    float getValueWithTaxes();
    static void resetNumOrders();
    void setTimeSimulator();
    float getTimeSimulator();
    friend istream& operator>>(istream&, Comanda&);

};