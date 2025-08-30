#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include "constants.h"
#include "draw.h"
#include "food.h"  // 包含food.h来使用Food::Position

class Snake {
public:
    Draw draw;
    Food foodm;
    
    // 使用Food中的Position类型来保持一致性
    std::vector<Food::Position> body;
    int length;
    int speed;
    char direction;
    
    bool checkCollision(const std::vector<Food::Position>& barriers);
    Snake();
    void updateSpeed();
    void moveSnake(char nowDir);
    void initializeSnake();
};

#endif