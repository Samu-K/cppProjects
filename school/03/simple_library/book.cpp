#include "book.hh"
#include <iostream>
#include <string>

using namespace std;

Book::Book(string author,string name):
    name_(name),
    author_(author)
{

}

void Book::loan(Date date)
{
    if (!loaned_) {
        loan_date_ = date;
        date.advance(28);
        return_date_ = date;
        loaned_ = true;
    } else {
        cout << "Already loaned: cannot be loaned" << endl;
    }
}

void Book::print()
{
    cout << author_ << " " << ":" << " " << name_ << endl;
    if (loaned_) {
        cout << "- loaned:" << " ";
        loan_date_.print();

        cout << "- to be returned:" << " ";
        return_date_.print();
    } else {
        cout << "- available" << endl;
    }

}

void Book::give_back()
{
    loaned_ = false;
}

void Book::renew()
{
    if (loaned_) {
        return_date_.advance(28);
    } else {
        cout << "Not loaned: cannot be renewed" << endl;
    }
}
