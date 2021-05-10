#include <stdio.h>
#include "cpu.h"

#include "display_driver.h"


int main() {
    display_init();
    display_swap_buffers();
    display_send_buffer();
}