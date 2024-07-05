#include "hal/usefulFunc.h"
#include <vector>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

class Terminal {
    public:
        Terminal();
        ~Terminal();
        void moveLeft();
        void moveRight();
        void printGrid();
        void generateObstacle();
        void restartGame();
        bool hit;
    private:
        int playerPos;
        int rows;
        int cols;
        int time;
        std::shared_mutex gridMutx;
        std::shared_mutex playerMutx;
        std::vector<std::vector<char>> charGrid;
        std::vector<int> obstacles;
        int generateNumber();
};