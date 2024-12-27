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
    int packing_time;
    bool isProcessed = false;

    public:
    Comanda() = default;
    Comanda(int, vector <Request>, float, int);
    void afisare();
    friend istream& operator>>(istream&, Comanda&);

};