#ifndef GAME_HH
#define GAME_HH

#include "gameboard.hh"
#include "point.hh"
#include <string>

class Game
{
public:
    Game();
    int run();

    void set_sts(int seed, int width, int height);
    Point getSnakeHead();

private:
    std::string getInput(const std::string& prompt = "> ");
    bool checkCommand(const std::string& command);
    void printHelp();
    unsigned int getRandomSeed();
    int getFieldSize(const std::string& prompt);

    // vars
    int seed_;
    int width_;
    int height_;
    GameBoard field;
};

#endif // GAME_HH
