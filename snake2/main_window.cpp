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
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: First Last, student#, first.last@tuni.fi                 #
####################################################################
*/

#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <string>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    // Move directions
    // A, left
    // D, right
    // S, Down
    // W, Up
    if(event->text()=="a"&&move_x_direction!=1){
        move_x_direction = -1;
        move_y_direction = 0;
    }
    if(event->text()=="s"&&move_y_direction!=-1){
        move_x_direction = 0;
        move_y_direction = 1;
    }
    if(event->text()=="d"&&move_x_direction!=-1){
        move_x_direction = 1;
        move_y_direction = 0;
    }
    if(event->text()=="w"&&move_y_direction!=1){
        move_x_direction = 0;
        move_y_direction = -1;
    }
}

void MainWindow::on_playButton_clicked() {
    game_over = false;

    const QRectF food_rect(0, 0, 1, 1);
    const QBrush brush_red(Qt::red);
    const QPen pen(Qt::white, 0);
    food_ = scene_.addRect(food_rect, pen, brush_red);
    food_->setPos(food_x, food_y);

    const QBrush brush_black(Qt::green);
    snake_body_ = scene_.addRect(food_rect, pen, brush_black);
    snake_body_->setPos(snake_head_x, snake_head_y);

    adjustSceneArea();
    timer_.start(500);
}

void MainWindow::moveSnake() {
    moves+=1;
    if(game_over==false){
    snake_head_x+=move_x_direction;
    snake_head_y+=move_y_direction;
    bool snake_ate = snake_eat_food();//Check if snake top of food. return true if top of food
    draw_snake();
    draw_food();
    check_snake(snake_ate);
    snake_body_points.pop_back();//Delete snake tail
    ui_.snake_length->setText("Points : "+QString::number(snake_body_points.size()+1));
    ui_.timer->setText("Timer : "+QString::number(moves/2));
    }
    else{
        snake_body_points.pop_back();//Delete snake tail
        for(auto i : snake_body_points){
            const QRectF empty_square(0, 0, 1, 1);
            const QBrush brush_white(Qt::blue);
            const QBrush brush_black(Qt::black);
            const QPen pen(Qt::white, 0);
            empty_ = scene_.addRect(empty_square, pen, brush_white);
            empty_->setPos(i.x, i.y);
        }
    }
}

void MainWindow::draw_food(){
    const QRectF food_rect(0, 0, 1, 1);
    const QBrush brush_red(Qt::red);
    const QPen pen(Qt::white, 0);
    food_ = scene_.addRect(food_rect, pen, brush_red);
    food_->setPos(food_x, food_y);
}

void MainWindow::check_snake(bool snake_ate){
    for(auto i :snake_body_points){
        bool not_same = false;
        for (auto b : snake_body_points){
            if(i.x==b.x && i.y==b.y && snake_ate==false){
                if(i.x==b.x && i.y==b.y && not_same){
                    game_over=true;
                }
                not_same = true;
            }
        }
    }
}

void MainWindow::draw_snake(){
    if(snake_head_x >= -1 && snake_head_y >= -1&&snake_head_x <= 10 && snake_head_y <= 10){
        snake_body_points.insert(snake_body_points.begin(),point{snake_head_x,snake_head_y});
        const QRectF empty_square(0, 0, 1, 1);
        const QBrush brush_white(Qt::white);
        const QBrush brush_green(Qt::green);
        const QRectF body_rect(0, 0, 1, 1);
        const QBrush brush_black(Qt::black);
        const QPen pen(Qt::white, 0);
        bool snake_head_drawn = false;
        for(int a = 0; a<10;a++){
            for(int i = 0; i<10;i++){
                    empty_ = scene_.addRect(empty_square, pen, brush_white);
                    empty_->setPos(a, i);
            }
        }
        for(auto part : snake_body_points){
            if(snake_head_drawn==false){
                snake_body_ = scene_.addRect(body_rect, pen, brush_green);
                snake_body_->setPos(part.x, part.y);
                snake_head_drawn = true;
            }
            else{
                snake_body_ = scene_.addRect(body_rect, pen, brush_black);
                snake_body_->setPos(part.x, part.y);
            }
        }
    }
    else{game_over=true;}
}

bool MainWindow::snake_eat_food(){
    if(food_x==snake_head_x && food_y==snake_head_y){
        bool square_for_food_found = true;
        add_body_parts();
        while(true){
          srand(time(NULL));
         /* generate secret number between 1 and map size: */
         food_x = rand() % 6+1;
         /* generate secret number between 1 and map size: */
         food_y = rand() % 6+1;
         for(auto i : snake_body_points){
              if(i.x==food_x && i.y==food_y){
                  square_for_food_found = false;
                  break;
              }
          }
         if(square_for_food_found){
             food_->setPos(food_x, food_y);
             break;
         }
        }
        return true;
    }
    return false;
}

void MainWindow::add_body_parts(){
    snake_body_points.push_back(point{
                                    snake_body_points[snake_body_points.size()-1].x,
                                    snake_body_points[snake_body_points.size()-1].y});
}

void MainWindow::adjustSceneArea() {
    // TODO: Replace the area's size with the play field's actual size.
    const QRectF area(0, 0, 7, 7);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}
