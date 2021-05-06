#include <stdio.h>
#include "cpu.h"

#include "display_driver.h"


int main() {
    display_init();

    struct colorStruct x = {1};

    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 400; j++) {
            display_put(i, j, x);
        }
    }

    display_swap_buffers();

    display_send_buffer();
}