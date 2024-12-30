#include "helperFuncProduct.h"
#include "helperFuncEmployee.h"

bool validCode(vector <Produs*> &products, const string &code){
    int counter = count_if(products.begin(), products.end(), [&code](Produs* i){
        return (code == i->getCode());
    });

    return counter == 0;
}

bool validColour(const string colour){
    
    vector <string> colours;

    colours.push_back("black");
    colours.push_back("white");
    colours.push_back("grey");
    colours.push_back("red");
    colours.push_back("orange");
    colours.push_back("yellow");
    colours.push_back("blue");
    colours.push_back("green");
    colours.push_back("purple");
    colours.push_back("pink");
    colours.push_back("brown");

    for(vector <string>::iterator it = colours.begin(); it != colours.end(); it++){
        if(colour == *it){
            return true;
        }
    }

    return false;
}

void displayAllProducts(vector <Produs*> &products){
    cout << "Products of the company:\n\n";
    for(vector <Produs*>::iterator it = products.begin(); it != products.end(); it++){
        (*it)->afisare();
        cout << endl;
    }
}

void displayAllCodes(vector <Produs*> &products){
    for(vector <Produs*>::iterator it = products.begin(); it != products.end(); it++){
        (*it)->displayCode();
    }
}

void addNewProduct(vector <Produs*> &products){

    string type;
    string code;
    string name;
    float base_price;
    int stock;

    cout << "Introduce the required fields for the new product!\n\n";

    cout << "Please introduce the code of the product" << endl;
    while(true){
        cin >> code;
        cout << endl;

        if(!validCode(products, (const string)code)){
            cout << "The code of the product must be unique" << endl;
            cout << "Here is a list of unavailable codes: " << endl;
            displayAllCodes(products);
        } else {
            break;
        }
    }

    cout << "Please introduce the name of the product" << endl;
    while(true){
        cin >> name;
        cout << endl;
        if(name.size() < 4){
            cout << "The name of the product must have at least 4 characters!" << endl;
        } else {
            break;
        }
    }

    cout << "Please introduce the base price of the product" << endl;
    while(true){
        cin >> base_price;
        cout << endl;
        if(base_price < 0){
            cout << "The base price must be a positive number!" << endl;
        } else {
            break;
        }
    }

    cout << "Please introduce the number of products in stock" << endl;
    while(true){
        cin >> stock;
        cout << endl;
        if(stock <= 0){
            cout << "The number of products in stock must be a positive number!" << endl;
        } else {
            break;
        }
    }

    cout << "What is the type of product?(vestimentatie/disc)" << endl;
    while(true){
        cin >> type;
        cout << endl;
        transform(type.begin(), type.end(), type.begin(), [](char c){
            return tolower(c);
        });
        if(type == "disc" || type == "vestimentatie"){
            break;
        } else {
            cout << "The type of product is not valid! Please introduce a valid type(disc/vestimentatie)" << endl;
        }
    }

    if(type == "vestimentatie"){
        string colour;
        string brand;

        cout << "Please introduce the colour of the product" << endl;
        while(true){
            cin >> colour;
            cout << endl;
            transform(colour.begin(), colour.end(), colour.begin(), [](char c){
                return tolower(c);
            });
            if(!validColour(colour)){
                cout << "This cannot be a colour!" << endl;
            } else {
                break;
            }
        }

        cout << "Please introduce the brand of the product" << endl;
        while(true){
            cin >> brand;
            cout << endl;
            brand[0] = toupper(brand[0]);
            transform(brand.begin() + 1, brand.end(), brand.begin() + 1, [](char c){
                    return tolower(c);
            });
            if(brand.size() < 3){
                cout << "The brand of the product must have at least 3 characters!" << endl;
            } else {
                break;
            }
        }

        products.push_back(new Vestimentatie((const string)code, name, stock, base_price, colour, brand));
    } else {
        string CDtype;
        string record_label;
        string date = "00.00.0000";
        string band;
        string album;

        cout << "Please introduce the type of disc(cd/vinil/vintage)" << endl;
        while(true){
            cin >> CDtype;
            cout << endl;
            transform(CDtype.begin(), CDtype.end(), CDtype.begin(), [](char c){
                return tolower(c);
            });
            if(CDtype != "cd" && CDtype != "vinil" && CDtype != "vintage"){
                cout << "The type of disc is incorrect!(cd/vinil/vintage)" << endl;
            } else {
                break;
            }
        }

        cout << "Please introduce the record label" << endl;
        while(true){
            cin >> record_label;
            cout << endl;
            if(record_label.size() < 3){
                cout << "The record label must have at least 3 characters!" << endl;
            } else {
                break;
            }
        }

        int day;
        int month;
        int year;

        cout << "Please introduce the date when the disc was listed" << endl;
        while(true){
        
            cout << "Day: ";
            cin >> day;
            cout << "Month: ";
            cin >> month;
            cout << "Year: ";
            cin >> year;
            cout << endl;

            if(validDate(day, month, year)){

                if(day < 10){
                    date.replace(1,1,to_string(day));
                } else {
                    date.replace(0,2,to_string(day));
                }
                if(month < 10) {
                    date.replace(4,1,to_string(month));
                } else {
                    date.replace(3,2,to_string(month));
                }

                date.replace(6, 4, to_string(year));

                break;
            } else {
                cout << "The provided date is invalid!" << endl;
            }
        }

        cout << "Please introduce the band" << endl;
        while(true){
            cin >> band;
            cout << endl;
            if(band.size() < 3){
                cout << "The band must have at least 3 characters!" << endl;
            } else {
                break;
            }
        }

        cout << "Please introduce the album" << endl;
        while(true){
            cin >> album;
            cout << endl;
            if(album.size() < 3){
                cout << "The album must have at least 3 characters!" << endl;
            } else {
                break;
            }
        }
        if(CDtype == "cd" || CDtype == "vinil"){
            products.push_back(new Disc(CDtype, (const string)code, name, stock, base_price, (const string)record_label, (const string)date, (const string)band, (const string)album));
        } else {
            string mint;
            bool mint_bool;
            int coef_rarity;
            cout << "Is the vintage disc mint?" << endl;
            while(true){
                cin >> mint;
                cout << endl;
                transform(mint.begin(), mint.end(), mint.begin(), [](char c){
                    return tolower(c);
                });
                if(mint != "true" && mint != "false"){
                    cout << "The answer must be true or false!" << endl;
                } else {
                    mint_bool = mint == "true";
                    break;
                }
            }

            cout << "Please introduce the rarity coefficient of the disc" << endl;
            while(true){
                cin >> coef_rarity;
                cout << endl;
                if(coef_rarity < 1 || coef_rarity > 5){
                    cout << "The rarity coefficient must be between 1 and 5!" << endl;
                } else {
                    break;
                }
            }
            products.push_back(new Vintage((const string)code, name, stock, base_price, (const string)record_label, (const string)date, (const string)band, (const string)album, mint_bool, coef_rarity));
        }
    }
}

