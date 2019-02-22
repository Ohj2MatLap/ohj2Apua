#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\n P = print id\n"
                              "C = count id\n D = depth id";

class person{
    public:
        person(string name, vector<string> hired_people);
        void add_person_to_vector(string new_hired_person);
        void print_hired_people(vector<string> hired_people_,string name);
        vector<string> get_vector();
        string get_name();
    private:
        string name_;
        vector<string> hired_people_;//Ei käytetä settiä, koska set on defaultina aakkosjärjestyksessä
};
person::person(string name, vector<string> hired_people):
    name_(name), hired_people_(hired_people)  {
}

vector<string> person::get_vector(){
    return hired_people_;
}

string person::get_name(){
    return name_;
}

void person::add_person_to_vector(string new_hired_person){
    hired_people_.push_back(new_hired_person);
}
void person::print_hired_people(vector<string> hired_people_, string name){
    cout<<name<<endl;
    // Creating a iterator pointing to start of set
    std::vector<std::string>::iterator it = hired_people_.begin();

    // Iterate till the end of set
    while (it != hired_people_.end())
    {
        // Print the element
        std::cout << (*it) << " , ";
        //Increment the iterator
        it++;
    }
}

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

//Käsky D
//vektori sisältää henkilöiden väliset etäisyydet
vector<int> depth(map<string,person> mymap, const string name,int i,vector<int> vec = {}){
    int time_plus = i+1;//ei käytetä ++time koska se lisää time arvoa, joka loopilla
    vec.push_back(time_plus);
    for(auto f : mymap.at(name).get_vector()){
          return depth(mymap, f,time_plus,vec);
    }
    //Palauttaa vektorin kun ollaan mapin viimeisessä arvossa
    if(name==mymap.rbegin()->first){
        return vec;
    }
    return vec;
}

//Käsky C
int count(map<string,person> mymap, const string name){
    int i = 0;
    for(auto f : mymap.at(name).get_vector()){
        i += 1;
        i += count(mymap,f);
    }
    return i;
}

//Käsky P
void command_p(map<string,person> mymap, const string name,int time){
    cout<<string(time*2,'.')<<name<<endl;
    int time_plus = time+1;//ei käytetä ++time koska se lisää time arvoa, joka loopilla
    for(auto f : mymap.at(name).get_vector()){
            command_p(mymap, f,time_plus);
    }
}

int main()
{
    // TODO: Implement the datastructure here
    map<string,person> all_persons;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            //Lisää id1 jos id1 ei löydy mapista
            //Jos id1 löytyy mapista, lisää id2 settiin
            if(all_persons.find(id1) == all_persons.end()){
                person new_person(id1,{id2});
                all_persons.insert({id1,new_person});
            }
            else{
                all_persons.at(id1).add_person_to_vector(id2);
            }
            //Jos id2 ei löydy mapista lisää se sinne
            //Huom new_person(name,set<string>) set on tyhjä
            if(all_persons.find(id2) == all_persons.end()){
                person new_person(id2,{});
                all_persons.insert({id2,new_person});
            }

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            command_p(all_persons,id,0);


        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            cout<<count(all_persons,id)<<endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            vector<int> vec = depth(all_persons,id,0);
            cout<<*max_element( vec.begin(), vec.end())<<endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
