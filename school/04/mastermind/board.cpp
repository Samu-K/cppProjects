/*
 * Developer: Samu Kaarlela
 * Studentnum: 150974219
 * username: dgsaka
 * email: samu.kaarlela@tuni.fi
*/

#include "board.hh"
#include "is_input_clear.hh"

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

Board::Board(char gentype)
/*
 Generates correct colorkey when called
 Stores the previous guesses
 Handles logic for new guesses

 Asks for gentype (R or L)
*/

{
    // randomly generate correct key
    if (gentype == 'R') {

        // helper vars
        string fullkey = "";
        int seed;

        cout << "Enter a seed value: ";
        cin >> seed;

        // setup random number engine
        default_random_engine gen(seed);
        uniform_int_distribution<int> distr(0,5);

        // loop to fetch four colors
        for (int i=0;i<4;i++) {
            // pick a random color
            char slc = usable_colors_.at(distr(gen));

            // add it to the correct key
            correct_key_.colors.push_back(slc);
            fullkey += slc;
        }

        correct_key_.fullkey = fullkey;

    } else {
        // generate correct key based on user input
        bool key_flag = true;
        string inp;

        // loop until user gives good answer
        while (key_flag) {
            cout << "Enter four colors (four letters without spaces): ";
            cin >> inp;
            // set input to all uppercase
            transform(inp.begin(), inp.end(), inp.begin(), ::toupper);

            // check that input is clear
            // if it is we can exit
            if (is_input_clear(inp)) {
                key_flag=false;
            }
        }

        // loop through given input string
        for (unsigned long int i=0;i<inp.length();i++) {
            // add colors to key
            correct_key_.colors.push_back(inp.at(i));
        }

        // full key is just given input
        correct_key_.fullkey = inp;
    }
}

void Board::print_gamestate()
{
    /*
     Takes no parameters

     Prints out info about previous guesses
         - the guesses colors
         - how many were right color
         - how many were right color and place

      Returns void
    */
    cout << "===================" << endl;

    // go through all guesses
    for (unsigned long int i=0;i<guesses_.size();i++) {

        // store the guess in it's own type
        guessType cur_gues = guesses_.at(i);

        cout << "|";

        // go through each letter in guess
        for (auto letter : cur_gues.key) {
            cout << " " << letter;
        }

        cout << " " << "|";
        cout << " " << cur_gues.score.full_right << " " << "|";
        cout << " " << cur_gues.score.color_right << " " << "|";
        cout << endl;

    }
    cout << "===================" << endl;
}

guessResult Board::guess(const string &input)
{
    // init the result and set values to 0
    guessResult result;
    result.full_right = 0;
    result.color_right = 0;

    // create a copy of the key so we can modify it
    // without affecting the original
    auto check_key = correct_key_;
    string check_inp = input;
    string unhandled = "";

    // loop through the input string
    // we first only handle full matches
    for (unsigned long int i=0;i<input.length();i++) {
        // get color by index
        char color = input.at(i);

        // see if given color in the correct key
        auto match_iterator = find(
                    check_key.colors.begin(),
                    check_key.colors.end(),
                    color);

        // if the key contains color
        if (match_iterator != check_key.colors.end()) {
            // check what index the color matched
            unsigned long int match_index = match_iterator - check_key.colors.begin();

            // check if index is correct
            if (i == match_index) {
                result.full_right += 1;
            } else {
                unhandled += check_key.colors.at(i);
            }
        } else {
            // if not a match, we need to handle later
            unhandled += check_key.colors.at(i);
        }

        // set handled color to X
        // this is required due to duplicate values (see main.cpp notes)
        check_key.colors.at(i) = 'X';
    }

    // now we handle the parts that did not have a full match
    for (unsigned long int i=0;i<unhandled.length();++i) {
        // get unhandled color
        char letter = unhandled.at(i);

        // see if we find color in input
        auto match_iterator = find(
                    check_inp.begin(),
                    check_inp.end(),
                    letter);

        // if we find unhandled color in input
        // we know there was a correct color, but wrong pos.
        // also se handled color to X (see reason above)
        if (match_iterator != check_inp.end()) {
            unsigned long int match_index = match_iterator - check_inp.begin();
            result.color_right += 1;
            check_inp.at(match_index) = 'X';
        }
    }

    // log the guess
    guessType guess;
    guess.score = result;
    guess.key = input;
    guesses_.push_back(guess);

    // return result of the guess
    return result;
}
