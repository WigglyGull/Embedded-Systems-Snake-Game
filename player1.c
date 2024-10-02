/** @file   player1.c
    @author Jade & Auron
    @date   5 Oct 2024
    @note   This is the player1 acting as snake to catch food gain mark.
*/

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "snake.h" 

#define LOOP_RATE 350
#define SNAKE_SPEED 3  // Speed of the snake

int main(void)
{
    snake_t snake;  
    int tick = 0;

    // Initialization system and display
    system_init();
    tinygl_init(LOOP_RATE);
    navswitch_init();
    pacer_init(LOOP_RATE);

    // Initialize snake
    snake_initialize(&snake);

    /* Paced loop */
    while (1)
    {
        pacer_wait();  // Wait for next loop iteration
        navswitch_update();  // Update navswitch input states
        snake_handle_input(&snake); // Handle navswitch input to change snake direction

        // Update the screen every tick
        tinygl_clear();

        // Draw the snake on screen
        for (int i = 0; i < snake.length; i++)
        {
            tinygl_draw_point(snake.body[i], 1);  // Draw each segment 1 by 1
        }
        tinygl_update();  // Update display

        tick = tick + 1;  // Increment the tick counter
        if (tick > LOOP_RATE / SNAKE_SPEED)
        {
            tick = 0;
            snake = snake_move(snake);  // Move the snake in the current direction
        }
    }

    return 0;
}
