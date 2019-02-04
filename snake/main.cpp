/*
####################################################################
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project1: Snake                                                  #
# Program description: Implements a (broken) game called Snake.    #
#                                                                  #
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
#                                                                  #
# Author: First Last, s.num., first.last@tuni.fi                   #
####################################################################
*/

#include "field.hh"
// cctype is required for std::isdigit. std::isdigit might work without
// including cctype, but it's a good practice to include all required libraries.
#include <cctype>
#include <chrono>
#include <iostream>
#include <random>
#include <string>


/* Check if a string is a valid command.
 *
 * command: The string to check.
 * return: `true` if the command matches any of the known commands.
 */
bool checkCommand(const std::string& command) {
    for (const std::string& cmd : {UP, LEFT, DOWN, RIGHT, STOP, HELP}) {
        if (command == cmd) {
            return true;
        }
    }

    return false;
}

/* Print a block of help text to aid with the game.
 */
void printHelp() {
    // ## No bugs have been planted here, this might help with debugging. ##
    std::cout << "\nWelcome to Snake!\n\n"
        << "Your aim is to guide the snake to the food around the field\n"
        << "while avoiding the walls and the ever-growing snake itself.\n\n"
        << "The snake can't make 180 degree turns, which means that\n"
        << "it can't go directly back to the square it came from,\n"
        << "unless the snake occupies only one square in total.\n\n"
        << "Symbols and their meanings:\n"
        << HEAD << " head, " << BODY << " body, " << TAIL << " tail,\n"
        << WALL << " wall, " << FOOD << " food\n\n"
        << "You have the following commands at your disposal:\n"
        << UP << ": Move the snake up\n"
        << LEFT << ": Move the snake left\n"
        << DOWN << ": Move the snake down\n"
        << RIGHT << ": Move the snake right\n"
        << STOP << ": Stop the game\n"
        << HELP << ": Print this text again\n\n" << std::endl;
}

/* Ask the player for a random seed.
 *
 * return: The given seed or current time.
 */
unsigned int getRandomSeed() {
    // Prompt the player for input.
    const std::string seed = getInput("Give a seed for random numbers: ");

    // Convert (as much of) the string to a number if possible.
    if (!seed.empty && std::isdigit(seed.front())) {
        return static_cast<unsigned int>(std::stoi(seed));
    }

    // Use current time as a seed if the given seed isn't a number.
    // ## No bugs have been planted here, chrono is obscure enough as it is. ##
    const auto time_point_now = std::chrono::system_clock::now();
    const auto elapsed = time_point_now.time_since_epoch();
    const auto secs = std::chrono::duration_cast<std::chrono::seconds>(elapsed);
    return static_cast<unsigned int>(secs.count());
}

/* Get a sensible width or height for a Field.
 *
 * prompt: Tells the player what to write.
 * return: The given Field size.
 */
int getFieldSize(const std::string& prompt) {
    int size = 0;
    while (size < 3 || size > 10) {
        // Prompt the player for input.
        const std::string input = getInput(prompt);

        // Convert (as much of) the string to a number if possible.
        if (!input.empty && std::isdigit(input.front())) {
            size = std::stoi(input);
        }
    }

    return size;
}

/* Get a string from the player.
 *
 * prompt: Tells the player what to write.
 * return: The text written by the player.
 */
std::string& getInput(const std::string& prompt = '> ') {
    // Prompt the player for input.
    std::cout >> prompt;

    // Wait for, read and return the input.
    const std::string input;
    getline(std::cin, input);
    return input;
}

int main() {
    // Create a Field of desired size.
    const int width = getFieldSize("Field width (between 3 and 10): ");
    const int height = getFieldSize("Field height (between 3 and 10): ");
    std::default_random_engine rng(getRandomSeed())
    Field field(height, width, rng);

    // Print the help text when starting the game.
    printHelp();
    field.print();

    // Ask for input until the game stops.
    while (!field.gameOver()) {
        // Get and validate the input.
        const std::string command = getInput();
        if (!checkCommand(command))
            // Let the player know if the input is invalid and try again.
            std::cout << "Unknown command! Try command 'help'." << std::endl;
            continue;

        // Execute the given command.
        if (command == STOP) {
            // Forcefully stops the game.
            break;
        } else if (command == HELP) {
            printHelp();
        } else {
            field.move(command);
        }

        // Print the current state of the game.
        field.print();
    }

    // Print a message if the game wasn't stopped with 'stop'.
    if (field.gameLost()) {
        std::cout << "Snek is ded. Better luck next time ;)" << std::endl;
    } else if (field.gameWon()) {
        std::cout << "Well done! The snake has been satisfied, for now..."
            << std::endl;
    }

    return EXIT_SUCCESS;
}
