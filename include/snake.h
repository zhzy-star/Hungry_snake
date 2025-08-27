#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <string>

struct Position {
    int x;
    int y;
};


class Snake {
public:
    Draw draw;
    Food foodm;
    std::vector<Position> body;
    int length;
    int speed;
    char direction;
    bool checkCollision();
    Snake();
private:
    void updateSpeed();
    void moveSnake();
    void initializeSnake();
};