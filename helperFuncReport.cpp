#include "helperFuncReport.h"

void generateReports(vector <Angajat*> employees, vector <Comanda> orders, ofstream &report1, ofstream &report2, ofstream &report3){
    vector <Operator*> operators;
    for(Angajat* it : employees){
        if(it->getType() == "operator"){
            Operator* op = (Operator*)it;
            operators.push_back(op);
        }
    }

    if(!operators.empty()){
        auto max_numOrd = max_element(operators.begin(), operators.end(), [](Operator* a, Operator* b) {
            return a->getNumOrders() < b->getNumOrders();
        });

        Operator *op = (Operator*)*max_numOrd;

        report1 << "ID,Name,Number of orders" << endl;

        report1 << op->getID() << ","
        << op->getFirstName() << " " << op->getLastName() << ","
        << op->getNumOrders() << endl;
    }

    if(!operators.empty()){
        sort(operators.begin(), operators.end(), [](Operator* a, Operator* b) {
            return a->getMaxValueOrd() > b->getMaxValueOrd();
        });

        report2 << "ID,Name,Max value of an order" << endl;

        for(vector<Operator*>::iterator it = operators.begin(); it != operators.begin() + 3; it++){
            report2 << (*it)->getID() << ","
            << (*it)->getFirstName() << " " << (*it)->getLastName() << ","
            << (*it)->getMaxValueOrd() << endl;
        }
    }

    vector <Angajat*> copy_employees = employees;

    sort(copy_employees.begin(), copy_employees.end(), [](Angajat* a, Angajat* b) {
        return a->getSalary() > b->getSalary();
    });

    vector<Angajat*> top3_employees(copy_employees.begin(), copy_employees.begin() + 3);

    sort(top3_employees.begin(), top3_employees.end(), [](Angajat* a, Angajat* b) {
            if(a->getLastName() == b->getLastName()){
                return a->getFirstName() < b->getFirstName();
            }
            
            return a->getLastName() < b->getLastName();
    });

    report3 << "ID,Name,Salary" << endl;

    for(vector<Angajat*>::iterator it = top3_employees.begin(); it != top3_employees.end(); it++){

        report3 << (*it)->getID() << ","
        << (*it)->getType() << ","
        << (*it)->getFirstName() << " " << (*it)->getLastName() << ","
        << (*it)->getSalary() << endl;
    }
}
