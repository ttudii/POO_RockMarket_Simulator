#include "helperFuncEmployee.h"
#include "helperFuncProduct.h"

//TODO: add possibility to display only one employee/product
//TODO: add message that the team is incomplete
//TODO: add message that the list of products is incomplete
//TODO: add to the salary of the operator 0.5% of the total sales
//TODO: decide on the min year on validDate

int main(){

    vector <Angajat*> employees;
    vector <Produs*> products;

    //menu
    while(true){

        system("cls");

        string response;
        cout << "Rock Market" << endl;
        cout << endl;

        cout << "1. Manage employees" << endl;
        cout << "2. Manage stock" << endl;
        cout << "3. Process orders" << endl;
        cout << "4. Reports" << endl;
        cout << "5. Exit" << endl;
        cout << endl;

        cout << "Select option: " << endl;
        while(true){
            cin >> response;
            cout << endl;

            if(response[0] != '1' && response[0] != '2' && response[0] != '3' && response[0] != '4' && response[0] != '5') {
                cout << "The option selected doesn't exist in the menu!" << endl;
            } else if(response[0] == '5'){
                return 0;
            } else {
                system("cls");
                break;
            }

        }
        
        if (response[0] == '1'){
            while(true){

                system("cls");

                cout << "Manage employees" << endl;
                cout << endl;

                cout << "1. Add employee" << endl;
                cout << "2. Modify employee" << endl;
                cout << "3. Remove employee" << endl;
                cout << "4. Display employees" << endl;
                cout << "5. Back" << endl;
                cout << endl;

                cout << "Select option: " << endl;
                while(true){
                    cin >> response;
                    cout << endl;

                    if(response[0] != '1' && response[0] != '2' && response[0] != '3' && response[0] != '4' && response[0] != '5') {
                        cout << "The option selected doesn't exist in the menu!" << endl;
                    } else {
                        break;
                    }
                }

                if(response[0] == '1'){
                    system("cls");
                    while(true){

                        addNewEmployee(employees);

                        while(true){
                            cout << "\nExit or add new employee(exit/new)"<<endl;
                            cin >> response;
                            cout << endl;
                            transform(response.begin(), response.end(), response.begin(), [](char c){
                                return tolower(c);
                            });
                            if(response == "exit" || response == "new"){
                                break;
                            } else {
                                cout << "Choose a valid answer!" << endl;
                            }
                        }

                        if(response == "exit"){
                            system("cls");
                            break;
                        } else {
                            continue;
                        }
                    }
                } else if(response[0] == '2') {
                    system("cls");
                    if(employees.size() != 0){
                        while(true){
                            modifyEmployee(employees);

                            while(true){
                                cout << "\nExit or modify another employee(exit/modify)"<<endl;
                                cin >> response;
                                cout << endl;
                                transform(response.begin(), response.end(), response.begin(), [](char c){
                                    return tolower(c);
                                });
                                if(response == "exit" || response == "modify"){
                                    break;
                                } else {
                                    cout << "Choose a valid answer!" << endl;
                                }
                            }

                            if(response == "exit"){
                                system("cls");
                                break;
                            } else {
                                continue;
                            }
                        }
                    } else {
                        cout << "You cannot modify any employee because the store is empty!" << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else if(response[0] == '3') {
                    system("cls");
                    if(employees.size() != 0){
                        while(true){
                            deleteEmployee(employees);

                            while(true){
                                cout << "\nExit or delete another employee(exit/delete)"<<endl;
                                cin >> response;
                                cout << endl;
                                transform(response.begin(), response.end(), response.begin(), [](char c){
                                    return tolower(c);
                                });
                                if(response == "exit" || response == "delete"){
                                    break;
                                } else {
                                    cout << "Choose a valid answer!" << endl;
                                }
                            }

                            if(response == "exit"){
                                system("cls");
                                break;
                            } else {
                                if(employees.size() == 0){
                                    goto employee_delete;
                                } else{
                                    continue;
                                }
                            }
                        }
                    } else {
                        employee_delete:
                        cout << "You cannot remove any employee because the store is empty!" << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else if(response[0] == '4') {
                    system("cls");
                    if(employees.size() != 0){
                        displayAllEmployees(employees);
                        cout << "Press ENTER to return to the menu...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    } else {
                        cout << "No employees to display because the store is empty!" << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else {
                    system("cls");
                    break;
                }
            }
        } else if(response[0] == '2') {
            while(true){
                system("cls");

                cout << "Manage products" << endl;
                cout << endl;

                cout << "1. Add product" << endl;
                cout << "2. Modify product" << endl;
                cout << "3. Remove product" << endl;
                cout << "4. Display products" << endl;
                cout << "5. Back" << endl;
                cout << endl;

                cout << "Select option: " << endl;
                while(true){
                    cin >> response;
                    cout << endl;

                    if(response[0] != '1' && response[0] != '2' && response[0] != '3' && response[0] != '4' && response[0] != '5') {
                        cout << "The option selected doesn't exist in the menu!" << endl;
                    } else {
                        break;
                    }
                }

                if(response[0] == '1'){
                    system("cls");
                    while(true){
                        addNewProduct(products);

                        while(true){
                            cout << "\nExit or add new product(exit/new)"<<endl;
                            cin >> response;
                            cout << endl;
                            transform(response.begin(), response.end(), response.begin(), [](char c){
                                return tolower(c);
                            });
                            if(response == "exit" || response == "new"){
                                break;
                            } else {
                                cout << "Choose a valid answer!" << endl;
                            }
                        }

                        if(response == "exit"){
                            system("cls");
                            break;
                        } else {
                                continue;
                        }
                    }
                } else if(response[0] == '2') {
                    system("cls");
                    if(products.size() != 0){
                        while(true){
                            modifyProduct(products);

                            while(true){
                                cout << "\nExit or modify another product(exit/modify)"<<endl;
                                cin >> response;
                                cout << endl;
                                transform(response.begin(), response.end(), response.begin(), [](char c){
                                    return tolower(c);
                                });
                                if(response == "exit" || response == "modify"){
                                    break;
                                } else {
                                    cout << "Choose a valid answer!" << endl;
                                }
                            }

                            if(response == "exit"){
                                system("cls");
                                break;
                            } else {
                                continue;
                            }
                        }
                    } else {
                        cout << "You cannot modify any product because the list is empty!" << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else if(response[0] == '3') {
                    system("cls");
                    if(products.size() != 0){
                        while(true){
                            deleteProduct(products);

                            while(true){
                                cout << "\nExit or delete another product(exit/delete)"<<endl;
                                cin >> response;
                                cout << endl;
                                transform(response.begin(), response.end(), response.begin(), [](char c){
                                    return tolower(c);
                                });
                                if(response == "exit" || response == "delete"){
                                    break;
                                } else {
                                    cout << "Choose a valid answer!" << endl;
                                }
                            }

                            if(response == "exit"){
                                system("cls");
                                break;
                            } else {
                                if(employees.size() == 0){
                                    goto product_delete;
                                } else{
                                    continue;
                                }
                            }
                        }
                    } else {
                        product_delete:
                        cout << "You cannot remove any product because the list is empty!" << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else if(response[0] == '4') {
                    system("cls");
                    if(products.size() != 0){
                        displayAllProducts(products);
                        cout << "Press ENTER to return to the menu...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    } else {
                        cout << "No products to display because the list of products is empty!" << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else {
                    system("cls");
                    break;
                }
            }
        } else if(response[0] == '3') {
            return 0;
        } else {
        return 0;
        }
    }
    return 0;
}