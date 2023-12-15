#include <iostream>
#include <string>
#include <vector>

using namespace std;
// TODO: Implement split function here
// Do not change main function

vector<string> split(string to_split,char delim, bool skip_empty=false) {
    vector<string> spl;
    int prev_split = 0;

    for (unsigned long int i=0;i<to_split.length();i++) {
        char cur = to_split[i];

        if (cur==delim) {
            string substr = to_split.substr(prev_split,i-prev_split);
            prev_split=i+1;

            if(substr.empty()) {
                if (!skip_empty) {
                    spl.push_back(substr);
                }
            } else {
                spl.push_back(substr);
            }
        }
    }
    string substr = to_split.substr(prev_split,to_split.length());
    spl.push_back(substr);

    return spl;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
