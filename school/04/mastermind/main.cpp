/*
 * Description:
 *     This project is a game called mastermind.
 *     The point of the game is to guess
 *     the correct sequence of colors.
 *     You can read more about the rules at:
 *         https://en.wikipedia.org/wiki/Mastermind_(board_game)
 *
 *     This console-based app work by the following logic:
 *         - First the player is asked how the correct colorkey is made
 *             - R will make the computer randomly produce a key
 *             - L allows the user to input the key themselves
 *         - When the colorkey is generated, the user is asked for a guess
 *             - The players current gues and previous guesses are shown
 *             - The score of each guess will also be shown
 *                - The first number indicates how many of the colors are
 *                    - the right color
 *                    - in the right place
 *                - The second number shows how many are
 *                    - the right color
 *                    - in the wrong place
 *                - If they guess all colors correct they win the game
 *
 *             - If the amount of guesses is less than 10
 *                 - the player gets to guess again
 *                 - otherwise they lose the game
 *         - It's possible to exit the app at anytime by inputting q
 *         - Inputs are not case sensitive
 *
 * Developer: Samu Kaarlela
 * Studentnum: 150974219
 * username: dgsaka
 * email: samu.kaarlela@tuni.fi
 *
 * Notes:
 *     Expanding on comment from board.cpp line 147
 *        The find function will always return the first value it finds
 *        This means that duplicate values would return the same index
 *
 *        This makes results inaccurate if there are duplicates
 *            - in the colorkey
 *            - in the input
 *
 *        To combat this we create a copy of the input and colorkey
 *        We then change handled values to X
 *           - (any character that is not a part of the game works)
 *        This way find will find the next unhandled value
 */


// imports
#include "board.hh"
#include "is_input_clear.hh"

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

char get_gentype() {
    /*
     * Asks the user to input R or L
     * Makes sure that input is
     *     - only one letter
     *     - R or L
     *
     * return the input
    */

    // vars
    bool gen_flag = true;
    string gentype_inp;
    char gentype;

    // loop until we have a clean input
    while (gen_flag) {
        // determine board gen method
        cout << "Enter an input way (R = random, L = list): ";
        cin >> gentype_inp;

        // make sure only one char is given
        if (gentype_inp.length()!=1) {
            cout << "Bad input" << endl;
            cin.clear();
            continue;
        } else {
            // we need this to turn gentype into char
            gentype = gentype_inp.at(0);
        }

        // set input to uppercase
        gentype = toupper(gentype);

        // check input is clear
        if ((gentype != 'R') && (gentype != 'L')) {
            cout << "Bad input" << endl;
            cin.clear();
            continue;
        }

        // if program runs to this points
        // then input is clear
        gen_flag = false;
    }

    return gentype;
}


int main()
{
    // flags used to track loops
    bool game_flag = true;

    // helper variables
    string inp;
    char gentype;

    // track the amount of guesses
    int guess_amount=0;

    // info print
    cout << "Colors in use: B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet" << endl;
    cout << "*******************************************************************************" << endl;

    // ask user for gentype
    gentype = get_gentype();

    // generate the board
    Board board = Board(gentype);

    // loop until q is pressed
    // or game ends
    while (game_flag) {
        cout << "ROW> ";
        cin >> inp;

        // set input to all uppercase
        transform(inp.begin(), inp.end(), inp.begin(), ::toupper);

        // quit if q is given
        if (inp=="Q") {
            game_flag = false;
            continue;
        }

        // check that input is proper
        if (!is_input_clear(inp)) {
            // skip back to beginning to ask new input
            continue;
        }

        // check amount of right colors and guesses in right place
        // this also saves the guess to be part of gamestate
        guessResult result = board.guess(inp);
        board.print_gamestate();

        // four fully correct guesses means the code was correct
        if (result.full_right == 4) {
            cout << "You won: Congratulations!" << endl;
            game_flag = false;
            continue;
        } else {
            // add attempt
            ++guess_amount;
        }

        // if not guessed in 10, then player loses
        if (guess_amount==10) {
            game_flag = false;
            cout << "You lost: Maximum number of guesses done" << endl;
        }
    }
}
