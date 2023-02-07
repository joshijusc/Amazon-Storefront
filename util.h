#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    // iterator through s1 and use find for s2
    std::set<T> intersection;
    typename std::set<T>::iterator it;
    for (it = s1.begin(); it != s1.end(); ++it){
        if (s2.find(*it) != s2.end()){
            intersection.insert(*it);
        }
    }
    return intersection;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    // create copy of s1, use iterator to iterate through s1 and compare each element using find on s2; if found && not in list, add to list copy
    std::set<T> u;
    typename std::set<T>::iterator it;
    u = s1; //shallow copy?
    for (it = s2.begin(); it != s2.end(); ++it){ // looks through each element of s2 and checks for duplicates in u
        if (s1.find(*it) == s1.end()){
            u.insert(*it);
        }
    }
    return u;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
