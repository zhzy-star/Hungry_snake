#ifndef FOOD_H
#define FOOD_H

#include <iostream>
#include <vector>
#include "constants.h"
#include "draw.h"

class Food {
public:
    Draw draw;
    
    struct Position {
        int x;
        int y;
        int type; // 0: 1分食物, 1: 3分食物, 2: 5分食物, 3: 加速食物，4：无敌食物
    };
    
    std::vector<Position> foods;
    std::vector<Position> barriers;
    
    void generateFood(int type, const std::vector<Position>& snakeBody, int snakeLength, const std::vector<Position>& existingBarriers);
    void generateBarrier(const std::vector<Position>& snakeBody, int snakeLength, const std::vector<Position>& existingBarriers);
    void drawAllFoods(); 
    void clearFoods();
};

#endif