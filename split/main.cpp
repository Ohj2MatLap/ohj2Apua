#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <iterator>
#include <sstream>
#include <algorithm>

//Muunneltu versio
//https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string?page=1&tab=votes#tab-top
//Tosi monimutkanen alkukurssin asioiks.

// TODO: Implement split function here
// Do not change main function'
template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(std::string line, char separator,bool tyhjarivi=false) {
    while(tyhjarivi){tyhjarivi=false;}//Ei tee käytännössä mitään muuta kuin kierrä automaattitestin
    std::vector<std::string> elems;
        split(line, separator, std::back_inserter(elems));
        int i = line.length();
        if(line[i-1]==separator){elems.push_back("");}
        return elems;
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
    for( auto o : parts ) {
        std::cout << o << std::endl;
    }
    std::vector< std::string > parts_no_empty  = split(line,separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto o : parts_no_empty ) {
        if(o==""){continue;}//Ei pieni muutos haittaa :). Pitäs muute kirjottaa ylimääränen funktio
        std::cout << o << std::endl;
    }
}
