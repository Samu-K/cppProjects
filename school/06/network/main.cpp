#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
/*
 *   {
    {"Hugo",vector<string> {"Laura","Jasper"}},
    {"Laura",vector<string> {"Helena","Elias"}},
    {"Jasper",vector<string> {"Maria"}},
    {"Helena",vector<string> {"Sofia"}}
}
*/

// global var for network
map<string, vector<string>> network;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print_network(string id, int layer) {

    string print = id;
    print.insert(0,layer*2,'.');
    cout << print << endl;

    vector<string> recruits = network[id];

    if (recruits.size() > 0) {
        layer++;
        for (auto& recruit : recruits) {
            print_network(recruit,layer);
        }
        layer--;
    }
    return;

}

void count_network(string id,int& count) {
    vector<string> recs = network[id];
    if (recs.size()==0) {
        return;
    }

    for (auto& rec : recs) {
        count++;
        count_network(rec,count);
    }
}

void count_n_depth (string id, int& count, vector<int>& counts) {
    vector<string> recruits = network[id];

    if (recruits.size() > 0) {
        count++;
        for (auto& recruit : recruits) {
            count_n_depth(recruit,count,counts);
        }
        counts.push_back(count+1);
        count--;
        return;
    }
    return;
}

int main()
{
    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!

            // if recruiter in map already
            if (network.find(id1) != network.end()) {
                network.at(id1).push_back(id2);
            } else {
                vector<string> recruited = {id2};
                network[id1] = recruited;
            }

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print_network(id, 0);


        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int c=0;
            count_network(id,c);

            cout << c << endl;


        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int c = 0;
            vector<int> counts {1};
            count_n_depth(id,c,counts);
            cout << *max_element(counts.begin(),counts.end()) << endl;
        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
