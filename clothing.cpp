#include "clothing.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand) : Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;

}

Clothing::~Clothing()
{}

string Clothing::getSize() const {
    return size_;
}

string Clothing::getBrand() const {
    return brand_;
}

set<string> Clothing::keywords() const {
    string word = name_ + " " + brand_;
    word = convToLower(word);
    set<string> keys = parseStringToWords(word);
    return keys;
}

string Clothing::displayString() const {
    string display = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_
                     + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
    return display;
}

void Clothing::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}