#include <iostream>
#include <thread>
#include "myThreads.h"


int main(){
    app_init();
    wait_shutdown();    
    shutdown_app();
    return 0;
}