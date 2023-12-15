#include <iostream>

using namespace std;

int main()
{
    int temp;
    cout << "Enter a temperature: ";
    cin >> temp;
    cin.clear();
    double c_temp;
    double f_temp;

    f_temp = temp*1.8+32;
    c_temp = (temp-32) / 1.8;

    cout << temp << " " << "degrees Celsius is" << " " << f_temp << " " << "degrees Fahrenheit" << endl;
    cout << temp << " " << "degrees Fahrenheit is" << " " << c_temp << " " << "degrees Celsius" << endl;
    // Write your code here

    return 0;
}
