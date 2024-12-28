#include "helperFuncEmployee.h"
#include "helperFuncProduct.h"

#include "Comanda.h"

//TODO: add possibility to display only one employee/product
//TODO: add message that the team is incomplete
//TODO: add message that the list of products is incomplete
//TODO: add to the salary of the operator 0.5% of the total sales
//TODO: reset stock after reading from file and reset numOrders of operators

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

void decrementStock(vector <Produs*> &products, vector <Request> requests){
    for(vector <Request>::iterator it = requests.begin(); it != requests.end(); it++){
        for(vector <Produs*>::iterator iter = products.begin(); iter != products.end(); iter++){
            if((*it).getCode() == (*iter)->getCode()){
                (*iter)->setStock((*iter)->getStock() - (*it).getQuantity());
            }
        }
    }
}

Angajat* minOrders(vector <Angajat*> employees){
    auto it = min_element(employees.begin(), employees.end(), [](Angajat* a, Angajat* b) {
        if (a->getType() == "operator" && b->getType() == "operator") {
            return ((Operator*)a)->getNumOrders() < ((Operator*)b)->getNumOrders();
        }
        return false;
    });

    if (it != employees.end()) {
        return (*it);
    } else {
        return nullptr;
    }
}

Angajat* findFreeOperator(vector <Angajat*> &employees){
    Angajat* minOp = nullptr;
    for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
        if((*it)->getType() == "operator" && ((Operator*)(*it))->getOrders().size() < 3){
            if((minOp == nullptr) || (((Operator*)(*it))->getNumOrders() < ((Operator*)minOp)->getNumOrders())){
                minOp = *it;
            }
        }
    }
    return minOp;
}

void removeExpiredOrders(vector<Angajat*> &employees) {
    for (vector<Angajat*>::iterator it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getType() == "operator") {
            Operator* op = (Operator*)(*it);
            vector<Comanda>& orders = op->getOrders();

            auto new_end = std::remove_if(orders.begin(), orders.end(), [&](Comanda& order) {
                order.setTimeSimulator();
                if (order.getTimeSimulator() - order.getPackingTime() >= 0) {
                    cout << endl;
                    cout << order.getID() << " was removed by operator with ";
                    (*it)->displayID();
                    return true;
                }

                return false;
            });

            orders.erase(new_end, orders.end());
        }
    }
}

