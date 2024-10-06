/** @file   food.h
    @author Auron Walker & Yumeng Shi
    @date   6/OCT/2024
    @brief  Header file for food handling in the Snake game.

    @defgroup Food management for the Snake game

    <h3>Introduction to Food Management</h3>

    This header file defines the data types and functions related to food
    management in the Snake game. It includes functionality for generating
    food at random positions on the display and drawing it on the screen.
    
    <h3>Food Structure</h3>

    The food structure holds the position of the food on the display.
    The position is represented by a point with (x, y) coordinates.

    <h3>Usage</h3>

    To use this module, include this header in your source files and
    implement the corresponding functions defined here.

    @code
    #include "food.h"

    void some_function() {
        food_t food;
        snake_t snake;
        generate_food(&snake, &food);
        draw_food(&food);
    }
    @endcode
*/

#ifndef FOOD_H
#define FOOD_H

#include "tinygl.h"
#include "snake.h"

typedef struct {
    tinygl_point_t position;  // Food position
} food_t;

void generate_food(snake_t* snake, food_t* food);
void draw_food(food_t* food);
tinygl_point_t generate_food_position(void);
int snake_food_position_equal(tinygl_point_t pos1, tinygl_point_t pos2);



#endif  // FOOD_H
