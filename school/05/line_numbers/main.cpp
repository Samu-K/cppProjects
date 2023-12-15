#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main()
{
    string input_fp;
    string output_fp;

    cout << "Input file: ";
    cin >> input_fp;

    cout << "Output file: ";
    cin >> output_fp;

    ifstream input(input_fp);
    if (!input.is_open()) {
        cout << "Error! The file " + input_fp + " " + "cannot be opened." << endl;

        return EXIT_FAILURE;
    }

    ofstream output(output_fp);

    int counter = 1;
    string line;

    while(getline(input,line)) {
        string new_l = to_string(counter) + " " + line;

        output << new_l;
        output << endl;
        ++counter;
    }
    input.close();
    output.close();

    return 0;
}
