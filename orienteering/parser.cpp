#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "parser.hh"

const std::string ERROR_IN_FORMAT = "Error: Incorrect line in input file";

bool read_size(std::ifstream &file, std::shared_ptr<Routes> routes);
bool read_points(std::ifstream &file, std::shared_ptr<Routes> routes);
bool read_routes(std::ifstream &file, std::shared_ptr<Routes> routes);
void split_line(std::vector<std::string>& res, std::string& line);
bool is_number(std::string& str);

void split_line(std::vector<std::string>& res, std::string& line){
    res.push_back("");
    for ( char c : line ){
        if ( c == ';' ){
            res.push_back("");
        } else {
            res.back() += c;
        }
    }
}

bool is_number(std::string& str){
    return std::any_of(str.begin(), str.end(), ::isdigit);
}

bool read_size( std::ifstream& file, std::shared_ptr<Routes> routes){
    std::string line;
    getline( file, line);
    std::vector<std::string> temp;
    split_line(temp, line);
    if ( temp.size() == 2 && is_number(temp.at(0)) && is_number(temp.at(1)) ){
        routes->set_map_size(std::stoi(temp.at(0)),
                             std::stoi(temp.at(1)));
        return true;
    } else {
        std::cout << ERROR_IN_FORMAT << std::endl;
        return false;
    }
}

bool read_points( std::ifstream& file, std::shared_ptr<Routes> routes){
    std::vector<std::string> temps;
    std::string line;
    while ( getline( file, line) ){
        if ( line == "ROUTES" ){
            return true;
        }
        temps.clear();
        split_line(temps, line);
        if ( temps.size() != 5
             || !is_number(temps.at(1))
             || !is_number(temps.at(2))
             || !is_number(temps.at(3))
             || temps.at(4).size() != 1){
            std::cout << ERROR_IN_FORMAT << std::endl;
            return false;
        } else {
            routes->add_point(temps.at(0),
                              std::stoi(temps.at(1)),
                              std::stoi(temps.at(2)),
                              std::stoi(temps.at(3)),
                              temps.at(4)[0]);
        }
    }
    return true;
}

bool read_routes( std::ifstream& file, std::shared_ptr<Routes> routes ){
    std::vector<std::string> temp;
    std::string line, route;
    while ( getline(file, line) ){
        temp.clear();
        split_line(temp, line);
        if ( temp.size() > 2 ){
            route = temp.at(0);
            for (unsigned int i = 2 ; i < temp.size(); ++i ){
                if ( !(routes->connect_route( temp.at(i - 1), temp.at(i), route)) ){
                    return false;
                }
            }
        } else {
            std::cout << ERROR_IN_FORMAT << std::endl;
            return false;
        }

    }
    return true;
}

bool read_input_from_file( std::string file, std::shared_ptr<Routes> routes ){
    std::ifstream input(file);
    if ( !input ){
        std::cout << "Error: Can't read file" << std::endl;
        return false;
    }
    return (read_size(input, routes) && read_points(input, routes) && read_routes(input, routes));
}
