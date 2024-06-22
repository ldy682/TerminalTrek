#include <iostream>
#include <thread>
#include "myThreads.h"
#include "terminal.h"
#include "hal/accelerometer.h"
using namespace std;

int main(){
    joystick_init();
    accTerminal_init();
    wait_shutdown();
    // Accelerometer acc = Accelerometer();
    // while(1){
    //     acc.updateAccValues();
        
    //     sleepThread(1000);
    // }

    
    return 0;
}