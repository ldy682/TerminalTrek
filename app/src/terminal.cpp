#include "terminal.h"
using namespace std;

Terminal::Terminal(){
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

}
void Terminal::printGrid(){
    charGrid[cols-1][playerPos] = 'O';
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            cout<<charGrid[y][x];
        }
        cout<<endl;
    }

}

void Terminal::generateObstacle(){
    obstacles.pop_back();
    obstacles.insert(obstacles.begin(), generateNumber());
    for(int y = 0; y < rows; y++){
        charGrid[y][obstacles[y]] = 'X';
    }
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