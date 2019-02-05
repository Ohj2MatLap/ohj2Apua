#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values(std::vector<int> integers){
    //Palauttaa arvon true, jos kaikki arvot ovat samoja
    //Huom! #include <algorithm>
    if (std::adjacent_find(integers.begin(), integers.end(), std::not_equal_to<int>() ) == integers.end() )
    {
        return true;
    }
    else{
        return false;
    }
}

bool is_ordered_non_strict_ascending(std::vector<int> integers){
    //Palauttaa arvon true, jos arvot ovat kasvavassa järjestyksessä
    int b = integers.at(0);
    for(int i : integers){
        if(i<b){return false;}
        else{b=i;}
    }
    return true;
}
bool is_arithmetic_series(std::vector<int> integers){
    //Palauttaa arvon true, jos kaikien arvojen kahden peräkkäisen arvon erotus on vakio
    bool first = true;
    int vakio = integers.at(0)-integers.at(1);
    int edeltava_arvo = integers.at(0);
    for(int i : integers){
        if (first)
            { first = false; continue; }
        if (edeltava_arvo-i==vakio){
            edeltava_arvo=i;
            continue;}
        else{return false;}
    }
    return true;
}

bool is_geometric_series(std::vector<int> integers){
    //Palauttaa arvon true, jos peräkkäisten arvojen osamäärä on vakio
    bool first = true;
    int vakio = integers.at(0)/integers.at(1);
    int edeltava_arvo = integers.at(0);
    for(int i : integers){
        if (first)
            { first = false; continue; }
        if (edeltava_arvo/i==vakio){
            edeltava_arvo=i;
            continue;}
        else{return false;}
    }
    return true;
}



int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
