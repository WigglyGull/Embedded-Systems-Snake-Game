/** @file   snake.c
    @author Auron Walker & Yumeng Shi
    @date   6/OCT/2024
    @brief  Snake in main game, including snake movement, collision detection, and growth mechanics.
*/

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "snake.h"
#include <stdlib.h>


/**
 * @brief Check if the snake has collided with itself.
 *
 * @param snake Pointer to snake structure.
 * @param new_head The new head position of the snake.
 * 
 * @return true if the snake has collided with itself; false otherwise.
 */

bool snake_has_collided(snake_t* snake, tinygl_point_t new_head)
{
    for (int i = 1; i < snake->length; i++) {
        if (snake->body[i].x == new_head.x && snake->body[i].y == new_head.y) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Move the snake.
 *
 * @param snake Pointer to snake structure.
 */

void snake_move(snake_t* snake)
{
    if(snake->dead == true) {
        return;
    }

    // Calculate new head position
    tinygl_point_t new_head = snake->body[0];
    switch (snake->dir) {
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

    // Check for collisions with screen boundaries
    if (new_head.x < 0 || new_head.x >= TINYGL_WIDTH || new_head.y < 0 || new_head.y >= TINYGL_HEIGHT) {
        snake->dead = true;
        return;
    }

    // Check for collisions with itself
    if (snake_has_collided(snake, new_head)) {
        snake->dead = true;
        return;
    }

    // Shift body positions to follow the head
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }

    // Update the head position
    snake->body[0] = new_head;
}



/**
 * @brief Initialize and draw the snake.
 *
 * @param snake Pointer to snake structure.
 */

void snake_initialize(snake_t* snake) 
{
    snake->length = INITIAL_SNAKE_LENGTH;
    snake->max_length = MAX_SNAKE_LENGTH;
    snake->body[0].x =TINYGL_WIDTH / 2; // Initialize head position
    snake->body[0].y =TINYGL_HEIGHT - 1;
    snake->dead = false;
    snake->dir = DIR_N;

    // Initialize snake body positions
    for (int i = 1; i < snake->length; i++) {
        snake->body[i] = snake->body[i - 1];  // Initially, all parts are in the same place
    }

    tinygl_draw_point(snake->body[0], 1);
    tinygl_update();
}

/**
 * @brief Increments the length of the snake by 1, up to maxi length limit.
 *
 * @param snake Pointer to the snake structure.
 */
void snake_grow(snake_t* snake) 
{
    if (snake->length < MAX_SNAKE_LENGTH) {
            snake->length++;
        }
    }


/**
 * @brief Change the snake's direction with user input from navswitch.
 *
 * @param snake Pointer to the snake structure.
 */

void snake_handle_input(snake_t* snake)
{
    if (navswitch_push_event_p(NAVSWITCH_WEST) && snake->dir != DIR_E && snake->dir != DIR_W) {
        snake->dir = DIR_W; // Turn left
    }
    if (navswitch_push_event_p(NAVSWITCH_EAST) && snake->dir != DIR_E && snake->dir != DIR_W) {
        snake->dir = DIR_E; // Turn right
    }
    if (navswitch_push_event_p(NAVSWITCH_NORTH) && snake->dir != DIR_N && snake->dir != DIR_S) {
        snake->dir = DIR_N; // Turn froward
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && snake->dir != DIR_N && snake->dir != DIR_S) {
        snake->dir = DIR_S; // Turn back
    }
}