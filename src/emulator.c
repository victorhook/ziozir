#include "cpu.h"
#include "memory.h"


void start()
{
    cpu_init();
    loadBios(ram);
    cpu_run();
}
