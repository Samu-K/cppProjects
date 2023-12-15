/*
####################################################################
# COMP.CS.110 Programming 2: Structures, 2022                      #
#                                                                  #
# Project4: Snake                                                  #
# Program description: Implements a game called Snake.             #
#                                                                  #
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
#                                                                  #
# Author: First Last, s.num., first.last@tuni.fi                   #
####################################################################
*/
#include "game.hh"

#include "gameboard.hh"
#include <cctype> // required for std::isdigit
#include <iostream>
#include <string>


// Constants for special commands
const char QUIT = 'q';
const char HELP = 'h';

Game::Game() {
};

// Gets a string from the player.
// Returns the text, the player wrote after the prompt.
std::string Game::getInput(const std::string& prompt)
{
    std::cout << prompt;
    std::string input;
    getline(std::cin, input);
    return input;
}

// Returns true if the given string is a valid command.
bool Game::checkCommand(const std::string& command)
{
    if(command.size() < 1)
    {
        return false;
    }
    for (const char& cmd : {UP, LEFT, DOWN, RIGHT, QUIT, HELP})
    {
        if (command.at(0) == cmd)
        {
            return true;
        }
    }
    return false;
}

// Prints a block of help text to aid with the game.
void Game::printHelp()
{
    // ## No bugs have been planted here, this might help with debugging. ##
    std::cout << "\nWelcome to Snake!\n\n"
        << "Your aim is to guide the snake to the food around the field\n"
        << "while avoiding the walls and the ever-growing snake itself.\n\n"
        << "The snake can't make 180 degree turns, which means that\n"
        << "it can't go directly back to the square it came from,\n"
        << "unless the snake occupies only one square in total.\n\n"
        << "Symbols and their meanings:\n"
        << HEAD << " head, " << BODY << " body, " << TAIL << " tail,\n"
        << WALL << " wall, " << FOOD << " food\n\n"
        << "You have the following commands at your disposal:\n"
        << UP << ": Move the snake up\n"
        << LEFT << ": Move the snake left\n"
        << DOWN << ": Move the snake down\n"
        << RIGHT << ": Move the snake right\n"
        << QUIT << ": Stop the game\n"
        << HELP << ": Print this text again\n\n" << std::endl;
}

// run game
int Game::run()
{
    //std::default_random_engine rng(getRandomSeed());
    GameBoard field = GameBoard(width_, height_, seed_);

    // Printing the help text when starting the game.
    printHelp();
    field.print();

    // Asking for input until the game stops.
    while (not field.gameOver())
    {
        // Getting and validating the input.
        const std::string command = getInput();
        if (not checkCommand(command))
        {
            std::cout << "Unknown command! Try command 'help'." << std::endl;
            continue;
        }

        // Executing the given command.
        if (command.at(0) == QUIT)
        {
            break;
        }
        else if (command.at(0) == HELP)
        {
            printHelp();
        }
        else
        {
            field.moveSnake(command);
        }

        // Printing the current state of the game.
        field.print();
    }

    // Printing a message if the game wasn't stopped with 'quit'.
    if (field.gameLost())
    {
        std::cout << "Snek is ded. Better luck next time ;)" << std::endl;
    }
    else if (field.gameWon())
    {
        std::cout << "Well done! The snake has been satisfied, for now..."
            << std::endl;
    }

    return EXIT_SUCCESS;
}

void Game::set_sts(int seed, int width, int height)
{
    seed_ = seed;
    width_ = width;
    height_ = height;
}

Point Game::getSnakeHead()
{
    return field.getHead();
}
