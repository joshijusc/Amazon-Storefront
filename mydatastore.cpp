#include "mydatastore.h"
#include <iostream>

using namespace std;

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore() {
    vector<Product*>::iterator it;
    for (it = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }
    map<string, User*>::iterator itMap;
    for (itMap = nameToUser_.begin(); itMap != nameToUser_.end(); ++itMap){
        delete itMap->second;
    }
}

void MyDataStore::addProduct(Product* p){
    products_.push_back(p);
    set<string> keys = p->keywords();
    // if keyword is in list currently, insert product to that keyword's set
    // else create new map pair and set
    set<string>::iterator it;
    for (it = keys.begin(); it != keys.end(); ++it){
        if (keyToProds_.find(*it) != keyToProds_.end()){ //keyword was in map already
            (keyToProds_.find(*it)->second).insert(p);
        } else {
            set<Product*> newProds;
            newProds.insert(p);
            keyToProds_.insert(pair<string, set<Product*>>(*it, newProds));
        }
    }
}

void MyDataStore::addUser(User* u){
    nameToUser_.insert(pair<string, User*>(u->getName(), u));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    vector<Product*> searchResults;
    if (terms.empty()){ // No keywords given
        return searchResults;
    }
    if (terms.size() == 1){ // 1 keyword
        if (keyToProds_.find(terms[0]) != keyToProds_.end()) {
            // Return set of Products at this key but convert to vector
            set<Product *>::iterator it;
            for (it = keyToProds_[terms[0]].begin(); it != keyToProds_[terms[0]].end(); ++it) {
                searchResults.push_back(*it);
            }
        }
        return searchResults;
    }



    set<Product*> searchSet;
    if (type == 0) { // AND
        if (keyToProds_.find(terms[0]) != keyToProds_.end()) {
            searchSet = keyToProds_[terms[0]];
        } else {
            return searchResults;
        }
        for (size_t i=1; i<terms.size(); i++){
            if (keyToProds_.find(terms[i]) != keyToProds_.end()){
                searchSet = setIntersection(keyToProds_[terms[i]], searchSet);
            } else {
                return searchResults;
            }
        }

    } else if (type == 1) { // OR
        for (size_t i=0; i<terms.size(); i++){
            if (keyToProds_.find(terms[i]) != keyToProds_.end()){
                searchSet = setUnion(keyToProds_[terms[i]], searchSet);
            }
        }
    }

    // Convert the final set to a vector
    set<Product*>::iterator it;
    for (it = searchSet.begin(); it != searchSet.end(); ++it) {
        searchResults.push_back(*it);
    }
    return searchResults;
}

void MyDataStore::dump(ostream& ofile){
    // Call dump on each product in product vector, then call dump on each user
    ofile << "<products>" << endl;
    for (size_t i=0; i<products_.size(); i++){ // Products
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it=nameToUser_.begin(); it!=nameToUser_.end(); ++it) { // Users
        (*it).second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string username, Product* p) {
    if (nameToUser_.find(username) == nameToUser_.end()){ // Username valid?
        cout << "Invalid request" << endl;
    } else {
        if (userToCart_.find(username) == userToCart_.end()){ // Has the cart been initialized yet?
            vector<Product*> cart;
            pair<string, vector<Product*>> p1(username, cart);
            userToCart_.insert(p1);
        }
        userToCart_.find(username)->second.push_back(p);
    }
}

void MyDataStore::viewCart(string username) {
    if (nameToUser_.find(username) == nameToUser_.end()) { // Username valid?
        cout << "Invalid username" << endl;
    } else if (userToCart_.find(username) == userToCart_.end()) { // Has the cart been initialized yet?
        cout << "Empty Cart" << endl;
    } else {
        vector<Product*> userCart = userToCart_[username];
        size_t numCartItems = userCart.size();
        for (size_t i=0; i<numCartItems; i++){
            cout << "Product " << i+1 << endl;
            cout << userCart[i]->displayString() << endl;
        }
    }
}

void MyDataStore::buyCart(std::string username) {
    if (nameToUser_.find(username) == nameToUser_.end()) { // Username valid?
        cout << "Invalid username" << endl;
    } else if (userToCart_.find(username) == userToCart_.end()) { // Has the cart been initialized yet?
        cout << "Empty Cart" << endl;
    } else {
        vector<Product*> newCart = {};
        vector<Product*> userCart = userToCart_[username];
        User* currUser = nameToUser_[username];
        size_t numCartItems = userCart.size();
        for (size_t i=0; i<numCartItems; i++) {
            Product* currProd = userCart[i];
            if (currProd->getQty() > 0 && currUser->getBalance() - currProd->getPrice() >= 0){
                currProd->subtractQty(1);
                currUser->deductAmount(currProd->getPrice());
            } else { // remove the added cart
                newCart.push_back(currProd);
            }
        }
        userToCart_[username] = newCart;
    }
}