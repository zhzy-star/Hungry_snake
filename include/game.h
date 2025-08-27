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

const int MAP_HEIGHT = 30;
const int MAP_WIDTH = 80;
const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const int MAX_SCORES = 100;
const std::string SCORE_FILE = "scores.txt";

struct Position {
    int x;
    int y;
};

class Game {
private:
    Snake snake;
    Menu menu;
    Draw draw;
    Food food;
    char nowDir;
    bool gameOver;
    void handleInput();
    void saveScore(int score);
    
public:
    Game();
    void runGame();
    void run();
};
