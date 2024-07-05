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
#include <chrono>
using std::cout;
using std::endl;
using namespace std::chrono;

bool stop = false;
std::thread joystickThread;
std::thread accPlayerTh;
std::thread terminalBoardTh;
std::thread mapPrintTh;


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
            default:
                break;
        }
        sleepThread(100);
    }
    std::cout<<"thread ended"<<std::endl;
    return;
}

static void joystickThreadFn(std::unique_ptr<Joystick> joystick,
                            std::shared_ptr<Terminal> terminal){
    
    while(!stop){
        joystick->updateDirection();
        switch (joystick->getJoystickDirection()){
            case UP:
                terminal->restartGame();
                break;
            case DOWN:
                stop = true;
            default:
                break;
        }
        sleepThread(10);
    }
    return;
}

static void obstacleThreadFn(std::shared_ptr<Terminal> terminal){
    while(!stop){
        terminal->generateObstacle();
        sleepThread(300);
    }
}

void mapPrintThreadFn(std::shared_ptr<Terminal> terminal){
    
    while(!stop){
        auto start = high_resolution_clock::now();
        while(!terminal->hit){
            system("clear");
            terminal->printGrid();
            sleepThread(100);
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout<<"Time survived in ms: "<<duration.count()<<endl;
        cout<<"Joystick Up: Game restart "<<endl;
        cout<<"Joystick Down: Quit game"<<endl;
        while(terminal->hit && !stop){
            sleepThread(50);
        }
    }
}

void app_init(){
    std::shared_ptr<Terminal> terminalPtr1 = std::make_shared<Terminal>();
    std::shared_ptr<Terminal> terminalPtr2 = terminalPtr1;
    std::shared_ptr<Terminal> terminalPtr3 = terminalPtr1;
    std::shared_ptr<Terminal> terminalPtr4 = terminalPtr1;

    std::unique_ptr<Accelerometer> acc = std::make_unique<Accelerometer>();
    std::unique_ptr<Joystick> joystick = std::make_unique<Joystick>();

    // load the threads with hardware first
    joystickThread = std::thread(joystickThreadFn, std::move(joystick), std::move(terminalPtr1));
    accPlayerTh = std::thread(accPlayerThreadFn, std::move(acc), std::move(terminalPtr2));
    terminalBoardTh = std::thread(obstacleThreadFn, std::move(terminalPtr3));
    mapPrintTh = std::thread(mapPrintThreadFn, std::move(terminalPtr4));
    
}



void wait_shutdown(){
    while(!stop){
        sleepThread(200);
    }
}

void shutdown_app(){
    terminalBoardTh.join();
    accPlayerTh.join();
    mapPrintTh.join();
    joystickThread.join();
}   