#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
using namespace std;

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void set_credit_limit(int limit);
    void save_money(int amount);
    bool take_money(int amount);
    void transfer_to(Account& target, int amount);
    void print() const;

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    string iban_;
    string owner_;
    bool has_credit_;
    int limit_;
    int stored_amount_ = 0;

};

#endif // ACCOUNT_HH
