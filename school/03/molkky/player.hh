#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>
using namespace std;

class Player
{
public:
    Player(string name);

    // funcs
    string get_name();
    int get_points();
    bool has_won();
    void add_points(int pts);

private:
    int points_ = 0;
    string name_;
};

#endif // PLAYER_HH
