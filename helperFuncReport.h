#pragma once

#include "helperFuncEmployee.h"
#include "helperFuncProduct.h"
#include "helperFuncOrder.h"

#include <fstream>

void generateReports(vector <Angajat*> employees, vector <Comanda> orders, ofstream &report1, ofstream &report2, ofstream &report3);