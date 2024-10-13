/** @file   food.h
    @author Auron Walker & Yumeng Shi
    @date   6/OCT/2024
    @brief  Food management handling in the Snake game.Including function of 
            food generation, drawing, and collision detection with the snake.
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
