#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "snake.h"
#include <stdlib.h>


/* Move the snake in its current direction */
void snake_move(snake_t* snake)
{
    // Calculate new head position
    tinygl_point_t new_head = snake->body[0];
    switch (snake->dir)
    {
        case DIR_N:
            new_head.y -= 1;  // Up
            break;
        case DIR_E:
            new_head.x += 1;  // Right
            break;
        case DIR_S:
            new_head.y += 1;  // Down
            break;
        case DIR_W:
            new_head.x -= 1;  // Left
            break;
    }

    // Wrap around screen boundaries
    if (new_head.x < 0)
        new_head.x = TINYGL_WIDTH - 1;
    else if (new_head.x >= TINYGL_WIDTH)
        new_head.x = 0;

    if (new_head.y < 0)
        new_head.y = TINYGL_HEIGHT - 1;
    else if (new_head.y >= TINYGL_HEIGHT)
        new_head.y = 0;

    // Shift body positions to follow the head
    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }

    // Update the head position
    snake->body[0] = new_head;
}


/* Initialize and draw the snake */
void snake_initialize(snake_t* snake) {
    snake->length = INITIAL_SNAKE_LENGTH;
    snake->max_length = MAX_SNAKE_LENGTH;
    snake->body[0].x =TINYGL_WIDTH / 2; // Initialize head position
    snake->body[0].y =TINYGL_HEIGHT - 1;

    // Initialize snake body positions
    for (int i = 1; i < snake->length; i++)
    {
        snake->body[i] = snake->body[i - 1];  // Initially, all parts are in the same place
    }


    tinygl_draw_point(snake->body[0], 1);
    tinygl_update();
}



void snake_grow(snake_t* snake) {
    if (snake->length < snake->max_length) {
        snake->length++;  // Increase the length of the snake
    } else {
        //player1.win
    }
}


/* Change snake direction based on input */
void snake_handle_input(snake_t* snake)
{


    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        snake->dir = DIR_W; // Turn left
    }
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        snake->dir = DIR_E; // Turn right 
    }
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        snake->dir = DIR_N; // Turn froward
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        snake->dir = DIR_S; // Turn back
    }
}


