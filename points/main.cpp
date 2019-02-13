#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <iterator>

using namespace std;
int main()
{
    map<string,int> players_and_points;

    //Get input file name
    string input_file_name;
    cout<<"Input file: ";
    getline(cin,input_file_name);

    //Test if file exist
    ifstream input_file(input_file_name);
    if (not input_file) {
        cout <<"Error! The file "<<input_file_name<<" cannot be opened."<< endl;
        return EXIT_FAILURE;
    }

    //Add points to players
    string rivi;
    int split_point;
    string name;
    int points;
    while(getline(input_file,rivi)){
        split_point = rivi.find(":");
        name = rivi.substr(0,split_point);
        points = stoi(rivi.substr(split_point+1));
        if(players_and_points.find(name) != players_and_points.end() ){
            players_and_points[name]+=points;
        }
        else{players_and_points[name] = points;}
    }

    //print player names and points in sorted order
    cout<<"Final scores:"<<endl;
    for ( auto it = players_and_points.begin(); it != players_and_points.end(); ++it  )
    {
       cout << it->first << ": " << it->second << std::endl;
    }
    input_file.close();
}
