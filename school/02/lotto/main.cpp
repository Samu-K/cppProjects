#include <iostream>

using namespace std;

long int factorial(int n) {
    int f=1;
    for (int i=1;i<=n;++i) {
        f *= i;
    }
    return f;
}

int main()
{
    int num_rows;
    int num_given;
    cout << "Enter the total number of lottery balls: ";
    cin >> num_rows;
    cin.clear();

    cout << "Enter the number of drawn balls: ";
    cin >> num_given;
    cin.clear();

    if (num_rows<0 or num_given<0) {
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    } else if (num_given > num_rows) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    }

    unsigned long int bottom_half = factorial(num_rows-num_given);
    unsigned long int iters = factorial(num_rows) / (bottom_half*factorial(num_given));

    cout << "The probability of guessing all" << " " << num_given << " " << "balls correctly is 1/" << iters << endl;
    return 0;
}
