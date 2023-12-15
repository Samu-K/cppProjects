#include <iostream>
using namespace std;


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int numcount;
    cin >> numcount;

    for (int i=1;i < numcount+1; i++)
    {
        if ((i % 3)==0 and (i % 7)==0) {
            cout << "zip boing" << endl;
        }
        else if ((i % 3)==0) {
            cout << "zip" << endl;
        } else if ((i%7)==0) {
            cout << "boing" << endl;
        } else {
            cout << i << endl;
        }

    }


    return 0;
}
