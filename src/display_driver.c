#include "display_driver.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


colorStruct* front_buffer;
colorStruct* back_buffer;

const char* driverFilePath = "/home/victor/coding/projects/ziozir/gui/display_driver";
const size_t TOTAL_PIXELS = SCREEN_HEIGHT * SCREEN_WIDTH;
const size_t BUFF_SIZE = TOTAL_PIXELS * sizeof(colorStruct);
const size_t ROW_SIZE = SCREEN_WIDTH * sizeof(colorStruct);


static inline void ensure_driver_file_path_exists()
{
    FILE* fd = fopen(driverFilePath, "r");
    if (fd) {
        fclose(fd);
    } else {
        printf("Failed to open display driver file at: \"%s\"\n", driverFilePath);
        printf("Exiting...\n");
        exit(0);
    }
}

void display_init()
{
    front_buffer = (colorStruct*) malloc(BUFF_SIZE);
    back_buffer = (colorStruct*) malloc(BUFF_SIZE);
    memset(front_buffer, 0, BUFF_SIZE);
    memset(back_buffer, 0, BUFF_SIZE);
    ensure_driver_file_path_exists();
}

void display_swap_buffers()
{
    colorStruct* tmp = front_buffer;
    front_buffer = back_buffer;
    back_buffer = tmp;
}

void display_put(const int row, const int col, const colorStruct color)
{
    *(back_buffer + row*ROW_SIZE + col) = color;
}

void display_send_buffer()
{
    printf("Sending buffer...\n");
    FILE* fd = fopen(driverFilePath, "w");
    size_t written = fwrite(front_buffer, sizeof(colorStruct), TOTAL_PIXELS, fd);
    printf("Written %ld bytes\n", written);
    fclose(fd);
}