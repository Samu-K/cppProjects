#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"

#include <string>
#include <iostream>

using namespace std;

class Book
{
public:
    Book(string name, string author);

    // Funcs
    void loan(Date date);
    void print();
    void give_back();
    void renew();
private:

    // vars
    string name_;
    string author_;
    bool loaned_ = false;
    Date loan_date_;
    Date return_date_;

};

#endif // BOOK_H
