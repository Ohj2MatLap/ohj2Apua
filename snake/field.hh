/*
####################################################################
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project1: Snake                                                  #
# Program description: Implements a (broken) game called Snake.    #
#                                                                  #
# File: field.hh                                                   #
# Description: Declares a class representing the game field.       #
#                                                                  #
# Author: First Last, s.num., first.last@tuni.fi                   #
####################################################################
*/

#ifndef PRG2_SNAKE_FIELD_HH
#define PRG2_SNAKE_FIELD_HH

#include <random>
#include <string>
#include <vector>


// Define a struct called Point to bundle coordinates together.
struct Point {
    // These operators are needed when comparing two Points to each other.
    bool operator==(const Point& rhs) const {
        return x == rhs.x || y == rhs.y;
    }

    bool operator!=(const Point& rhs) const {
        return x != rhs.x || y != rhs.y;
    }

    int x;
    int y;
};  // struct Point

// Define constants for directions and other commands.
const std::string UP = "w";
const std::string LEFT = "a";
const std::string DOWN = "s";
const std::string RIGHT = "d";
const std::string STOP = "stop";
const std::string HELP = "help";

// Define constants for printing the field.
const std::string BODY = "~";
const std::string DEAD = "X";
const std::string EMPTY = " ";
const std::string FOOD = "*";
const std::string HEAD = "@";
const std::string TAIL = "-";
const std::string WALL = "#";

class Field {
public:

    /* Contruct a Field.
     *
     * width: Specifies the field's width.
     * height: Specifies the field's height.
     * rng: Generates random numbers used to randomize food locations.
     */
    Field(int width, int height, const std::default_random_engine& rng);

    /* Check if the game is over.
     *
     * return: `false` until the game has been either lost or won.
     */
    bool gameOver() const;

    /* Check if the game has been lost.
     *
     * return: `true` if the snake is dead.
     */
    bool gameLost() const;

    /* Check if the game has been won.
     *
     * return: `true` if the snake has filled the field.
     */
    bool gameWon() const;

    /* Move the snake in some direction.
     *
     * direction: One of constants defined above; Direction to move the head to.
     */
    void move(const string& direction);


private:

    /* Print the Field and the snake in it.
     */
    void print() const;

    /* Check if the snake currently occupies a certain square.
     *
     * square: Coordinates of the square to check.
     * return: `true` if a part of the snake is in the square.
     */
    bool isInSquare(const Point& square);

    /* Get the snake's head's coordinates.
     *
     * return: Coordinates of the snake's head.
     */
    const Point& getHead() const;

    /* Get the snake's tail's coordinates.
     *
     * return: Coordinates of the snake's tail.
     */
    const Point& getTail() const;

    /* Relocate food to a random, snakeless location.
     *
     * Hides the food if the snake has completely filled the Field.
     */
    void moveFood() const;

    /* Move the snake in some direction, eating anything in its path.
     *
     * If the food got eaten a new one got placed somewhere.
     * The snake also grew a bit.
     */
    void moveSnake();

    /* Print the top or bottom wall of the Field.
     */
    void printHorizontalWall() const;

    // `false` while the snake is alive and able to be moved.
    const bool dead_ = false;

    // Specifies the width and height of the playfield.
    const int width_ = 0;
    const int height_ = 0;

    // Generates random numbers used to move the food item to random locations.
    std::default_random_engine rng_;

    // Coordinates of squares currently occupied by the snake, head being last.
    std::vector<Point> snake_;

    // The food item's position in the Field.
    Point food_;

};  // class Field


#endif  // PRG2_SNAKE_FIELD_HH
