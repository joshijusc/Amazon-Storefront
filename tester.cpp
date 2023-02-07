#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include "book.h"
#include "product.h"
using namespace std;

int main(){
    // parseStringToWords tester
//    string rawWord = "Men's Clothing We'll";
//    set <string> newSet = parseStringToWords(rawWord);
//    set<string>:: iterator it;
//    for (it = newSet.begin() ; it != newSet.end(); ++it){
//        cout << *it << endl;
//    }

    // setIntersection and setUnion testers
//    set <string> s1 = {"John", "Mark", "Mike", "James"};
//    set <string> s2 = {"Jason", "Max", "John"};
//    set <string> setInt = setIntersection(s1, s2);
//    set <string> setU = setUnion(s1, s2);
//    set<string>:: iterator itInt;
//    for (itInt = setInt.begin() ; itInt != setInt.end(); ++itInt){
//        cout << *itInt << endl;
//    }
//    cout << "*******" << endl;
//    set<string>:: iterator itU;
//    for (itU = setU.begin() ; itU != setU.end(); ++itU){
//        cout << *itU << endl;
//    }
    Book b("book", "Data Abstraction & Problem Solving with C++", 79.99, 20, "978-013292372-9", "Carrano and Henry");
    cout << b.displayString() << endl;
    b.dump(cout);
}