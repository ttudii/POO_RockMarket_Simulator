#pragma once

#include "Request.h"
#include <ctime>

class Comanda{
    static int numOrders;
    int numRequests;
    vector <Request> requests;
    string id;
    time_t date;
    float value;
    int packing_time;
    bool isProcessed = false;

    public:
    Comanda() = default;
    Comanda(const Comanda&);
    void afisare();
    void setFields();
    friend istream& operator>>(istream&, Comanda&);

};