#include "helperFuncEmployee.h"
#include "helperFuncProduct.h"

#include "Comanda.h"

//TODO: add possibility to display only one employee/product
//TODO: add message that the team is incomplete
//TODO: add message that the list of products is incomplete
//TODO: add to the salary of the operator 0.5% of the total sales
//TODO: finish processFileOrder function
//TODO: implement simulation of adding orders to operators
//TODO: add some employees and products from the start

bool validRequest(vector <Produs*> products, const string &code, int quantity){
    for(vector <Produs*>::iterator it = products.begin(); it != products.end(); it++){
        if(code == (*it)->getCode()){
            if(quantity <= (*it)->getStock()){
                return true;
            }
        }
    }

    return false;
}

void displayAllOrders(vector <Comanda> &orders){
    for(vector <Comanda>::iterator it = orders.begin(); it != orders.end(); it++){
        (*it).afisare();
    }
}

void processFileOrder(vector <Angajat*> &employees, vector <Produs*> &products, vector <Comanda> &orders, ifstream &file){
    Request temp;
    int numRequests;
    int counter = 0;
    while (file >> numRequests){
        vector<Request> requests;
        int counter_disk = 0;
        int counter_clothes = 0;

        float value = 0;
        int packing_time = 0;

        cout << "Attempting to process Order " << counter++ << endl;
        for (int i = 0; i < numRequests; i++){
            file >> temp;
            if (validRequest(products, (const string)temp.getCode(), temp.getQuantity())){
                for (vector<Produs *>::iterator iter = products.begin(); iter != products.end(); iter++){
                    if (temp.getCode() == (string)(*iter)->getCode()){
                        value += (*iter)->getBasePrice() * temp.getQuantity();
                        if ((*iter)->getType() == "vestimentatie"){
                            counter_clothes += temp.getQuantity();
                            packing_time += 2 * temp.getQuantity();
                        } else {
                            counter_disk += temp.getQuantity();
                            packing_time += 4 * temp.getQuantity();
                        }
                    }
                }
                requests.push_back(temp);
            } else {
                cout << "Invalid code or quantity requested isn't available in stock. Order will be dropped!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
                break;
            }
        }

        if (requests.size() == numRequests){
            if (counter_disk <= 5 && counter_clothes <= 3 && value >= 100){
                // seachFreeEmployee(employees, temp.packing_time);
                // addToWaitingList();
                orders.push_back(Comanda(numRequests, requests, value, packing_time));
                cout << "Order processed!" << endl;
                // decrementStock(products, temp.getCode(), temp.getQuantity());
                std::this_thread::sleep_for(std::chrono::seconds(4));
            } else {
                cout << "Too many products or order value is lower than 100 RON. Order will be dropped!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
                // dropOrder();
            }
        }
    }
    file.close();
}

int main(){

    vector <Angajat*> employees;
    vector <Produs*> products;
    vector <Comanda> orders;

    // //menu
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
            while(true){
                system("cls");

                cout << "Process orders" << endl;
                cout << endl;

                cout << "1. Read orders from file" << endl;
                cout << "2. Place order" << endl;
                cout << "3. Display orders" << endl;
                cout << "4. Back" << endl;
                cout << endl;

                cout << "Select option: " << endl;
                while(true){
                    cin >> response;
                    cout << endl;

                    if(response[0] != '1' && response[0] != '2' && response[0] != '3' && response[0] != '4') {
                        cout << "The option selected doesn't exist in the menu!" << endl;
                    } else {
                        break;
                    }
                }

                if(response[0] == '1'){
                    system("cls");
                    ifstream file("orders.txt");

                    if (file.is_open()) {
                        processFileOrder(employees, products, orders, file);
                        cout << "Press ENTER to return to the menu...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    } else {
                        cout << "Unable to open file";
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else if(response[0] == '2') {
                    system("cls");
                    cout << "Place order" << endl;
                    cout << endl;
                    cout << "\nPress ENTER to return to the menu...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();

                }else if(response[0] == '3'){
                    system("cls");
                        if(orders.size() != 0){
                            displayAllOrders(orders);
                            cout << "\nPress ENTER to return to the menu...";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.get();
                        } else {
                            cout << "No orders to display because the list of orders is empty!" << endl;
                            std::this_thread::sleep_for(std::chrono::seconds(4));
                        }
                } else {
                    system("cls");
                    break;
                }
            }

        } else {
        return 0;
        }
    }

    return 0;
}