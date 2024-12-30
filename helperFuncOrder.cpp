#include "helperFuncOrder.h"

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

void removeExpiredOrders(vector <Angajat*> &employees){
    for(vector<Angajat*>::iterator it = employees.begin(); it != employees.end(); ++it){
        if((*it)->getType() == "operator"){
            Operator* op = (Operator*)(*it);
            vector<Comanda>& orders = op->getOrders();

            auto new_end = remove_if(orders.begin(), orders.end(), [&](Comanda& order){
                order.setTimeSimulator();
                if(order.getTimeSimulator() - order.getPackingTime() >= 0){
                    cout << endl;
                    cout << order.getID() << " was finished by operator with ";
                    (*it)->displayID();
                    return true;
                }

                return false;
            });

            orders.erase(new_end, orders.end());
        }
    }
}

void displayAllOrdersOp(vector <Angajat*> &employees){
    for(vector <Angajat*>::iterator it = employees.begin(); it != employees.end(); it++){
        if((*it)->getType() == "operator"){
            ((Operator*)(*it))->displayNumOrders();
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
