/** @file   snake.c
    @author Auron Walker & Yumeng Shi
    @date   6/OCT/2024
    @brief  Food management handling in the Snake game.Including function of 
            food generation, drawing, and collision detection with the snake.
*/

#include "food.h"
#include <stdlib.h>

/**
 * @brief Compare two positions to check if they are equal.
 *
 * @param pos1 The first position.
 * @param pos2 The second position.
 * 
 * @return Returns 1 if the positions are equal. Returns 0 ,otherwise.
 * 
 */
int snake_food_position_equal(tinygl_point_t pos1, tinygl_point_t pos2)
{
    return pos1.x == pos2.x && pos1.y == pos2.y;
}

/**
 * @brief Generate a random position for food within the display boundaries.
 *
 * @return A tinygl_point_t structure representing the random position for the food.
 */

tinygl_point_t generate_food_position()
{
    int x = rand() % TINYGL_WIDTH;  // Random x position 
    int y = rand() % TINYGL_HEIGHT; // Random y position 
    return tinygl_point(x, y);       
}

/**
 * @brief Generate one food each time at a random position.Make sure the food not collisions.
 *
 * @param snake Pointer to the snake_t , check for collisions.
 * @param food Pointer to the food_t, init with a valid position.
 */
void generate_food(snake_t* snake, food_t* food)
{
    int succeed = 0;
    
    while (!succeed) {
        food->position = generate_food_position();
        succeed = 1;

        for (int i = 0; i < snake->length; i++) {
            if (snake_food_position_equal(food->position, snake->body[i])) {
                succeed = 0;  // Position collides with the snake
                break;
            }
        }
    }
}

/**
 * @brief Draw the food at its current position on the display.
 *
 * @param food Pointer to the food_t ,the food to be drawn.
 */
void draw_food(food_t* food)
{
    tinygl_draw_point(food->position, 1);  // Draw the food at its current position
}