void processFileOrder(vector <Angajat*> &employees, vector <Produs*> &products, vector <Comanda> &orders, ifstream &file){

    vector <Comanda> waitList;

    Request temp;
    int numRequests;
    while (file >> numRequests){
        cout << "==============================================================================================================" << endl;
        removeExpiredOrders(employees);

        vector<Request> requests;
        int counter_disk = 0;
        int counter_clothes = 0;

        float value = 0;
        float packing_time = 0;
        cout << "\nAttempting to process order\n" << endl;
        for (int i = 0; i < numRequests; i++){
            file >> temp;
            if (validRequest(products, (const string)temp.getCode(), temp.getQuantity())){
                for (vector<Produs *>::iterator iter = products.begin(); iter != products.end(); iter++){
                    if (temp.getCode() == (string)(*iter)->getCode()){
                        value += (*iter)->getBasePrice() * temp.getQuantity();
                        if ((*iter)->getType() == "vestimentatie"){
                            counter_clothes += temp.getQuantity();
                            packing_time += 0.25 * temp.getQuantity();
                        } else {
                            counter_disk += temp.getQuantity();
                            packing_time += 0.5 * temp.getQuantity();
                        }
                    }
                }
                requests.push_back(temp);
            } else {
                cout << "Invalid code or quantity requested isn't available in stock. Order will be dropped!" << endl;
                break;
            }
        }

        if (requests.size() == numRequests){
            if (counter_disk <= 5 && counter_clothes <= 3 && value >= 100){
                orders.push_back(Comanda(numRequests, requests, value, packing_time));
                string id = orders.back().getID();
                Operator *op = (Operator*)findFreeOperator(employees);
                if(op != nullptr){
                    if(waitList.size() == 0){
                        op->addOrder(orders.back());
                        cout << id << " accepted by operator with ";
                        op->displayID();
                        // cout << "Time to pack: " << orders.back().getPackingTime() << " seconds" << endl;
                        decrementStock(products, requests);
                    } else {
                        waitList.push_back(orders.back());
                        cout << id << " will go in the wait list because another order was already waiting!" << endl;
                        op->addOrder(waitList.front());
                        cout << endl;
                        cout << waitList.front().getID() << " accepted by operator with ";
                        op->displayID();
                        waitList.erase(waitList.begin());
                    }
                } else {
                    waitList.push_back(orders.back());
                    cout << id << " was added to wait list because there are no available operators!" << endl;
                }
            } else {
                cout << "Too many products or order value is lower than 100 RON. Order will be dropped!" << endl;
            }
        }

        cout << "==============================================================================================================" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void addNewOrder(ofstream &file){
    cout << "Place order" << endl;
    cout << endl;
    Request temp;

    vector <Request> requests;

    while(true){
        cout << "Please introduce the code and the quantity of the product" << endl;
        cin >> temp;

        requests.push_back(temp);

        cout << "Do you want to add another product?(y/n)" << endl;
        string response;
        while(true){
            cin >> response;
            cout << endl;
            if(tolower(response[0]) == 'y' || tolower(response[0]) == 'n'){
                break;
            } else {
                cout << "Choose a valid answer!" << endl;
            }
        }

        if(tolower(response[0]) == 'n'){
            break;
        }
    }

    if(file << requests){
        std::this_thread::sleep_for(std::chrono::seconds(4));
        cout << "Your order was processed!" << endl;
    } else {
        cout << "Failed to process order!" << endl;
    }

}

int main(){

    vector <Angajat*> employees;
    vector <Produs*> products;
    vector <Comanda> orders;

    employees.push_back(new Manager("1", "Ion", "Popescu", "5041208460047", "24.12.2024"));
    employees.push_back(new Operator("2", "Mihai", "Ionescu", "1810915416632", "20.10.2007"));
    employees.push_back(new Operator("3", "Andrei", "Popa", "2731202139069", "20.03.2003"));
    employees.push_back(new Operator("4", "Maria", "Popescu", "5031002132668", "07.03.2024"));
    employees.push_back(new Asistent("5", "Ana", "Popescu", "6021202131077", "08.01.2023"));

    products.push_back(new Disc("cd", "20", "Disc1", 100, 30, "global", "20.10.2010", "Rock", "Pop"));
    products.push_back(new Disc("cd", "21", "Disc2", 100, 40, "global", "20.03.2007", "ceva", "ceva"));
    products.push_back(new Disc("vinil", "22", "Disc3", 100, 50, "global", "07.03.2024", "ceva", "ceva"));
    products.push_back(new Disc("vinil", "23", "Disc4", 10, 60, "global", "24.12.2024", "ceva", "ceva"));
    products.push_back(new Vintage("24", "Disc5", 100, 70, "global", "20.10.2010", "ceva", "ceva", true, 2));
    products.push_back(new Vintage("25", "Disc6", 10, 80, "global", "20.03.2007", "ceva", "ceva", false, 4));
    products.push_back(new Vestimentatie("7", "Vestimentatie1", 30, 100, "blue", "Zara"));
    products.push_back(new Vestimentatie("8", "Vestimentatie2", 30, 175, "pink", "Gucci"));

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
                    Comanda::resetNumOrders();
                    orders.clear();
                    for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
                        if((*it)->getType() == "operator"){
                            ((Operator*)(*it))->getOrders().clear();
                        }
                    }
                    ifstream file("orders.txt");

                    if (file.is_open()) {
                        processFileOrder(employees, products, orders, file);
                        file.close();
                        cout << "Press ENTER to return to the menu...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    } else {
                        cout << "Unable to open file";
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }
                } else if(response[0] == '2') {
                    system("cls");
                    ofstream file("orders.txt", ios::app);

                    if (file.is_open()) {
                        addNewOrder(file);
                        file.close();
                        cout << "Press ENTER to return to the menu...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    } else {
                        cout << "Unable to open file";
                        std::this_thread::sleep_for(std::chrono::seconds(4));
                    }


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
                } else if(response[0] == '4') {
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