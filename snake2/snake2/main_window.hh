/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
# Author: Matias Lappalainen, 275852, matias.a.lappalainen@tuni.fi                 #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <random>

/* \class MainWindow
 * \brief Implements the main window through which the game is played.
 */
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    struct point{
        int x; //X position
        int y; //Y position
    };

    /* \brief Construct a MainWindow.
     *
     * \param[in] parent The parent widget of this MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /* \brief Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /* \brief Change the Snake's bearing when certain keys get pressed.
     *
     * \param[in] event Contains data on pressed and released keys.
     */
    void keyPressEvent(QKeyEvent* event) override;


private slots:

    /* \brief Start the game.
     */
    void on_playButton_clicked();

    /* \brief Move the Snake by a square and check for collisions.
     *
     * The game ends if a wall or the Snake itself gets in the way.
     * When a food gets eaten a point is gained and the Snake grows.
     */
    void moveSnake();

    /* \brief Check if snake head is top off food
     * True-> eat food and make snake one tile longer. return true (Snake just ate)
     * False-> return false (Snake did not eat)
     */
    bool snake_eat_food();

    /* \brief Adds body parts to snake. Creates new point to snake_body_points
     */
    void add_body_parts();

    /* \brief Draws snake
     */
    void draw_snake();

    /* \brief Draws food
     */
    void draw_food();

    /* \brief End game if snakes body outside square or if its top of itself
     */
    void check_snake(bool);

    /* \brief resets values
     */
    void reset();

    /* \brief pause game
     */
    void on_pause_clicked();

private:

    /* \brief Make the play field visible and fit it into the view.
     *
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    std::vector<point> snake_body_points;

    int move_x_direction = 0;//X move aggerelation
    int move_y_direction = 1;//Y move aggerelation
    int food_x = 1;//Food x coordinate
    int food_y = 1;//Food y coordinate
    int snake_head_x = 2;//snake_head_x coordinate
    int snake_head_y = 2;//snake_head_y coordinate
    bool game_over = false;//Is game over
    int moves = 0;//Amount of moves
    int map_x_length = 7;//map x length
    int map_y_length = 7;//map y length
    bool move_done = true;//snake moved. Disables multiple fast movements
    bool restarted = false;//Has game been restarted
    bool paused = false;//Is game paused
    int timer = 500; //speed;

    Ui::MainWindow ui_;                 /**< Accesses the UI widgets. */
    QGraphicsRectItem* food_ = nullptr; /**< The food item in the scene. */
    QGraphicsScene scene_;              /**< Manages drawable objects. */
    QTimer timer_;                      /**< Triggers the Snake to move. */
    std::default_random_engine rng_;    /**< Randomizes food locations. */
    QGraphicsRectItem* snake_body_ = nullptr; /**< snake head location. */
    QGraphicsRectItem* empty_ = nullptr; /**< empty square. */

};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