void modifyProduct(vector <Produs*> &products){
    int new_stock;
    string search_code;

    cout << "What is the code of the product you want to modify?" << endl;
    while(true){
        cin >> search_code;
        cout << endl;

        if(!validCode(products, (const string)search_code)){
            break;
        } else {
            cout << "The provided code doesn't exist in the list of products!" << endl;
            cout << "Here is a list of available codes :" << endl;
            displayAllCodes(products);
        }
    }

    cout << "What is the new number of products in stock?" << endl;
    while(true){        
        cin >> new_stock;
        cout << endl;

        if(new_stock >= 0){
            vector <Produs*>::iterator it;
            for (it = products.begin(); (*it)->getCode() != search_code; it++)
                ;
            if((*it)->getStock() == new_stock){
                cout << "The stock value is the same as the old one!" << endl;
                continue;
            }
            (*it)->setStock(new_stock);
            cout << "Product stock modified!" << endl;
            break;
        } else {
            cout << "The stock value must be a positive number!" << endl;
        }
    }
}

void deleteProduct(vector <Produs*> &products){
    string search_code;

    cout << "What is the code of the product to delete?" << endl;
    while(true){
        cin >> search_code;
        cout << endl;

        if(!validCode(products, (const string)search_code)){
            vector <Produs*>::iterator it;
            for (it = products.begin(); (*it)->getCode() != search_code; it++)
                ;
            products.erase(it);
            cout << "Product deleted!" << endl;
            break;
        } else {
            cout << "The provided code doesn't exist in the list of products!" << endl;
            cout << "Here is a list of available codes :" << endl;
            displayAllCodes(products);
        }
    }
}

bool countProducts(vector <Produs*> &products){
    int numCD = count_if(products.begin(), products.end(), [](Produs* i){
        return (i->getType() == "cd");
    });

    int numVinil = count_if(products.begin(), products.end(), [](Produs* i){
        return (i->getType() == "vinil");
    });

    int numVintage = count_if(products.begin(), products.end(), [](Produs* i){
        return (i->getType() == "vintage");
    });

    int numClothes = count_if(products.begin(), products.end(), [](Produs* i){
        return (i->getType() == "vestimentatie");
    });

    if(numCD < 2 || numVinil < 2 || numVintage < 2 || numClothes < 2){
        return false;
    } else {
        return true;
    }
}