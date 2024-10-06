#include "food.h"
#include <stdlib.h>

/** Compare two positions to check if they are equal.
    @param pos1 the first position (e.g., snake body part)
    @param pos2 the second position (e.g., food)
    @return 1 if positions are equal, 0 otherwise */
int snake_food_position_equal(tinygl_point_t pos1, tinygl_point_t pos2)
{
    return pos1.x == pos2.x && pos1.y == pos2.y;
}


/** Generate a random position for food within the display boundaries.
    @return a tinygl_point_t representing the random position */
tinygl_point_t generate_food_position()
{
    int x = rand() % TINYGL_WIDTH;  // Random x position 
    int y = rand() % TINYGL_HEIGHT; // Random y position 
    return tinygl_point(x, y);       
}

/** Generate food at a random position that not collide with the snake.
    @param snake the snake object to check for collisions
    @param food the food object to initialize with a valid position */
void generate_food(snake_t* snake, food_t* food)
{
    int succeed = 0;
    
    while (!succeed) 
    {
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

/** Draw the food at its current position on the display.
    @param food the food object to be drawn */
void draw_food(food_t* food)
{
    tinygl_draw_point(food->position, 1);  // Draw the food at its current position
}
