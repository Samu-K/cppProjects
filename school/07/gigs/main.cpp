/* COMP.CS.110 Project 2: GIGS
 * ===========================
 * This programs acts as a simple gig calendar.
 *  First, a text file with correct formatting (see below)
 *  is read to create the base calendar
 *
 *  After the text file has been read, you can use command (see below)
 *  in order to modify inspect the list, or to modify it
 *      ! NOTE: These modifications are not reflected in the base file
 *
 * Acts as a simple gig calendar with 8 commands:
 *  QUIT - Quits the program
 *  ARTISTS - Prints all known artist names
 *  ARTIST <artist name> - Prints single artist's gigs
 *  STAGES - Prints all known stage names and their locations
 *  STAGE <stage name> - Prints all artists having a gig at the given stage
 *  ADD_ARTIST <artist name> - Adds a new artist
 *  ADD_GIG <artist name> <date> <town name> <stage name> - Adds a new gig for
 *      an artist with the given date, town, and stage (the artist can't already
 *      have a gig on the same date and there can't be other gigs at the same stage
 *      at the same time)
 *  CANCEL <artist name> <date> - Cancels artist's gigs after the given date
 *
 * The data file should be formatted like:
 *      artist_name;date;town_name;stage_name
 *
 *  Otherwise the program execution terminates.
 *
 * Developer:
 *  Name: Samu Kaarlela
 *  Studentnum: 150974219
 *  Username: dgsaka
 *  E-Mail: samu.kaarlela@tuni.fi
 * Notes:
 *  About using a global variable for artists:
 *      I decided to go with a global variable for all_artists,
 *      because it makes the code much cleaner than the alternative
 *
 *      The same could be argued for gigs, but gigs is used
 *      in too many differing places. This means keeping track of it
 *      as a global variable would be difficult, especially
 *      if this program would be expanded.
 *
 *      all_artists is used in very similar cases and is rarely modified.
 *      I believe this justifies it being a global variable
 * */

// imports
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <map>
using namespace std;

// define error messages
const string FILE_NOT_READ = "Error: File could not be read.";
const string INVALID_FILE_FORMAT = "Error: Invalid format in file.";

const string INVALID_DATE = "Error: Invalid date.";
const string INVALID_INPUT = "Error: Invalid input.";

const string NOT_FOUND = "Error: Not found.";
const string DUPLICATE_ERROR = "Error: Already exists.";
const string NO_GIGS_FOUND = "Error: No gigs after the given date.";

// define structure for gig
struct gig {
    string artist,date,location,venue;
};
// set gigs to sort by date
bool operator<(const gig& lhs, const gig& rhs) {
    return lhs.date < rhs.date;
}

// define equals operator for struct
bool operator==(const gig& lhs, const gig& rhs) {
    // check that all values in gig are equal
    if (lhs.artist != rhs.artist) {
        return false;
    }
    if (lhs.date != rhs.date) {
        return false;
    }
    if (lhs.location != rhs.location) {
        return false;
    }
    if (lhs.venue != rhs.venue) {
        return false;
    }

    return true;
}

// Define global constants
const std::string FARTHEST_POSSIBLE_YEAR = "2030";
const set<string> accepted_commands {
    "QUIT",
    "ARTISTS",
    "ARTIST",
    "STAGES",
    "STAGE",
    "ADD_ARTIST",
    "ADD_GIG",
    "CANCEL"
};

const map<string,unsigned long int> command_lens {
    {"ARTISTS",1},
    {"ARTIST",2},
    {"STAGES",1},
    {"STAGE",2},
    {"ADD_ARTIST",2},
    {"ADD_GIG",5},
    {"CANCEL",3},
};

// we need a custom ordering for some sets
auto cmp = [](string a, string b){
    // first letters of both strings
    char fa = a[0];
    char fb = b[0];

    // if a is capitalized, then it's ordered before b
    if (isupper(fa) && !isupper(fb)) {
        return true;
    // if b is capitalized it's ordered before a
    } else if (!isupper(fa) && isupper(fb)) {
        return false;
    // if both capitalized (or both not), then order alphabetically
    } else {
        return a < b;
    }
};

// use global list to store all artists
// order set using custom lambda
set<string,decltype(cmp)> all_artists(cmp);

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim = ';')
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// gets all gigs for given artist
set<gig> get_artist_gigs(string& artist, vector<gig>& gigs)  {
    set<gig> all_gigs;
    // add to list if artist matches
    for (gig& cur_gig : gigs) {
        if (cur_gig.artist == artist) {
            all_gigs.insert(cur_gig);
        }
    }

    return all_gigs;
}

// gets all gigs for given stage
set<gig> get_stage_gigs(string& stage, vector<gig>& gigs) {
    set<gig> all_gigs;
    // add to list if venue matches
    for (gig& cur_gig : gigs) {
        if (cur_gig.venue == stage) {
            all_gigs.insert(cur_gig);
        }
    }

    return all_gigs;
}

