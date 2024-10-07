#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "snake.h" 
#include "food.h"
#include "ir_uart.h"
#include "../../fonts/font5x7_1.h"
#include <stdlib.h>
#include <time.h>

#define LOOP_RATE 500
#define SNAKE_SPEED 3 // Speed of the snake
#define PACER_RATE 500
#define MESSAGE_RATE 10

int main(void)
{
    snake_t* snake = malloc(sizeof(snake_t));   
    food_t food; 
    int tick = 0;
    bool game_won = false;

    // Seed the random number generator
    srand(time(NULL));

    // Initialization system and display
    system_init();
    tinygl_init(LOOP_RATE);
    navswitch_init();
    pacer_init(LOOP_RATE);
    ir_uart_init();

    // Initialize snake and food
    snake_initialize(snake);
    generate_food(snake, &food);

    /* Paced loop */
    while (1)
    {  
        pacer_wait();  // Wait for next loop iteration
        navswitch_update();

        if(snake->dead == true){
            break;
        }
        if(ir_uart_read_ready_p()){
            game_won = true;
            break;
        }
        tinygl_clear(); // Update the screen every tick

        for (int i = 0; i < snake->length; i++)
        {
            tinygl_draw_point(snake->body[i], 1);
        }
        tinygl_update();

    
        tick = tick + 1;  // Increment the tick counter

        draw_food(&food);// Draw the food
        
        if (tick > LOOP_RATE / SNAKE_SPEED)
        {
            tick = 0;
        
            // Check if the snake eats the food
            if (snake->body[0].x==food.position.x && snake->body[0].y==food.position.y) {
                generate_food(snake, &food);// Generate new food
                snake_grow(snake);
            }
            tinygl_clear();
            snake_move(snake);
        }
 
        snake_handle_input(snake); // Handle navswitch input to change snake direction

        tinygl_update();  // Update display
    }

    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    if(game_won) {
        tinygl_text("Game Won");
    } else {
        tinygl_text("Game Over");
    }
    
    while(1){
        pacer_wait();
        ir_uart_putc('A');
        tinygl_update();  // Continue to update the scrolling "Game Over" message
    }

    return 0;
}
