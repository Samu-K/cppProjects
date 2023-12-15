/*
 * Developer: Samu Kaarlela
 * Studentnum: 150974219
 * username: dgsaka
 * email: samu.kaarlela@tuni.fi
*/

#include <string>
#include <vector>

using namespace std;

#ifndef BOARD_HH
#define BOARD_HH

struct guessResult {
    int color_right, full_right;
};

// stores a singular guess
struct guessType {
    guessResult score;
    string key;
};

// stores the correct colorkey
struct colorKey {
    vector<char> colors;
    string fullkey;
};

class Board
{
public:
    Board(char gentype);

    void print_gamestate();
    guessResult guess(const string& input);

private:
    colorKey correct_key_;
    vector<char> usable_colors_ = {'B','R','Y','G','O','V'};
    vector<guessType> guesses_;

};

#endif // BOARD_HH
