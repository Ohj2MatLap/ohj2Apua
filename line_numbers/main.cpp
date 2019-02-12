#include <iostream>
#include <fstream>  // Huomaa kirjasto
#include <string>

using namespace std;

int main() {
    string input_file_name;
    cout<<"Input file: ";
    getline(cin,input_file_name);
    cout<<"Output file: ";
    string output_file_name;
    getline(cin,output_file_name);


    ifstream input_file(input_file_name);
    ofstream output_file;


    if (not input_file) {
        cout <<"Error! The file "<<input_file_name<<" cannot be opened."<< endl;
        return EXIT_FAILURE;
    }
    else{
        output_file.open(output_file_name);
        int rivinumero = 1;
        string rivi;
        while ( getline(input_file, rivi) ) {
           output_file<<rivinumero<<" "<<rivi<<endl;
           rivinumero++;
        }
        input_file.close();
        output_file.close();
    }



}
