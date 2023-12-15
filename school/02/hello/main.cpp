#include <iostream>
#include <string>

using namespace std;

int main() {
    string nimi = "";
    cout << "Syota nimesi: ";
    getline(cin, nimi);

    int ika = 0;
    cout << "Syota ikasi: ";
    cin >> ika;

    cout << "Hauska tavata " << nimi << " "
         << ika << " v." << endl;
    cout << 50 - ika
         << " vuoden paasta olet 50 vuotias."
         << endl;
}
