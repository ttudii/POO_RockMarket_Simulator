#include "Request.h"

Request::Request(string code, int quantity) 
:code(code), quantity(quantity)
{}

string Request::getCode(){
    return code;
}

int Request::getQuantity(){
    return quantity;
}

istream &operator>>(istream &in, Request &request){
    in >> request.code;
    in >> request.quantity;

    return in;
}