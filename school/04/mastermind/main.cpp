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

#include "board.hh"
#include "helpFuncs.hh"

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

const std::string INFO_TEXT= "Colors in use: B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";
const std::string SEP_TEXT="*******************************************************************************";

int main()
{
    // flags used to track loops
    bool game_flag = true;

    std::string inp;
    char gentype;

    int guess_amount=0;

    std::cout << INFO_TEXT << std::endl << SEP_TEXT << std::endl;

    gentype = get_gentype();

    // generate the board
    Board board = Board(gentype);

    // loop until q is pressed
    // or game ends
    while (game_flag) {
        std::cout << "ROW> ";
        std::cin >> inp;

        // set input to all uppercase
        transform(inp.begin(), inp.end(), inp.begin(), ::toupper);

        if (inp=="Q") {
            game_flag = false;
            continue;
        }

        if (!is_input_clear(inp)) {
            // skip back to beginning to ask new input
            continue;
        }

        // check amount of right colors and guesses in right place
        // this also saves the guess to be part of gamestate
        guessResult result = board.guess(inp);
        board.print_gamestate();

        if (result.full_right == 4) {
            std::cout << "You won: Congratulations!" << std::endl;
            game_flag = false;
            continue;
        } else {
            ++guess_amount;
        }

        if (guess_amount==10) {
            game_flag = false;
            std::cout << "You lost: Maximum number of guesses done" << std::endl;
        }
    }
}
