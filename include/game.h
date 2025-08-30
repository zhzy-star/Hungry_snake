#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include "constants.h"

// 前向声明
class Snake;
class Menu;
class Draw;
class Food;

class Game {
private:
    Snake* snake;
    Menu* menu;
    Draw* draw;
    Food* food;
    char nowDir;
    bool gameOver;
    void handleInput();
    void saveScore(int score);
    
public:
    Game();
    ~Game();
    void runGame_one();
    void runGame_two();
    void runGame_three();
    void choose_runGame();
    void run();
};

#endif