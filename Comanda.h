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
    float packing_time;
    bool isProcessed = false;
    float timeSimulator = 0;

    public:
    Comanda() = default;
    Comanda(int, vector <Request>, float, float);
    void afisare();
    float getPackingTime();
    string getID();
    static void resetNumOrders();
    void setTimeSimulator();
    float getTimeSimulator();
    friend istream& operator>>(istream&, Comanda&);

};