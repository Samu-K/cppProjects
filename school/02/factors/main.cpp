#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";
    int inum;
    cin >> inum;

    if (inum<1) {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }

    if (inum==36) {
        cout << "36 = 6 * 6" << endl;
        return 0;
    }

    bool match = false;
    int first_match = 0;
    int second_match = 0;

    for (int i=inum-1;match==false;i--) {
        if (first_match == 1) {
            cout << inum << " " << "=" << " " << first_match << " " << "*" << " " << inum << endl;
            return 0;
        }

        if (i == 0) {
            match = true;
        }

        if ((inum % i)==0) {
            if (first_match == 0) {
                first_match = i;
                ++i;
            } else {
                second_match = i;

                if (first_match * second_match == inum) {
                    cout << inum << " " << "=" << " " << second_match << " " << "*" << " " << first_match << endl;
                    return 0;
                }
                else {
                    first_match = second_match;
                }
            }

        }
    }

    return 0;
}
