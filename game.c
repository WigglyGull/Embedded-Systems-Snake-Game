#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"

#define LOOP_RATE 1000
#define SNAKE_SPEED 4

enum dir {DIR_N, DIR_E, DIR_S, DIR_W};
typedef enum dir dir_t;

#define MAX_SNAKE_LENGTH 3 // Set snake length, change this to adjust size

struct snake
{
    tinygl_point_t body[MAX_SNAKE_LENGTH]; // Array to store body positions
    int length; // Length of the snake
    dir_t dir;  // Current direction of the snake
};
typedef struct snake snake_t;

/* Move the snake in its current direction */
static snake_t snake_move(snake_t snake)
{
    // Calculate new head position
    tinygl_point_t new_head = snake.body[0];
    switch (snake.dir)
    {
        case DIR_N:
            new_head.y -= 1;  // Move up
            break;
        case DIR_E:
            new_head.x += 1;  // Move right
            break;
        case DIR_S:
            new_head.y += 1;  // Move down
            break;
        case DIR_W:
            new_head.x -= 1;  // Move left
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
    for (int i = snake.length - 1; i > 0; i--)
    {
        snake.body[i] = snake.body[i - 1];
    }

    // Update the head position
    snake.body[0] = new_head;

    return snake;
}

/* Turn the snake left (counter-clockwise) */
static snake_t snake_turn_left(snake_t snake)
{
    dir_t newdir[] = {DIR_W, DIR_N, DIR_E, DIR_S};
    snake.dir = newdir[snake.dir];
    return snake;
}

/* Turn the snake right (clockwise) */
static snake_t snake_turn_right(snake_t snake)
{
    dir_t newdir[] = {DIR_E, DIR_S, DIR_W, DIR_N};
    snake.dir = newdir[snake.dir];
    return snake;
}

int main(void)
{
    snake_t snake;
    int tick = 0;

    system_init();
    tinygl_init(LOOP_RATE);
    navswitch_init();
    pacer_init(LOOP_RATE);

    // Initialize the snake
    snake.length = MAX_SNAKE_LENGTH;  // Set the snake length (adjustable)
    snake.dir = DIR_N;                // Initial direction is North
    snake.body[0].x = TINYGL_WIDTH / 2;  // Start in the middle of the LED matrix
    snake.body[0].y = TINYGL_HEIGHT - 1; // Start at the bottom

    // Initialize snake body positions
    for (int i = 1; i < snake.length; i++)
    {
        snake.body[i] = snake.body[i - 1];  // Initially, all parts are in the same place
    }

    // Draw initial snake position
    tinygl_draw_point(snake.body[0], 1);
    tinygl_update();

    /* Paced loop */
    while (1)
    {
        pacer_wait();
        navswitch_update();

        // Update the screen every tick
        tinygl_clear();
        for (int i = 0; i < snake.length; i++)
        {
            tinygl_draw_point(snake.body[i], 1);
        }
        tinygl_update();

        tick = tick + 1;
        if (tick > LOOP_RATE / SNAKE_SPEED)
        {
            tick = 0;
            snake = snake_move(snake);  // Move the snake in the current direction
        }

        // Turn left if NAVSWITCH_WEST is pressed
        if (navswitch_push_event_p(NAVSWITCH_WEST))
        {
            snake = snake_turn_left(snake);
        }

        // Turn right if NAVSWITCH_EAST is pressed
        if (navswitch_push_event_p(NAVSWITCH_EAST))
        {
            snake = snake_turn_right(snake);
        }
    }

    return 0;
}