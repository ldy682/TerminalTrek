#include "terminal.h"
using namespace std;

Terminal::Terminal(){
    hit = false;
    rows = 15;
    cols = 15;
    playerPos = cols/2;

    // initializes the grid
    charGrid.resize(rows, std::vector<char>(cols, ' '));

    // initializes the obstacles
    obstacles.resize(rows, -1);
    obstacles.pop_back();
    obstacles.insert(obstacles.begin(), generateNumber());

    // sets the sides
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            if(x == 0 || x == (cols-1)){
                charGrid[y][x] = '|';
            }
        }
    }
}
Terminal::~Terminal(){
    cout<<"Terminal deconstructor called"<<endl;
}
void Terminal::printGrid(){
    static int prevPlayerPos = playerPos;
    gridMutx.lock_shared();
    if (prevPlayerPos != playerPos) {
        charGrid[rows-1][prevPlayerPos] = ' ';
        prevPlayerPos = playerPos;
    }
    charGrid[cols-1][playerPos] = 'O';
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
          cout<<charGrid[y][x];
        }
        cout<<endl;
    }
    charGrid[rows-1][playerPos] = ' ';
    gridMutx.unlock_shared();
}

void Terminal::restartGame(){
    charGrid.resize(rows, std::vector<char>(cols, ' '));
    for(int y = 0; y < rows; y++){
        charGrid[y][obstacles[y]] = ' ';
    }
    // sets the sides
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            if(x == 0 || x == (cols-1)){
                charGrid[y][x] = '|';
            }
        }
    }
    std::fill(obstacles.begin(), obstacles.end(), -1);
    hit = false;
}

void Terminal::generateObstacle(){
    gridMutx.lock();
    for(int y = 0; y < rows; y++){
        if(obstacles[y] != -1){
            charGrid[y][obstacles[y]] = ' ';
        }
    }
    obstacles.pop_back();
    obstacles.insert(obstacles.begin(), generateNumber());
    for(int y = 0; y < rows; y++){
        if(obstacles[y] != -1){
            charGrid[y][obstacles[y]] = 'X';
        }
    }
    if(obstacles[rows-1] == playerPos){
        hit = true;
    }
    gridMutx.unlock();
}

int Terminal::generateNumber(){
    return (rand() % (cols-2)) + 1;
}

void Terminal::moveLeft(){
    playerMutx.lock();
    if(playerPos > 1){
        playerPos--;
    }
    playerMutx.unlock();
}
void Terminal::moveRight(){
    playerMutx.lock();
    if(playerPos < cols - 2){
        playerPos++;
    }
    playerMutx.unlock();
}