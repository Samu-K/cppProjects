#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int num;
    cin >> num;

    int cnum;
    cnum = num * num * num;

    if ((cnum/num)/num==num) {
        cout << "The cube of" << " " << num << " " << "is" << " " << cnum << "." << endl;
    } else {
        cout << "Error!" << " " << "The cube of" << " " << num << " " << "is not" << " " << cnum << "." << endl;
    }
}
