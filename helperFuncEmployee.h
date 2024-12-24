#pragma once

#include "Angajat.h"
#include "Manager.h"
#include "Operator.h"
#include "Asistent.h"

#include <thread>
#include <chrono>

bool validCNP(const string &CNP);
bool validName(const string &first_name, const string &second_name);
bool validID(vector <Angajat*> &employees, const string &id);
void displayIDs(vector <Angajat*> &employees);
bool isLeapYear(int year);
bool validDate(int day, int month, int year);
bool validType(const string type);
void addNewEmployee(vector <Angajat*> &employees);
void displayAllEmployees(vector <Angajat*> &employees);
void modifyEmployee(vector <Angajat*> &employees);
void deleteEmployee(vector <Angajat*> &employees);