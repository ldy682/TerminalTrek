#include "hal/joystick.h"
#include "hal/usefulFunc.h"
#include <thread>


Joystick::Joystick(){
    // configures the joystick to work
    runCommand("config-pin p8.14 gpio");
    runCommand("config-pin p8.15 gpio");
    runCommand("config-pin p8.16 gpio");
    runCommand("config-pin p8.18 gpio");
    runCommand("config-pin p8.17 gpio");
    runCommand("config-pin p9_18 i2c");
    runCommand("config-pin p9_17 i2c");

    // config joystick pins for input
    writeToFile("/sys/class/gpio/gpio26/direction", "in");
    writeToFile("/sys/class/gpio/gpio47/direction", "in");
    writeToFile("/sys/class/gpio/gpio46/direction", "in");
    writeToFile("/sys/class/gpio/gpio65/direction", "in");
    writeToFile("/sys/class/gpio/gpio27/direction", "in");
}

Joystick::~Joystick(){

}

void Joystick::updateDirection(){
    if(readIntFromFile("/sys/class/gpio/gpio26/value") == 0){
        this->direction = UP;
    }
    else if(readIntFromFile("/sys/class/gpio/gpio46/value") == 0){
        this->direction = DOWN;
    }
    else if(readIntFromFile("/sys/class/gpio/gpio65/value") == 0){
        this->direction = LEFT;
    }
    else if(readIntFromFile("/sys/class/gpio/gpio47/value") == 0){
        this->direction = RIGHT;
    }
    else if(readIntFromFile("/sys/class/gpio/gpio27/value") == 0){
        this->direction = IN;
    }
    else {
        this->direction = NONE;
    }
}

JoystickDirection Joystick::getJoystickDirection(){
    return this->direction;
}

// void joystickThreadFn(std::unique_ptr<Joystick> joystick){
    
//     while(joystick->getJoystickDirection() != DOWN){
//         joystick->updateDirection();
//         sleepThread(10);
//     }
//     std::cout<<"thread ended"<<std::endl;
//     return;
// }
// void joystick_init(){
    
//     std::unique_ptr<Joystick> joystick = std::make_unique<Joystick>();
//     std::thread joystickThread(joystickThreadFn, std::move(joystick));
//     std::cout<<"thread exectured"<<std::endl;
//     joystickThread.detach();
// }
