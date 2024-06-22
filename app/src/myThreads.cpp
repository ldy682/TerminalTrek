#include "hal/accelerometer.h"
#include "hal/joystick.h"
#include "hal/usefulFunc.h"
#include "terminal.h"
#include "threads.h"
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cmath>

bool stop = false;


static void accPlayerThreadFn(std::unique_ptr<Accelerometer> acc,
                        std::shared_ptr<Terminal> terminal){
    int val;
    while(!stop){ 
        acc->updateAccValues();
        val = std::round(acc->getX()*2.0/17000);
        switch(val){
            case -2:
                terminal->moveLeft();
                terminal->moveLeft();
                break;
            case -1:
                terminal->moveLeft();
                break;
            case 1:
                terminal->moveRight();
                break;
            case 2: 
                terminal->moveRight();
                terminal->moveRight();
                break;
        }
        // std::cout<<acc->getX()<<std::endl;
        // terminal->printGrid();
        sleepThread(100);
        // system("clear");
    }
    std::cout<<"thread ended"<<std::endl;
    return;
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

static void obstacleThreadFn(std::shared_ptr<Terminal> terminal){
    while(!stop){
        terminal->generateObstacle();
        sleepThread(500);
    }
}

void mapPrintThreadFn(std::shared_ptr<Terminal> terminal){
    while(!stop){
        system("clear");
        terminal->printGrid();
        sleepThread(100);
    }
}

void accTerminal_init(){
    std::shared_ptr<Terminal> terminalPtr1 = std::make_shared<Terminal>();
    std::shared_ptr<Terminal> terminalPtr2 = terminalPtr1;
    std::shared_ptr<Terminal> terminalPtr3 = terminalPtr1;
    std::unique_ptr<Accelerometer> acc = std::make_unique<Accelerometer>();

    std::thread terminalBoardTh(obstacleThreadFn, std::move(terminalPtr1));
    std::thread accPlayerTh(accPlayerThreadFn, std::move(acc), std::move(terminalPtr2));
    std::thread mapPrintTh(mapPrintThreadFn, std::move(terminalPtr3));
    std::cout<<"terminal threads executed"<<std::endl;
    terminalBoardTh.detach();
    accPlayerTh.detach();
    mapPrintTh.detach();
}



void wait_shutdown(){
    while(!stop){
        sleepThread(100);
    }
}