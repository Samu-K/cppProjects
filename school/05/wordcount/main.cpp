#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>

using namespace std;

int main()
{
    string input_fp;

    cout << "Input file: ";
    cin >> input_fp;

    ifstream input(input_fp);

    if (!input.is_open()) {
        cout << "Error! The file "<< input_fp << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    string line;
    map<string,pair<int,string>> word_counts;

    int row_index = 1;

    // loop through all input
    while (getline(input,line)) {
        string word;
        stringstream line_s(line);
        vector<string> handled;

        // loop through each word in input
        while ( getline(line_s, word, ' ') ) {
            if (word_counts.find(word) == word_counts.end()) {

                pair<int,string> appears (1,to_string(row_index));
                pair<string,pair<int,string>> word_count(word,appears);

                word_counts.insert(word_count);
                handled.push_back(word);

            } else {
                if (count(handled.begin(),handled.end(),word) == 0) {
                    word_counts.at(word).first += 1;
                    word_counts.at(word).second += ", " + to_string(row_index);
                    handled.push_back(word);
                }
            }
        }

        ++row_index;
    }

    for (auto count : word_counts) {
        cout << count.first
             << " " << count.second.first << ": "
             << count.second.second << endl;
    }

    return 0;
}
