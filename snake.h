#include "tinygl.h"
#ifndef SNAKE_H
#define SNAKE_H

#define INITIAL_SNAKE_LENGTH 3  // Set snake length, change this to adjust size
#define MAX_SNAKE_LENGTH 6  // Define a maximum length to avoid overflow

//snake directions
typedef enum dir
{
    DIR_N,  // North (up)
    DIR_E,  // East (right)
    DIR_S,  // South (down)
    DIR_W   // West (left)
} direction_t;

// Structure for the snake
typedef struct {
    tinygl_point_t body[MAX_SNAKE_LENGTH];  // body segments
    int length;            // Current length 
    int max_length;        // Maximum length allocated
    direction_t dir;       // Current direction of the snake
} snake_t;


void snake_move(snake_t* snake);
void snake_initialize(snake_t* snake);
void snake_handle_input(snake_t* snake);

#endif  // SNAKE_H
