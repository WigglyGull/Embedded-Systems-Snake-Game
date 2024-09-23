#include "system.h"
#include "navswitch.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"

// Set pacer rate refresh updates
#define PACER_RATE 250

// LED position init 
static tinygl_coord_t row = 0;
static tinygl_coord_t col = 0;
static tinygl_point_t position ;


/*  display the current character position
*/
static void display_char_position (void) 
{
    
    tinygl_clear();
    tinygl_draw_point(position,1);
    tinygl_update();
}

/*  navswitch action
*/
static void navswitch_action(void) 
{
    if (navswitch_push_event_p(NAVSWITCH_WEST) && row > 0)
            row--;  
        // Move down
        if (navswitch_push_event_p(NAVSWITCH_EAST) && row <= LEDMAT_ROWS_NUM )
            row++;  
        // Move right
        if (navswitch_push_event_p(NAVSWITCH_SOUTH) && col <= LEDMAT_COLS_NUM )
            col++;  
         // Move left
        if (navswitch_push_event_p(NAVSWITCH_NORTH) && col > 0)
            col--; 
        position = tinygl_point(row, col);
}
int main(void)
{
    system_init();        
    navswitch_init();   
    pacer_init(PACER_RATE);      
    tinygl_init(PACER_RATE);
    row = 2;
    col = 6;
    position = tinygl_point(row, col);
    while (1)
    {
        pacer_wait();      // Wait for next pace
        navswitch_update();  // Poll the navswitch state
        navswitch_action();
        display_char_position(); 
    }
}
