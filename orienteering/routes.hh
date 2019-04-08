/*  TIE-02201 Ohjelmointi 2, K2019 / TIE-02207 Programming 2, S2019
 *  Project 3: Orienteering
 *  File: routes.hh
 *  Description: Datastructure that represents the orienteering map
 *      and handles the information of different points and routes
 *  Notes:
 *      * Students aren't allowed to make changes to the public interface!
 *      * Modifying the private part of class is allowed.
 * */

#ifndef ROUTES_HH
#define ROUTES_HH

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

/**
 * @brief Struct Point
 * Contains information about a single point.
 */
struct Point{
    std::string name;
    int x;
    int y;
    int heigth;
    char mark;
};

class Routes
{
public:
    // Constructor and deconstructor
    Routes();
    ~Routes();

    /**
     * @brief set_map_size
     * @param width
     * @param height
     * Sets the map to print in this size
     */
    void set_map_size(int width, int height);

    /**
     * @brief add_point
     * @param name
     * @param x
     * @param y
     * @param height : in meters from sealevel
     * @param marker : char to be printed instead of generic marker '.'
     * Adds a point to the datastructure
     */
    void add_point(std::string& name, int x, int y, int height, char marker);

    /**
     * @brief connect_route
     * @param from  : point name
     * @param to    : point name
     * @param route_name
     * @return true if connection was succesful, false otherwise
     * Connects 2 points with a one-way connection
     */
    bool connect_route(std::string& from, std::string& to, std::string& route_name);

    /**
     * @brief print_map
     * Prints the map
     */
    void print_map() const;

    /**
     * @brief print_route_names
     * Prints all routes' names, ordered alphabetically.
     */
    void print_route_names() const;

    /**
     * @brief print_points
     * Prints all points and their markers on map
     */
    void print_points() const;

    /**
     * @brief print_route
     * @param name
     * Prints points belonging to route 'name' in the order they are in the route.
     */
    void print_route(const std::string& name) const;

    /**
     * @brief route_length
     * @param name
     * Prints the route's combined length
     */
    void route_length(const std::string& name) const;

    /**
     * @brief greatest_rise
     * @param point_name
     * Finds the biggest continous rise in any of the routes after point given
     */
    void greatest_rise(const std::string& point_name) const;

private:
    /**
     * @brief points_
     * Datastructure that contains all of the control points
     */
    std::map<std::string, Point*> points_by_name;//Contains all points. Key is point name.
    std::map<std::string, Point*> points_by_coordinate;//Contains all points. Key is x:y. Used for printing map
    std::map<std::string, std::vector<Point*>> routes_;//Contains all routes. Key is route name
    int map_width;
    int map_heigth;
};

#endif // ROUTES_HH
