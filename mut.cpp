#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

volatile int globvar = 0;

auto_init_mutex(my_mutex);

void trylock(int core){
    uint32_t owner_out;
    if (mutex_try_enter(&my_mutex,&owner_out)){
        printf("from core%d: in Mutex!!\n",core); 
        sleep_ms(10);
        mutex_exit(&my_mutex);
        printf("from core%d: Out Mutex!!\n",core); 

        sleep_ms(10);
    }
    else{
        printf("from core%d: locked %d\n",core,owner_out);
        sleep_ms(10);
    }
}

void core1_entry() { 
    while (1){
        trylock(1);
    }
}

int main()
{
    stdio_init_all();

    multicore_launch_core1(core1_entry);
    while(1){
        trylock(0);
    }
    return 0;
}
