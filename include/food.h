#ifndef FOOD_H
#define FOOD_H

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


class Food{
public:
    Draw draw;
    Position food;
    Position foods;
    Position foodss;
    std::vector<Position> barriers;
private:
    void generateFood(int type)
    void generateBarrier();
};