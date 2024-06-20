#include <iostream>
#include "hal/joystick.h"
#include "hal/accelerometer.h"
#include "hal/usefulFunc.h"
using namespace std;

int main(){
    
    Accelerometer acc = Accelerometer();
    while(1){
        acc.updateAccValues();
        std::cout<<"X: " << acc.getX()<<std::endl;
        std::cout<<"Y: " << acc.getY()<<std::endl;
        std::cout<<"Z: " << acc.getZ()<<std::endl;
        sleepThread(1000);
    }
    return 0;
}