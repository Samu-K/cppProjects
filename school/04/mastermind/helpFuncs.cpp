#include <iostream>

char get_gentype() {
    /*
     * Asks the user to input R or L
     * Makes sure that input is
     *     - only one letter
     *     - R or L
     *
     * return the input
    */

    bool gen_flag = true;
    std::string gentype_inp;
    char gentype;

    // loop until we have a clean input
    while (gen_flag) {
        std::cout << "Enter an input way (R = random, L = list): ";
        std::cin >> gentype_inp;

        if (gentype_inp.length()!=1) {
            std::cout << "Bad input" << std::endl;
            std::cin.clear();
            continue;
        } else {
            // we need this to turn gentype into char
            gentype = gentype_inp.at(0);
        }

        gentype = toupper(gentype);

        // check input is clear
        if ((gentype != 'R') && (gentype != 'L')) {
            std::cout << "Bad input" << std::endl;
            std::cin.clear();
            continue;
        }

        // if program runs to this points
        // then input is clear
        gen_flag = false;
    }

    return gentype;
}

bool is_input_clear(std::string inp) {
    /*
     Checks that the give input meets all criteria
         - only contains usable colors
         - is only four letters long
    */

    std::string allowed_input = "BRYGOV";

    // make sure input length is correct
    if (inp.length()!=4) {
        std::cout << "Wrong size" << std::endl;
        return false;
    }

    // make sure only allowed colors are input
    for (char letter : inp) {
        // npos is returned if substring is not found in string
        if (allowed_input.find(letter) == std::string::npos) {
            std::cout << "Unknown color" << std::endl;
            return false;
        }
    }

    // if programs runs to this point then input is clear
    return true;
}

