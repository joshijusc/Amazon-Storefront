#include "movie.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;

}

Movie::~Movie()
{}

string Movie::getGenre() const {
    return genre_;
}

string Movie::getRating() const {
    return rating_;
}

set<string> Movie::keywords() const {
    string word = name_ + " " + genre_;
    word = convToLower(word);
    set<string> keys = parseStringToWords(word);
    return keys;
}

string Movie::displayString() const {
    string display = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_
                     + "\n" + to_string(getPrice()) + " " + to_string(getQty()) + " left.";
    return display;
}

void Movie::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}