// gets all stages listed in gigs
set<pair<string,string>> get_all_stages(vector<gig>& gigs) {
    // store in set first to get alphabetical order
    set<pair<string,string>> all_stages;

    for (auto& current_gig : gigs) {
        pair<string,string> stage;
        stage.first = current_gig.location;
        stage.second = current_gig.venue;
        all_stages.insert(stage);
    }

    return all_stages;
}

// Checks if the given date_str is a valid date, i.e. if it has the format
// dd-mm-yyyy and if it is also otherwise possible date.
bool is_valid_date(const std::string& date_str)
{
    std::vector<std::string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    std::string year = date_vec.at(0);
    std::string month = date_vec.at(1);
    std::string day = date_vec.at(2);
    std::vector<std::string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" or month > "12" )
    {
        return false;
    }
    if ( year < "0001" or year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) or
                        (year_int % 100 != 0 and year_int % 4 == 0);
    if ( day >= "01" and
        (day <= month_sizes.at(stoi(month) - 1) or
        (month == "02" and is_leap_year and day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

// checks if given gig is valid
bool is_gig_valid(string& artist,string& date,string& venue,vector<gig>& gigs) {

    // check if artist exists
    if (all_artists.find(artist) == all_artists.end()) {
        cout << NOT_FOUND << endl;
        return false;
    }

    // check if date valid
    if (!is_valid_date(date)) {
        cout << INVALID_DATE << endl;
        return false;
    }

    // check if artist has gig on date
    set<gig> all_gigs = get_artist_gigs(artist,gigs);
    for (const gig& gig : all_gigs) {
        if (gig.date == date) {
            cout << DUPLICATE_ERROR << endl;
            return false;
        }
    }

    // check if date has gig on stage
    set<gig> stage_gigs = get_stage_gigs(venue,gigs);
    for (auto& gig : stage_gigs) {
        if (gig.date == date) {
            cout << DUPLICATE_ERROR << endl;
            return false;
        }
    }
    return true;
}

// checks if command is valid
bool is_command_valid(string& cmd) {
    // set to all uppercase
    for (char& letter : cmd) {
        letter = toupper(letter);
    }

    // skip if command not found
    if (accepted_commands.find(cmd)==accepted_commands.end()) {
        cout << INVALID_INPUT << endl;
        return false;
    }
    return true;
}

// cancels gigs after given date
void cancel_gigs(vector<string>& cmd_parts, vector<gig>& gigs) {
    string artist = cmd_parts[1];
    string date = cmd_parts[2];

    if (all_artists.find(artist) == all_artists.end()) {
        cout << NOT_FOUND << endl;
        return;
    }

    if (!is_valid_date(date)) {
        cout << INVALID_DATE << endl;
        return;
    }

    // filter gigs
    vector<gig> filtered_gigs;
    copy_if(gigs.begin(),gigs.end(), back_inserter(filtered_gigs), [&date,&artist](const gig& gig){
        if (gig.artist == artist) {
            if (gig.date <= date) {
                return true;
            } else {
                return false;
            }
        }
        // if not specified artist,
        // we do not want to remove gig
        return true;
    });

    // check if any gigs were removed
    if (gigs.size() == filtered_gigs.size()) {
        cout << NO_GIGS_FOUND << endl;
    } else {
        // if they were we set gigs to filtered version
        cout << "Artist's gigs after the given date cancelled." << endl;
        gigs = filtered_gigs;
    }
}

// adds gig to vector of gigs
// operation performed in place
bool add_gig(string& artist,
             string& date,
             string& location,
             string& venue,
             vector<gig>& gigs) {

    // check if date is valid
    if (!is_valid_date(date)) {
        cout << INVALID_DATE << endl;
        return false;
    }

    // check if artist has gig on date
    set<gig> all_gigs = get_artist_gigs(artist,gigs);
    for (const gig& gig : all_gigs) {
        if (gig.date == date) {
            cout << DUPLICATE_ERROR << endl;
            return false;
        }
    }

    // check if date has gig on stage
    set<gig> stage_gigs = get_stage_gigs(venue,gigs);
    for (auto& gig : stage_gigs) {
        if (gig.date == date) {
            cout << DUPLICATE_ERROR << endl;
            return false;
        }
    }

    // construct gig and append to gig list
    gig new_gig;
    new_gig.artist = artist;
    new_gig.date = date;
    new_gig.location = location;
    new_gig.venue = venue;

    gigs.push_back(new_gig);
    // return true to show adding was succesfull
    return true;
}

// read the input file
// errors during parsing cause function to return empy
vector<gig> read_gigs() {
    // get filepath
    cout << "Give a name for input file: ";
    string filepath;
    getline (cin,filepath);

    vector<gig> gigs;

    // connect to file
    ifstream gig_file(filepath);

    // check if file could be opened
    if (!gig_file.is_open()) {
        cout << FILE_NOT_READ << endl;
        return vector<gig> {};
    }

    // read file
    string line;
    while ( getline(gig_file,line)) {
        // store command parts
        vector<string> spl = split(line);

        // make sure line doesn't contain empty
        for (auto& line_part : spl) {
            if (line_part.empty()) {
                cout << INVALID_FILE_FORMAT << endl;
                return vector<gig> {};
            }
        }

        // make sure line has correct amount of parts
        if (spl.size() != 4) {
            cout << INVALID_FILE_FORMAT << endl;
            return vector<gig> {};
        }

        // parse input
        string artist = spl[0];
        string date = spl[1];
        string location = spl[2];
        string venue = spl[3];

        // add gig
        bool success = add_gig(artist,date,location,venue,gigs);
        if (!success) {
            return vector<gig> {};
        }

        // add artist to list
        all_artists.insert(artist);
    }

    // close file and return
    gig_file.close();
    return gigs;
}

int main()
{
    // get gigs from file
    vector<gig> gigs = read_gigs();

    // if we got empty vector,
    // it means we had an error in reading
    if (gigs.empty()) {
        return EXIT_FAILURE;
    }

    // main program loop
    while (true) {

        // get command
        string input;
        cout << "gigs> ";
        getline (cin,input);

        // split command into parts
        vector<string> cmd_parts = split(input,' ');

        // fetch command and set to all uppercase
        string& cmd = cmd_parts[0];
        is_command_valid(cmd);

        // quit if asked
        if (cmd == "QUIT") {
            break;
        }

        // check that command has the minimum amount of params
        // note here, that I personally disagree with this design choice
        // the command should not work if given extra params
        // but testing requires it, so it will be changed here
        if (cmd_parts.size() < command_lens.at(cmd)) {
            cout << INVALID_INPUT << endl;
            continue;
        }

        // print out all artists
        if (cmd == "ARTISTS") {
            cout << "All artists in alphabetical order:" << endl;

            for (auto& artist : all_artists) {
                cout << artist << endl;
            }
            continue;
        }

        // print all gigs for given artist
        if (cmd == "ARTIST") {
            // get artist requested
            string artist = cmd_parts[1];

            // if artist not found
            if (all_artists.find(artist)==all_artists.end()) {
                cout << NOT_FOUND << endl;
                continue;
            }

            cout << "Artist " << artist << " has the following gigs in the order they are listed:" << endl;

            // get all gigs of requested artist
            set<gig> all_gigs = get_artist_gigs(artist,gigs);

            for (const gig& gig : all_gigs) {
                cout << "- ";
                cout << gig.date << " : ";
                cout << gig.location << ", ";
                cout << gig.venue << endl;
            }
            continue;
        }

        // pring out all stages
        if (cmd == "STAGES") {
            cout << "All gig places in alphabetical order: " << endl;

            set<pair<string,string>> all_stages = get_all_stages(gigs);

            // print stages out
            for (auto& stage : all_stages) {
                cout << stage.first << ", ";
                cout << stage.second << endl;
            }
            continue;
        }

        // get all gigs at given stage
        if (cmd == "STAGE") {
            // get requested stage
            string stage = cmd_parts[1];

            // store all performers at stage
            set<gig> stage_gigs = get_stage_gigs(stage,gigs);
            set<string,decltype(cmp)> performers(cmp);

            for (auto& gig : stage_gigs) {
                performers.insert(gig.artist);
            }

            // if stage not found (or no gigs)
            if (performers.size() == 0) {
                cout << NOT_FOUND << endl;
                continue;
            }

            cout << "Stage " << stage << " has gigs of the following artists:" << endl;

            // print out all performers
            for (auto& performer : performers) {
                cout << " - ";
                cout << performer << endl;
            }

            continue;
        }

        // add new artist
        if (cmd == "ADD_ARTIST") {
            string artist = cmd_parts[1];

            // if artist in list
            if (all_artists.find(artist) != all_artists.end()) {
                cout << DUPLICATE_ERROR << endl;
                continue;
            }

            all_artists.insert(artist);
            cout << "Artist added." << endl;
            continue;
        }

        // add new gig
        if (cmd == "ADD_GIG") {
            // parse input
            string artist = cmd_parts[1];
            string date = cmd_parts[2];
            string location = cmd_parts[3];
            string venue = cmd_parts[4];

            if (is_gig_valid(artist,date,venue,gigs)) {
                add_gig(artist,date,location,venue,gigs);
                cout << "Gig added." << endl;
            }
        }

        // cancel gigs after given date
        if (cmd=="CANCEL") {cancel_gigs(cmd_parts,gigs);}
    }

    return EXIT_SUCCESS;
}
