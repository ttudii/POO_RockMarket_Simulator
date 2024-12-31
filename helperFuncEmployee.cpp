#include "helperFuncEmployee.h"

bool validCNP(const string &CNP){

    int sex = stoi(CNP.substr(0,1));
    int year = stoi(CNP.substr(1,2));
    int month = stoi(CNP.substr(3,2));
    int day = stoi(CNP.substr(5,2));
    int judet = stoi(CNP.substr(7,2));
    int number = stoi(CNP.substr(9,3));
    int c = stoi(CNP.substr(12,1));

    if (CNP.size() != 13) {
        return false;
    } else {

        if(!all_of(CNP.begin(), CNP.end(), [](unsigned char c) { return isdigit(c); })){
            return false;
        }

        if (sex != 1 && sex != 2 && sex != 5 && sex != 6 && sex != 7 && sex != 8) {
            return false;
        }

        if(sex == 1 || sex == 2){
            year += 1900;
        } else {
            year += 2000;
        }

        if(year > 2024 || year < 1900){
            return false;
        }

        if(month > 12 || month < 1){
            return false;
        }

        if(day > 31 || day < 1){
            return false;
        }

        if(!((judet <= 52 && judet != 47 || judet != 48) || judet == 70)){
            return false;
        }

        int check = 0;

        string CONST = "279146358279";

        for(int i = 0; i < CNP.size() - 1; i++){
            check = check + stoi(CNP.substr(i,1)) * stoi(CONST.substr(i,1));
        }

        check %= 11;

        if(check == 10){
            check = 1;
        }

        if(check != c){
            return false;
        }

    }

    return true; 
}

bool validName(const string &first_name, const string &second_name){
    if(first_name.size() < 3 || first_name.size() > 30)
        return false;

    if(second_name.size() < 3 || second_name.size() > 30)
        return false;

    return true;
}

bool validID(vector <Angajat*> &employees, const string &id){
    int counter = count_if(employees.begin(), employees.end(), [&id](Angajat* i){
        return (id == i->getID());
    });

    return counter == 0;
}

void displayIDs(vector <Angajat*> &employees){
    for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
        (*it)->displayID();
    }
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validDate(int day, int month, int year) {
    if (year < 1900) return false; 
    if (month < 1 || month > 12) return false;

    vector <int> daysInMonth {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    if(day < 0 || day > daysInMonth[month - 1]) return false;

    time_t now = time(0);

    tm *ltm = localtime(&now);

    ltm->tm_hour = 0;
    ltm->tm_min = 0;
    ltm->tm_sec = 0;

    tm inputDate = {};
    inputDate.tm_year = year - 1900;
    inputDate.tm_mon = month - 1;
    inputDate.tm_mday = day;
    inputDate.tm_hour = 0;
    inputDate.tm_min = 0;
    inputDate.tm_sec = 0;

    time_t inputTime = mktime(&inputDate);

    if (inputTime > now) return false;

    return true;
}

bool validType(const string type){
    if(type != "manager" && type != "operator" && type != "asistent"){
        return false;
    } else {
        return true;
    }
}

void addNewEmployee(vector <Angajat*> &employees){

    string type;
    string id;
    string first_name;
    string last_name;
    string CNP;
    string hire_date = "00.00.0000";

    cout << "Introduce the required fields for the new employee!\n\n";

    while(true){
        cout << "Please introduce the ID" << endl;
        cin >> id;
        cout << endl;

        if(validID(employees, (const string)id)){
            break;
        } else {
            cout << "The ID must be unique in the company!" << endl;
            cout << "Here is the list of unavailable id's :" << endl;
            displayIDs(employees);
        }
    }

    cout<< "Please introduce the first name" << endl;

    while(true){
        cin >> first_name;
        first_name[0] = toupper(first_name[0]);
        transform(first_name.begin() + 1, first_name.end(), first_name.begin() + 1, [](char c){
                return tolower(c);
        });
        cout << endl;
        cout<< "Please introduce the last name" << endl; 
        cin >> last_name;
        last_name[0] = toupper(last_name[0]);
        transform(last_name.begin() + 1, last_name.end(), last_name.begin() + 1, [](char c){
                return tolower(c);
        });
        cout << endl;
        
        if(validName((const string)first_name, (const string)last_name)){
            break;
        } else {
            cout << "The provided first name or last name are incorrect!" << endl;
        }
    }

    cout<< "Please introduce the CNP" << endl;

    while(true){
        cin >> CNP;
        cout << endl;

        if(validCNP((const string)CNP)){
            break;
        } else {
            cout << "The provided CNP is invalid!" << endl;
        }
    }

    int day;
    int month;
    int year;

    int CNPsex = stoi(CNP.substr(0,1));
    int CNPyear = stoi(CNP.substr(1,2));
    int CNPmonth = stoi(CNP.substr(3,2));
    int CNPday = stoi(CNP.substr(5,2));

    if(CNPsex == 1 || CNPsex == 2){
        CNPyear += 1900;
    } else {
        CNPyear += 2000;
    }

    cout << "Please introduce the date of employment" << endl;

    while(true){
        
        cout << "Day: ";
        cin >> day;
        cout << "Month: ";
        cin >> month;
        cout << "Year: ";
        cin >> year;
        cout << endl;

        if(validDate(day, month, year)){

            if (year - CNPyear < 18 || (year - CNPyear == 18 && (month < CNPmonth || (month == CNPmonth && day < CNPday)))) {
                cout << "You must have at least 18 years old!" << endl;
                continue;
            } else {
                if(day < 10){
                    hire_date.replace(1,1,to_string(day));
                } else {
                    hire_date.replace(0,2,to_string(day));
                }

                if(month < 10) {
                    hire_date.replace(4,1,to_string(month));
                } else {
                    hire_date.replace(3,2,to_string(month));
                }

                hire_date.replace(6, 4, to_string(year));

                break;
            }
        } else {
            cout << "The provided date of employment is invalid!" << endl;
        }
    }

    cout << "Please introduce the function of the employee in the company" << endl;

    while(true){
        cin >> type;
        transform(type.begin(), type.end(), type.begin(), [](char c){
            return tolower(c);
        });

        if(!validType(type)){
            cout << "This function doesn't exist in the company!" << endl;
        } else {
            if(type == "manager"){
                employees.push_back(new Manager ((const string)id, first_name, last_name, (const string)CNP, (const string)hire_date));
                break;
            } else if(type == "operator") {
                employees.push_back(new Operator ((const string)id, first_name, last_name, (const string)CNP, (const string)hire_date));
                break;
            } else if(type == "asistent") {
                employees.push_back(new Asistent ((const string)id, first_name, last_name, (const string)CNP, (const string)hire_date));         
                break;
            }
        }
    }
}

void displayAllEmployees(vector <Angajat*> &employees){
    cout << "Employees of the company:\n\n";
    for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
        (*it)->afisare();
        cout << endl;
    }
}

