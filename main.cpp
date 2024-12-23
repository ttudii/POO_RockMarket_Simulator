#include "Angajat.h"
#include "Manager.h"

//TODO: verify if the employee is older than 18 and younger than 70
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

//TODO: verify that the date is lower than the current localtime and higher than the date of birth and has proper aspect (DD.MM.YYYY)
bool validDate(const string date){
    return true;
}

bool validType(const string type){
    if(type != "manager" && type != "operator comenzi" && type != "asistent"){
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
    string hire_date;

    cout << "Introduce the required fields for the new employee!\n\n";

    while(true){
        cout << "Please introduce the ID" << endl;
        cin >> id;

        if(validID(employees, (const string)id)){
            break;
        } else {
            cout << "The ID must be unique in the company!" << endl;
        }
    }

    while(true){
        cout<< "Please introduce the first name" << endl;
        cin >> first_name;
        cout << endl;
        cout<< "Please introduce the last name" << endl; 
        cin >> last_name;
        cout << endl;
        
        if(validName((const string)first_name, (const string)last_name)){
            break;
        } else {
            //throw error or message?
            cout << "The provided first name or last name are incorrect!" << endl;
        }
    }

    while(true){
        cout<< "Please introduce the CNP" << endl;
        cin >> CNP;

        if(validCNP((const string)CNP)){
            break;
        } else {
            cout << "The provided CNP is invalid!" << endl;
        }
    }

    while(true){
        cout<< "Please introduce the date of employment" << endl;
        cin >> hire_date;

        if(validDate(hire_date)){
            break;
        } else {
            cout << "The provided date of employment is invalid!" << endl;
        }
    }

    while(true){
        cout << "Please introduce the function of the employee in the company" << endl;
        cin >> type;

        if(!validType(type)){
            cout << "This function doesn't exist in the company!" << endl;
        } else {
            if(type == "manager"){
                employees.push_back(new Manager ((const string)id, first_name, last_name, (const string)CNP, (const string)hire_date));
                break;
            } else if(type == "operator comenzi") {
                // employees.push_back(new OperatorComenzi (id, first_name, last_name, CNP, hire_date));
                break;
            } else if(type == "asistent") {
                // employees.push_back(new Asistent (id, first_name, last_name, CNP, hire_date));         
                break;
            }
        }
    }
}

void displayAllEmployees(vector <Angajat*> &employees){
    for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
        (*it)->afisare();
    }
}

//TODO: add OperatorComenzi and Asistent classes
//TODO: create Menu
//TODO: add modify employee and delete employee functions
//TODO: add display salary functions for all employees
//TODO: modify added data to a standard format (name: Aaaaa, date: DD.MM.YYYY, type: Aaaaa)

int main(){

    vector <Angajat*> employees;

    char res;

    while(true){
        cout << "Add a new employee?(y/n)"<<endl;
        cin >> res;
        if(tolower(res) == 'y' || tolower(res) == 'n'){
            break;
        } else {
            cout << "Choose a valid answer!" << endl;
        }
    }

    if(tolower(res) == 'y'){
        addNewEmployee(employees);
    }

    displayAllEmployees(employees);

    return 0;
}