#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    set<string> words;

    //Get input file name
    string input_file_name;
    cout<<"Input file: ";
    getline(cin,input_file_name);

    //Check if file exist
    ifstream input_file(input_file_name);
    if (not input_file) {
        cout <<"Error! The file "<<input_file_name<<" cannot be opened."<< endl;
        return EXIT_FAILURE;
    }

    //read file and add words to set<string> words
    string row;
    string word;
    while(getline(input_file,row)){
        std::istringstream iss(row);
        for(std::string row; iss >> row; )
            words.insert(row);//row is here a one word
    }

    //Loops words
    set<string>::iterator iter;
    int row_number;
    int amount_of_finds;
    string rows_indexes;//rows where word was found example (1, 2, 4)
    for(iter=words.begin(); iter!=words.end();++iter) {
        //Prints set words
        cout<<*iter<<" ";

        //Reseting file before reading it again
        input_file.clear();
        input_file.seekg(0, input_file.beg);

        //Prints the amount of finds
        amount_of_finds = 0;
        while(getline(input_file,row)){
            std::istringstream iss(row);
            for(std::string row; iss >> row;){
                if(*iter==row){amount_of_finds+=1;
                break;}//row is here a one word
            }
        }
        cout<<amount_of_finds<<": ";

        //Reseting file before reading it again
        input_file.clear();
        input_file.seekg(0, input_file.beg);

        //Prints row numbers, where word is included
        row_number = 1;
        rows_indexes = "";
        while(getline(input_file,row)){
            std::istringstream iss(row);
            for(std::string row; iss >> row;){
                if(*iter==row){rows_indexes=rows_indexes+to_string(row_number)+", ";
                break;}
            }
            row_number+=1;
        }
        cout<<rows_indexes.substr(0,rows_indexes.length()-2)<<endl;//rows_indexes.length()-2 cuts of the extra ", "
    }
    input_file.close();

    return EXIT_SUCCESS;
}
