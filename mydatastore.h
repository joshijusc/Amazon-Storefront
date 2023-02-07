#ifndef HW2_MYDATASTORE_H
#define HW2_MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include <map>
#include <set>

class MyDataStore : public DataStore {
public:
    MyDataStore();

    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);
    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    /*
     * Idx is the previous index
     */
    void addToCart(std::string username, Product* p);

    void viewCart(std::string username);

    void buyCart(std::string username);

private:
    // vector of all products
    std::vector<Product*> products_;

    // map each username to a user object
    std::map<std::string, User*> nameToUser_;

    // map each keyword to a set of products
    std::map<std::string, std::set<Product*>> keyToProds_;

    // map each username to a vector of products associated with each user (cart)
    std::map<std::string, std::vector<Product*>> userToCart_;
};


#endif //HW2_MYDATASTORE_H