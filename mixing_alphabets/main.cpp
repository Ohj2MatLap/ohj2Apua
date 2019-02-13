#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;
    std::string cut_word; //Word without first and last letter

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
        cut_word = word.substr(1,word.length()-2);
        shuffle(cut_word.begin(), cut_word.end(),generator);
        if (word.length() == 1){std::cout << word<<std::endl;}
        else{
        std::cout <<word.substr(0,1) << cut_word <<word.substr(word.length()-1,1)<< std::endl;
        }
    }
}
