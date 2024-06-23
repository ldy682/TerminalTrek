#include "terminal.h"
using namespace std;

Terminal::Terminal(){
    hit = false;
    rows = 15;
    cols = 15;
    playerPos = cols/2;
    // charGrid(rows, vector<char>(cols, ' '));
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
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            if(obstacles[y] == x){
                if(x == playerPos && y == rows-1){
                    hit = true;
                }
                // could probably add the endgame logic in here!!!!!!!!!!!!!!!!!
                cout<<"X";
            }
            else if(y==rows-1 && x == playerPos){
                cout<<"O";
            }
            else{
                cout<<charGrid[y][x];
            }
        }
        cout<<endl;
    }
    // sleepThread(100);
    // system("clear");
}

void Terminal::restartGame(){
    // for(long unsigned int i = 0; i < obstacles.size(); i++){
    //     obstacles[i] = -1;
    // }
    std::fill(obstacles.begin(), obstacles.end(), -1);
    hit = false;
}

void Terminal::generateObstacle(){
    obstacles.pop_back();
    obstacles.insert(obstacles.begin(), generateNumber());
}

int Terminal::generateNumber(){
    return (rand() % (cols-2)) + 1;
}

void Terminal::moveLeft(){
    if(playerPos > 1){
        playerPos--;
    }
}
void Terminal::moveRight(){
    if(playerPos < cols - 2){
        playerPos++;
    }
}