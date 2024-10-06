#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "snake.h" 
#include "food.h"
#include <stdlib.h>
#include <time.h>

#define LOOP_RATE 350
#define SNAKE_SPEED 1 // Speed of the snake

int main(void)
{
    snake_t* snake = malloc(sizeof(snake_t));   
    food_t food; 
    int tick = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Initialization system and display
    system_init();

    tinygl_init(LOOP_RATE);

    navswitch_init();

    pacer_init(LOOP_RATE);

    // Initialize snake and food
    snake_initialize(snake);
    generate_food(snake, &food);


    /* Paced loop */
    while (1)
    {
        pacer_wait();  // Wait for next loop iteration
        
        navswitch_update();

        // Update the screen every tick
        tinygl_clear();
        for (int i = 0; i < snake->length; i++)
        {
            tinygl_draw_point(snake->body[i], 1);
        }
        tinygl_update();

    
        tick = tick + 1;  // Increment the tick counter

        if (tick > LOOP_RATE / SNAKE_SPEED)
        {
            tick = 0;
            snake_move(snake);  // Move snake 1 unit in the current direction
        }

        draw_food(&food);// Draw the food
        tick += 1;
        if (tick > LOOP_RATE / SNAKE_SPEED)
        {
            tick = 0;
            snake_move(snake);

            // Check if the snake eats the food
            if (snake->body[0].x==food.position.x && snake->body[0].y==food.position.y) {
                generate_food(snake, &food);// Generate new food
                snake_grow(snake);
            }
        }
 
        snake_handle_input(snake); // Handle navswitch input to change snake direction

        tinygl_update();  // Update display
    }

    return 0;
}
