#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner),has_credit_(has_credit) {
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int limit) {
    if (has_credit_) {
        limit_ = limit;
    } else {
        cout << "Cannot set credit limit: the account has no credit card" << endl;
    }
}

void Account::save_money(int amount) {
    stored_amount_ += amount;
}

bool Account::take_money(int amount) {
    if (stored_amount_ - amount >= 0) {
        stored_amount_ -= amount;
        cout << amount << " " << "euros taken:"
             << " " << "new balance of" << " " << iban_
             << " " << "is" << " " << stored_amount_ << " " << "euros" << endl;
        return 1;

    } else if (has_credit_){
        if (stored_amount_-amount >= (limit_*(-1))) {
            stored_amount_ -= amount;
            cout << amount << " " << "euros taken:"
                 << " " << "new balance of" << " " << iban_
                 << " " << "is" << " " << stored_amount_ << " " << "euros" << endl;
            return 1;

        } else {
            cout << "Cannot take money: credit limit overflow" << endl;
            return 0;
        }

    } else {
        cout << "Cannot take money: balance underflow" << endl;
        return 0;
    }
}

void Account::transfer_to(Account& target, int amount) {
    bool suc = take_money(amount);
    if (suc) {
        target.save_money(amount);
    } else {
        cout << "Transfer from" << " " << iban_ << " " << "failed" << endl;
    }
}


void Account::print() const{
    cout << owner_ << " "
         << ":" << " " << iban_ << " "
         << ":" << " " << stored_amount_ << " " << "euros"
         << endl;
}