void modifyEmployee(vector <Angajat*> &employees){

    string new_name;
    string search_id;

    cout << "What is the id of the employee to modify?" << endl;
    while(true){
        cin >> search_id;
        cout << endl;

        if(!validID(employees, (const string)search_id)){
            break;
        } else {
            cout << "The provided ID doesn't exist in the company!" << endl;
            cout << "Here is a list of available id's :" << endl;
            displayIDs(employees);
        }
    }

    cout << "What is the new name of the employee?" << endl;
    while(true){        
        cin >> new_name;
        cout << endl;

        if(new_name.size() >= 3 && new_name.size() <= 30){
            new_name[0] = toupper(new_name[0]);
            transform(new_name.begin() + 1, new_name.end(), new_name.begin() + 1, [](char c){
                    return tolower(c);
            });
            vector <Angajat*>::iterator it;
            for (it = employees.begin(); (*it)->getID() != search_id; it++)
                ;
            if((*it)->getLastName() == new_name){
                cout << "The name provided is the same as the current name!" << endl;
                continue;
            }
            (*it)->setLastName((const string)new_name);
            cout << "Employee name modified!" << endl;
            break;
        } else {
            cout << "The name provided is incorrect!" << endl;
        }
    }
}

void deleteEmployee(vector <Angajat*> &employees){
    string search_id;

    cout << "What is the id of the employee to delete?" << endl;
    while(true){
        cin >> search_id;

        if(!validID(employees, (const string)search_id)){
            vector <Angajat*>::iterator it;
            for (it = employees.begin(); (*it)->getID() != search_id; it++)
                ;
            employees.erase(it);
            cout << "Employee deleted!" << endl;
            break;
        } else {
            cout << "The provided ID doesn't exist in the company!" << endl;
            cout << "Here is a list of available id's :" << endl;
            displayIDs(employees);
        }
    }
}

bool countEmployees(vector <Angajat*> &employees){

    int numManagers = count_if(employees.begin(), employees.end(), [](Angajat* i){
        return i->getType() == "manager";
    });

    int numOperators = count_if(employees.begin(), employees.end(), [](Angajat* i){
        return i->getType() == "operator";
    });

    int numAsistents = count_if(employees.begin(), employees.end(), [](Angajat* i){
        return i->getType() == "asistent";
    });

    if(numManagers == 0 || numOperators < 3 || numAsistents == 0){
        return false;
    } else {
        return true;
    }
}