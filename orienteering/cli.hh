/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Project3: Suku on pahin                                                   #
# File: cli.hh                                                              #
# Description: Commandline interface for the program.                       #
# Notes: * This is a part of an exercise program                            #
#        * Student's don't touch this file.                                 #
#        * Understanding how the module works isn't necessary to complete   #
#          this exercise.                                                   #
#        * This is also an example how you can use function pointers to     #
#          a class' functions.                                              #
#        * This could be upgraded to have commandhistory with a relative    #
#          ease.                                                            #
#############################################################################
*/
#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <memory>

#include "routes.hh"

/* In order to define a function pointer to a class you have to add
 * class as the visibility range before the pointer declaring * and
 * after that comes the type-name for the pointer.
 * In this case we have named the types according to the amount of
 * parameters the function receives.
 */

using noparam = void (Routes::*)() const;
using oneparam = void (Routes::*)(const std::string&) const;
using twoparam = void (Routes::*)(const int&, const int&) const;

// CommandInfo contains the list of strings that select it and
// Function-pointers to the function that is going to be called through it.
struct CommandInfo
{
    std::vector<std::string> lines_;
    noparam func0_;
    oneparam func1_;
    twoparam func2_;
};


class Cli
{
public:
    // The database that is going to be used is given as a parameter.
    Cli(std::shared_ptr<Routes> db);

    /* Description: Runs the interface.
     * Return values:
     *  True    - Normal command
     *  False   - Exit command
     */
    bool exec_prompt();

private:
    std::shared_ptr<Routes> database_;

    // Stores the arguments from current command.
    std::vector<std::string> args_;

    // Pointer to the recognized command.
    const CommandInfo* recognized_;

    // Printed for every query
    const std::string PROMPT = "CMD> ";

    // Parses the given input to different arguments
    void parseCommand(const std::string& line);

    /* Description: Sets the recognized_ to point at the correct
     * CommandInfo.
     * Return values:
     *  Amount of arguments - Command can be executed
     *  -1                  - Exit command
     *  -2                  - Invalid amount of parameters
     *  -3                  - Command not recognized.
     */
    int checkCommandType();

    // To make code more readable. Could also be different constants but this
    // groups them better.
    enum Commandtypes {QUIT = -1, NO_PARAMETERS = 1, ONE_PARAMETER = 2,
                       TWO_PARAMETER = 3, FIVE_PARAMETER = 6,EMPTY = 0, UNKNOWN = -3,
                       WRONG_PARAMETERS = -2};


    // Constant table that contains the different commands that the CLI can
    // recognize.
    std::vector<CommandInfo> const COMMANDS = {
        {{"EXIT","QUIT","Q","LOPETA"}, nullptr, nullptr, nullptr},
        {{"MAP","KARTTA","P", "M", "K", "PRINT"}, &Routes::print_map, nullptr, nullptr},
        {{"ROUTES", "REITIT", "R"}, &Routes::print_route_names, &Routes::print_route, nullptr},
        {{"ROUTE", "REITTI"}, nullptr, &Routes::print_route, nullptr},
        {{"LENGTH", "PITUUS", "L"}, nullptr, &Routes::route_length, nullptr},
        {{"NOUSU", "RISE", "GREATEST"}, nullptr, &Routes::greatest_rise, nullptr},
        {{"POINTS", "PISTEET"}, &Routes::print_points, nullptr, nullptr},
        {{}, nullptr, nullptr, nullptr}
    };


};

#endif // CLI_H
