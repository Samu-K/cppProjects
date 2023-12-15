#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;




int main()
{
    string input_fp;
    cout << "Input file: ";
    cin >> input_fp;

    ifstream input(input_fp);

    if (!input.is_open()) {
        cout << "Error! The file " + input_fp + " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, int> players;

    string line;
    while (getline(input,line)) {
        auto delim_place = line.find(":");
        int points = stoi(line.substr(delim_place+1,line.length()));
        string name = line.substr(0,delim_place);

        if (players.count(name) == 0) {
            pair<string,int> player(name,points);
            players.insert(player);
        } else {
            players.at(name) += points;
        }
    }

    cout << "Final scores:" << endl;

    for (auto player : players) {
        cout << player.first << ": " << player.second << endl;
    }


    return 0;
}
