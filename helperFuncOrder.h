#pragma once

#include "helperFuncEmployee.h"
#include "helperFuncProduct.h"
#include "Comanda.h"

bool validRequest(vector <Produs*> products, const string &code, int quantity);
void displayAllOrders(vector <Comanda> &orders);
void decrementStock(vector <Produs*> &products, vector <Request> requests);
Angajat* minOrders(vector <Angajat*> employees);
Angajat* findFreeOperator(vector <Angajat*> &employees);
void removeExpiredOrders(vector <Angajat*> &employees);
void displayAllOrdersOp(vector <Angajat*> &employees);
void processFileOrder(vector <Angajat*> &employees, vector <Produs*> &products, vector <Comanda> &orders, ifstream &file);
void addNewOrder(ofstream &file);