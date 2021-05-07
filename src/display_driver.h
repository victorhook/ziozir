#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#ifndef SCREEN_WIDTH
    #define SCREEN_WIDTH 400
#endif
#ifndef SCREEN_HEIGHT
    #define SCREEN_HEIGHT 400
#endif

typedef struct{
    unsigned char x;
} colorStruct;

/* Initializes the display. */
void display_init();

/* Swaps the front buffer with the back buffer. */
void display_swap_buffers();

/* Puts a colorStruct at given row and col. */
void display_put(const int row, const int col, const colorStruct);

/* Sends the buffer data to the display. */
void display_send_buffer();


#endif