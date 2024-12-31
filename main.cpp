#include "helperFuncEmployee.h"
#include "helperFuncProduct.h"
#include "helperFuncOrder.h"
#include "helperFuncReport.h"

int main(){

    vector <Angajat*> employees;
    vector <Produs*> products;
    vector <Comanda> orders;

    std::unique_ptr<Manager> manager(new Manager("1", "Ion", "Setescu", "1500126130407", "24.12.2002"));
    std::unique_ptr<Operator> operator1(new Operator("2", "Tudor", "Lungescu", "1810915416632", "20.10.2007"));
    std::unique_ptr<Operator> operator2(new Operator("3", "Andrei", "Popa", "2731202139069", "20.03.2003"));
    std::unique_ptr<Operator> operator3(new Operator("4", "Luca", "Camliescu", "5031002132668", "07.03.2024"));
    std::unique_ptr<Asistent> asistent(new Asistent("5", "Ana", "Mancacescu", "6021202131077", "08.01.2023"));

    employees.push_back(manager.get());
    employees.push_back(operator1.get());
    employees.push_back(operator2.get());
    employees.push_back(operator3.get());
    employees.push_back(asistent.get());

    std::unique_ptr<Disc> disc1(new Disc("cd", "20", "Disc1", 100, 30, "global", "20.10.2010", "Rock", "Pop"));
    std::unique_ptr<Disc> disc2(new Disc("cd", "21", "Disc2", 100, 40, "global", "20.03.2007", "ceva", "ceva"));
    std::unique_ptr<Disc> disc3(new Disc("vinil", "22", "Disc3", 100, 50, "global", "07.03.2024", "ceva", "ceva"));
    std::unique_ptr<Disc> disc4(new Disc("vinil", "23", "Disc4", 10, 60, "global", "24.12.2024", "ceva", "ceva"));
    std::unique_ptr<Vintage> vintage1(new Vintage("24", "Disc5", 100, 70, "global", "20.10.2010", "ceva", "ceva", true, 2));
    std::unique_ptr<Vintage> vintage2(new Vintage("25", "Disc6", 10, 80, "global", "20.03.2007", "ceva", "ceva", false, 4));
    std::unique_ptr<Vestimentatie> vest1(new Vestimentatie("7", "Vestimentatie1", 30, 100, "blue", "Zara"));
    std::unique_ptr<Vestimentatie> vest2(new Vestimentatie("8", "Vestimentatie2", 30, 175, "pink", "Gucci"));

    products.push_back(disc1.get());
    products.push_back(disc2.get());
    products.push_back(disc3.get());
    products.push_back(disc4.get());
    products.push_back(vintage1.get());
    products.push_back(vintage2.get());
    products.push_back(vest1.get());
    products.push_back(vest2.get());

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

            if(response != "1" && response != "2" && response != "3" && response != "4" && response != "5") {
                cout << "The option selected doesn't exist in the menu!" << endl;
            } else if(response == "5"){
                return 0;
            } else {
                system("cls");
                break;
            }

        }
        
        if (response == "1"){
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

                    if(response != "1" && response != "2" && response != "3" && response != "4" && response != "5") {
                        cout << "The option selected doesn't exist in the menu!" << endl;
                    } else {
                        break;
                    }
                }

                if(response == "1"){
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
                } else if(response == "2") {
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
                        this_thread::sleep_for(chrono::seconds(4));
                    }
                } else if(response == "3") {
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
                        this_thread::sleep_for(chrono::seconds(4));
                    }
                } else if(response == "4") {
                    if(employees.size() != 0){
                        while(true){
                            system("cls");

                            cout << "Display options" << endl;
                            cout << endl;

                            cout << "1. Display employee" << endl;
                            cout << "2. Display all employees" << endl;
                            cout << "3. Back" << endl;
                            cout << endl;

                            cout << "Select option: " << endl;

                            while(true){
                                cin >> response;
                                cout << endl;

                                if(response != "1" && response != "2" && response != "3") {
                                    cout << "The option selected doesn't exist in the menu!" << endl;
                                } else {
                                    break;
                                }
                            }

                            if(response == "1"){
                                system("cls");
                                while(true){
                                    string search_id;

                                    cout << "\nEnter the ID of the employee you want to display: ";
                                    cin >> search_id;
                                    cout << endl;

                                    if(!validID(employees, search_id)){
                                        for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
                                            if((*it)->getID() == search_id){
                                                (*it)->afisare();
                                                cout << endl;
                                                break;
                                            }
                                        }
                                        cout << "Press ENTER to return to the menu...";
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cin.get();
                                        break;
                                    } else {
                                        cout << "The ID entered doesn't exist in the list of employees!" << endl;
                                        cout << "Here are the IDs of the employees: " << endl;
                                        displayIDs(employees);
                                    }
                                }
                            } else if(response == "2"){
                                system("cls");
                                displayAllEmployees(employees);
                                cout << "Press ENTER to return to the menu...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                            } else {
                                system("cls");
                                break;
                            }
                        }
                    } else {
                        cout << "No employees to display because the store is empty!" << endl;
                        this_thread::sleep_for(chrono::seconds(4));
                    }
                } else {
                    system("cls");
                    break;
                }
            }
        } else if(response == "2") {
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

                    if(response != "1" && response != "2" && response != "3" && response != "4" && response != "5") {
                        cout << "The option selected doesn't exist in the menu!" << endl;
                    } else {
                        break;
                    }
                }

                if(response == "1"){
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
                } else if(response == "2") {
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
                        this_thread::sleep_for(chrono::seconds(4));
                    }
                } else if(response == "3") {
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
                        this_thread::sleep_for(chrono::seconds(4));
                    }
                } else if(response == "4") {
                    if(products.size() != 0){
                        while(true){
                            system("cls");

                            cout << "Display options" << endl;
                            cout << endl;

                            cout << "1. Display product" << endl;
                            cout << "2. Display all products" << endl;
                            cout << "3. Back" << endl;
                            cout << endl;

                            cout << "Select option: " << endl;

                            while(true){
                                cin >> response;
                                cout << endl;

                                if(response != "1" && response != "2" && response != "3") {
                                    cout << "The option selected doesn't exist in the menu!" << endl;
                                } else {
                                    break;
                                }
                            }

                            if(response == "1"){
                                system("cls");
                                while(true){
                                    string search_code;

                                    cout << "\nEnter the code of the product you want to display: ";
                                    cin >> search_code;
                                    cout << endl;

                                    if(!validCode(products, search_code)){
                                        for(vector <Produs*>::iterator it = products.begin(); it != products.end(); it++){
                                            if((*it)->getCode() == search_code){
                                                (*it)->afisare();
                                                cout << endl; 
                                                break;
                                            }
                                        }
                                        cout << "Press ENTER to return to the menu...";
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cin.get();
                                        break;
                                    } else {
                                        cout << "The code entered doesn't exist in the list of products!" << endl;
                                        cout << "Here are the IDs of the employees: " << endl;
                                        displayAllCodes(products);
                                    }
                                }
                            } else if(response == "2"){
                                system("cls");
                                displayAllProducts(products);
                                cout << "Press ENTER to return to the menu...";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin.get();
                            } else {
                                system("cls");
                                break;
                            }
                        }
                    } else {
                        cout << "No products to display because the list of products is empty!" << endl;
                        this_thread::sleep_for(chrono::seconds(4));
                    }
                } else {
                    system("cls");
                    break;
                }
            }
        } else if(response == "3") {
            while(true){
                system("cls");
                if(!countEmployees(employees)){
                    cout << "The team is incomplete!" << endl;
                }

                if(!countProducts(products)){
                    cout << "The list of products is incomplete!" << endl;
                }

                if(!countEmployees(employees) || !countProducts(products)){
                    this_thread::sleep_for(chrono::seconds(4));
                    break;
                }

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

                    if(response != "1" && response != "2" && response != "3" && response != "4") {
                        cout << "The option selected doesn't exist in the menu!" << endl;
                    } else {
                        break;
                    }
                }

                if(response == "1"){
                    system("cls");
                    Comanda::resetNumOrders();
                    orders.clear();
                    for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
                        if((*it)->getType() == "operator"){
                            ((Operator*)(*it))->getOrders().clear();
                            ((Operator*)(*it))->resetNumOrders();
                            ((Operator*)(*it))->resetSalary();
                        }
                    }
                    ifstream file("orders.txt");

                    if (file.is_open()) {
                        processFileOrder(employees, products, orders, file);
                        file.close();
                        cout << "Press ENTER to return to the menu...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                    } else {
                        cout << "Unable to open file";
                        this_thread::sleep_for(chrono::seconds(4));
                    }
                } else if(response == "2") {
                    system("cls");
                    ofstream file("orders.txt", ios::app);

                    if (file.is_open()) {
                        addNewOrder(file);
                        file.close();
                        cout << "Press ENTER to return to the menu...";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.get();
                    } else {
                        cout << "Unable to open file";
                        this_thread::sleep_for(chrono::seconds(4));
                    }


                }else if(response == "3"){
                    system("cls");
                        if(orders.size() != 0){
                            displayAllOrders(orders);
                            cout << "\nPress ENTER to return to the menu...";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cin.get();
                        } else {
                            cout << "No orders to display because the list of orders is empty!" << endl;
                            this_thread::sleep_for(chrono::seconds(4));
                        }
                } else {
                    system("cls");
                    break;
                }
            }

        } else if (response == "4") {
            while(true){
                system("cls");
                cout << "Reports" << endl;
                cout << endl;

                cout << "1. Generate reports" << endl;
                cout << "2. Back" << endl;
                cout << endl;

                cout << "Select option: " << endl;
                while(true){
                    cin >> response;
                    cout << endl;

                    if(response != "1" && response != "2"){
                        cout << "The option selected doesn't exist in the menu!" << endl;
                    } else {
                        break;
                    }
                }

                if(response == "1"){
                    system("cls");
                    ofstream report1("highest_numOrd.csv");
                    ofstream report2("top3_valuableOrd.csv");
                    ofstream report3("top3_highestSalary.csv");
                    generateReports(employees, orders, report1, report2, report3);
                    report1.close();
                    report2.close();
                    report3.close();
                    this_thread::sleep_for(chrono::seconds(4));
                    cout << "Reports generated!" << endl;
                    cout << "\nPress ENTER to return to the menu...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                } else {
                    system("cls");
                    break;
                }
            }
        } else {
            return 0;
        }
    }

}
