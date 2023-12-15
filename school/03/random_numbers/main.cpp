#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    bool flag = true;
    unsigned int seed;
    string inp;

    cout << "Enter a seed value: ";
    cin >> seed;

    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(lower,upper);

    while (flag == true) {
        cout << endl;
        cout << "Your drawn random number is" << " " << distr(gen) << endl;
        cout << "Press q to quit or any other key to continue: ";
        cin >> inp;

        if (inp == "q") {
            flag = false;
        };
    }
}


int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cin.clear();

    cout << "Enter an upper bound: ";
    cin >> upper_bound;
    cin.clear();

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
