#include "calculations.hh"
#include <iostream>
#include <iomanip>
#include <sstream>  // for implementing function string_to_double
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const string GREETING_AT_END = "Thanks and see you later!";

// Utility function to sections a string at delimiters
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty = false);

// Function string_to_double changes a string comprising a real number
// into a float type value for calculations.
// It returns true, if parameter s comprised a real.
// It returns false, if s was not a valid real number.
// The converted float will be assigned into reference parameter result.
// The implementation of the function uses stringstream for the sake of example.
bool string_to_double(const string& s, double& result);


// TODO: Explore the following data structures!
struct Command {
    string str;
    vector<string>::size_type parameter_number;
    bool exit;
    double(*action)(double, double);
};

const vector<Command> COMMANDS = {
    {"+", 2, false, addition},
    {"-", 2, false, subtraction},
    {"*", 2, false, multiplication},
    {"/", 2, false, division},
    {"PLUS", 2, false, addition},
    {"MINUS", 2, false, subtraction},
    {"TIMES", 2, false, multiplication},
    {"DIVIDED", 2, false, division},
    {"ADDITION", 2, false, addition},
    {"SUBTRACTION", 2, false, subtraction},
    {"MULTIPLICATION", 2, false, multiplication},
    {"DIVISION", 2, false, division},
    {"SUM", 2, false, addition},
    {"DIFFERENCE", 2, false, subtraction},
    {"PRODUCT", 2, false, multiplication},
    {"QUOTIENT", 2, false, division},
    {"ADD", 2, false, addition},
    {"INCREASE", 2, false, addition},
    {"SUBTRACT", 2, false, subtraction},
    {"DECREASE", 2, false, subtraction},
    {"MULTIPLY", 2, false, multiplication},
    {"^", 2, false, potens},
    {"POWER", 2, false, potens},
    {"EXP", 2, false, potens},
    {"DIVIDE", 2, false, division},
    {"STOP", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr}
};


int main() {

    // Using precision of two decimals in printing
    cout.precision(2);
    cout << fixed;

    while ( true ) {
        cout << "calculator> ";

        string line = "";
        getline(cin, line);

        if ( line.empty() ) {
            // If the user inputs an empty line, the execution of the program will end.
            cout << GREETING_AT_END << endl;
            break;
        }

        vector<string> pieces = split(line, ' ', true);

        if(pieces.size() == 0){
            continue;
        }

        string command_to_be_executed = pieces.at(0);
        std::transform(command_to_be_executed.begin(), command_to_be_executed.end(),command_to_be_executed.begin(), ::toupper);

        // TODO: Implement command execution here!
        bool command_found = false;
        if(pieces.size() == 1 && (command_to_be_executed=="STOP" ||
                command_to_be_executed=="QUIT" ||
                command_to_be_executed=="EXIT" ||
                command_to_be_executed=="Q"))
        {
            cout<<"Thanks and see you later!"<<endl;
            return EXIT_SUCCESS;
        }
        for(auto i : COMMANDS){
            if(i.str == command_to_be_executed){
                command_found = true;
            }
        }
        if(command_found==false){
            cout<<"Error: unknown command."<<endl;
            continue;
        }
        if(command_found){
            if(pieces.size()!= 3){
                command_found = true;
                cout<<"Error: wrong number of parameters."<<endl;
                continue;
            }
        }
        if(command_found){
            for(auto i : COMMANDS){
                if(i.str == command_to_be_executed){
                    try {
                        stoi(pieces.at(1).c_str());
                        stoi(pieces.at(2).c_str());
                         double first_num = atof(pieces.at(1).c_str());
                         double second_num = atof(pieces.at(2).c_str());
                         double result = i.action(first_num,second_num);
                         cout<<result<<endl;
                         break;
                        }catch (exception) {
                         cout<<"Error: a non-number operand."<<endl;
                         command_found = false;
                         break;
                        }
                }
            }
        }
    }
}


// This function exemplifies istringstreams.
// It would be possible to use function stod of string to convert a string to a double,
// but to recognize all error cases would be more complicated with it at this phase of
// education. It is easier to use the boolean type return value that can be
// examined at calling point as done in the implementation below.
bool string_to_double(const string& s, double& result) {
    // Initializing input stream of istringstream type the string that will scanned
    // with ">>" or getline.
    istringstream stream(s);

    double tmp;

    // Reading input value in a normal way with ">>" operator.
    // You can operate istringstreams with the same operations as cin
    // and other ifstreams.
    stream >> tmp;

    if ( not stream ) {
        return false;
    }

    // ws is special operator that skips all the word delimiters (such as spaces)
    // until it meets something else
    stream >> ws;

    // If parameter s is a string comprising a valid real number, it cannot succeed
    // other characters than spaces.
    // Since previous ">> ws" operation threw the spaces away, at this point
    // the input stream should contain nothing. If it does, then it is erroneous.
    // Let's try to read a character from the input stream.
    // If this fails, because the input stream has no characters left, then all is right.
    // If it succeeds, then string s has something that it should not have.
    stream.get();

    if ( stream ) {
        return false;
    } else {
        result = tmp;
        return true;
    }
}

// Model implementation of good old split function
vector< string > split(const string& s, const char delimiter, bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
