#include "hal/accelerometer.h"
#include "hal/joystick.h"
#include "hal/usefulFunc.h"
#include "threads.h"
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <string>

bool stop = false;

static void accThreadFn(std::unique_ptr<Accelerometer> acc){
    
    while(!stop){ 
        acc->updateAccValues();
        sleepThread(10);
    }
    std::cout<<"thread ended"<<std::endl;
    return;
}
void acc_init(){
    
    std::unique_ptr<Accelerometer> acc = std::make_unique<Accelerometer>();
    std::thread accThread(accThreadFn, std::move(acc));
    std::cout<<"accelerometer thread executed"<<std::endl;
    accThread.detach();
}

static void joystickThreadFn(std::unique_ptr<Joystick> joystick){
    
    while(!stop){
        joystick->updateDirection();
        if(joystick->getJoystickDirection() == DOWN){
            stop = true;
        }
        sleepThread(10);
    }
    std::cout<<"thread ended"<<std::endl;
    return;
}
void joystick_init(){
    
    std::unique_ptr<Joystick> joystick = std::make_unique<Joystick>();
    std::thread joystickThread(joystickThreadFn, std::move(joystick));
    std::cout<<"joystick thread executed"<<std::endl;
    joystickThread.detach();
}

void wait_shutdown(){
    while(!stop){
        
    }
}