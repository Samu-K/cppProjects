#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;


bool check_letters(string key, string accepted_letters, bool is_key=true) {
    string::size_type keylen = key.length();

    for (string::size_type i=0;i< keylen;++i) {
        char c = key[i];
        if (accepted_letters.find(c) == string::npos) {
            if (is_key == true) {
                cout << "Error! The encryption key must contain only lower case characters." << endl;
            } else {
                cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            }
            return false;
        }
     }

    return true;
}


bool check_validity (string key, string accepted_letters) {
    string::size_type keylen = key.length();

    if (keylen != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return false;
    };

    string sorted_key = key;
    sort(sorted_key.begin(),sorted_key.end());

    if (accepted_letters != sorted_key) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return false;
    }

    if (check_letters(key,accepted_letters) == false) {
     return false;
    }

    return true;


};

int main()
{
    string accepted_letters="abcdefghijklmnopqrstuvwxyz";
    cout << "Enter the encryption key: ";
    string key;
    cin >> key;
    cin.clear();

    if (check_validity(key,accepted_letters) == false) {
        return EXIT_FAILURE;
    }

    string to_crypt;
    cout << "Enter the text to be encrypted: ";
    cin >> to_crypt;
    cin.clear();

    if (check_letters(to_crypt,accepted_letters,false) == false) {
        return EXIT_FAILURE;
    }

    string::size_type cyptlen = to_crypt.length();

    for (string::size_type i=0; i < cyptlen;++i) {
        to_crypt[i] = key[accepted_letters.find(to_crypt[i])];
    }

    cout << "Encrypted text:" << " " << to_crypt << endl;

    return EXIT_SUCCESS;

};
