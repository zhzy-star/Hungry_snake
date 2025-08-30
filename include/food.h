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
    };
    
    Position food;
    Position foods;
    Position foodss;
    std::vector<Position> barriers;
    
    void generateFood(int type, const std::vector<Position>& snakeBody, int snakeLength, const std::vector<Position>& existingBarriers);
    void generateBarrier(const std::vector<Position>& snakeBody, int snakeLength, const std::vector<Position>& existingBarriers);
};

#endif