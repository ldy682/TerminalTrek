#include <iostream>
#include "myThreads.h"
using namespace std;

int main(){
    joystick_init();
    acc_init();
    wait_shutdown();
    // Accelerometer acc = Accelerometer();
    // while(1){
    //     acc.updateAccValues();
    //     std::cout<<"X: " << acc.getX()<<std::endl;
    //     std::cout<<"Y: " << acc.getY()<<std::endl;
    //     std::cout<<"Z: " << acc.getZ()<<std::endl;
    //     sleepThread(1000);
    // }
    return 0;
}