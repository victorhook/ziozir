#include <stdio.h>
#include "cpu.h"


int main() {
    printf("Hello\n");

    for (int i = 0; i < 10; i++) {
        int res = (int) writeMemory(i, i*i);
        printf("%d, ", res);
    }

    for (int i = 0; i < 10; i++) {
        int res = (int) readMemory(i);
        printf("%d, ", res);
    }

    return 0;
}