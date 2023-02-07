#include "book.h"

using namespace std;

Book::Book(const string category, const string name, double price, int qty, string isbn, string author) : Product(category, name, price, qty)
{
    isbn_ = isbn;
    author_ = author;

}

Book::~Book()
{}

string Book::getIsbn() const {
    return isbn_;
}

string Book::getAuthor() const {
    return author_;
}

set<string> Book::keywords() const {
    string word = name_ + " " + author_;
    word = convToLower(word);
    set<string> keys = parseStringToWords(word);
    keys.insert(isbn_);
    return keys;
}

string Book::displayString() const {
    string display = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_
            + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
    return display;
}

void Book::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}