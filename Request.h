#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Request {
    string code;
    int quantity;

    public:
    Request() = default;
    Request(string, int);
    string getCode();
    int getQuantity();
    friend istream& operator>>(istream&, Request&);
    friend ostream& operator<<(ostream &, vector <Request>);
};