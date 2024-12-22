#include "Angajat.h"
#include "Manager.h"

bool validCNP(string CNP){

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

int main(){

    string CNP = "6000713233752";

    if(validCNP(CNP) == true){
        cout << "valid" << endl;
    } else {
        cout << "invalid" << endl;
    }

    Manager manager("id", "nume", "prenume", "5041208460047", "21.12.2024");

    manager.afisare();

    float manager_salary = manager.calculateSalary();

    cout << manager_salary;

    return 0;
}