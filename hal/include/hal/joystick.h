#include <iostream>
#include <string>


enum JoystickDirection{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    IN,
    NONE
};

class Joystick {
    public:
        Joystick();
        ~Joystick();
        void updateDirection();
        JoystickDirection getJoystickDirection();
    private:
        JoystickDirection direction;
};

void joystick_init();