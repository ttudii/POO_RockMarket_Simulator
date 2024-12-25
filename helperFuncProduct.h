#pragma once

#include "Produs.h"
#include "Vestimentatie.h"
#include "Disc.h"
#include "Vintage.h"

bool validCode(vector <Produs*> &products, const string &code);
bool validColour(const string colour);
void displayAllProducts(vector <Produs*> &products);
void displayAllCodes(vector <Produs*> &products);
void addNewProduct(vector <Produs*> &products);
void modifyProduct(vector <Produs*> &products);
void deleteProduct(vector <Produs*> &products);