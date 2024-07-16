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

    // config joystick pins for input
    writeToFile("/sys/class/gpio/gpio26/direction", "in");
    writeToFile("/sys/class/gpio/gpio47/direction", "in");
    writeToFile("/sys/class/gpio/gpio46/direction", "in");
    writeToFile("/sys/class/gpio/gpio65/direction", "in");
    writeToFile("/sys/class/gpio/gpio27/direction", "in");
}

Joystick::~Joystick(){
    // std::cout<<"Joystick deconstructor called"<<std::endl;
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

