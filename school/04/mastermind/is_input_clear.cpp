/*
 * Developer: Samu Kaarlela
 * Studentnum: 150974219
 * username: dgsaka
 * email: samu.kaarlela@tuni.fi
*/


#include <string>
#include <iostream>

using namespace std;

bool is_input_clear(string inp) {
    /*
     Checks that the give input meets all criteria
         - only contains usable colors
         - is only four letters long
    */

    string allowed_input = "BRYGOV";

    // make sure input length is correct
    if (inp.length()!=4) {
        cout << "Wrong size" << endl;
        return false;
    }

    // make sure only allowed colors are input
    for (char letter : inp) {
        // npos is returned if substring is not found in string
        if (allowed_input.find(letter) == string::npos) {
            cout << "Unknown color" << endl;
            return false;
        }
    }

    // if programs runs to this point then input is clear
    return true;
}
