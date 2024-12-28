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

ostream &operator<<(ostream &out, vector <Request> requests){

    out << endl;
    out << requests.size() << endl;
    for(vector <Request>::iterator it = requests.begin(); it != requests.end(); it++){
        out << (*it).code << " " << (*it).quantity << endl;
    }

    return out;
}