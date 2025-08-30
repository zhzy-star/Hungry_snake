#include "food.h"
#include <iostream>
using namespace std;

void Food::generateFood(int type, const std::vector<Position>& snakeBody, int snakeLength, const std::vector<Position>& existingBarriers) {
    bool flag;
    Position newFood;
    
    do {
        flag = false;
        newFood.x = rand() % (MAP_WIDTH - 2) + 1;
        newFood.y = rand() % (MAP_HEIGHT - 2) + 1;
        
        // 检查是否与蛇身重叠
        for (size_t i = 0; i < snakeBody.size() && i < (size_t)snakeLength; i++) {
            if (snakeBody[i].x == newFood.x && snakeBody[i].y == newFood.y) {
                flag = true;
                break;
            }
        }
        
        // 检查是否与障碍物重叠
        for (size_t i = 0; i < existingBarriers.size(); i++) {
            if (existingBarriers[i].x == newFood.x && existingBarriers[i].y == newFood.y) {
                flag = true;
                break;
            }
        }
        
        // 检查是否与其他食物重叠
        if ((type != 1 && newFood.x == food.x && newFood.y == food.y) ||
            (type != 0 && newFood.x == foods.x && newFood.y == foods.y) ||
            (type != 2 && newFood.x == foodss.x && newFood.y == foodss.y)) {
            flag = true;
        }
    } while (flag);
    
    switch (type) {
        case 1:
            food = newFood;
            draw.gotoXY(food.x, food.y);
            cout << "$";
            break;
        case 0:
            foods = newFood;
            draw.gotoXY(foods.x, foods.y);
            cout << "&";
            break;
        case 2:
            foodss = newFood;
            draw.gotoXY(foodss.x, foodss.y);
            cout << "#";
            break;
    }
}

void Food::generateBarrier(const std::vector<Position>& snakeBody, int snakeLength, const std::vector<Position>& existingBarriers) {
    bool flag;
    Position newBarrier;
    
    do {
        flag = false;
        newBarrier.x = rand() % (MAP_WIDTH - 2) + 1;
        newBarrier.y = rand() % (MAP_HEIGHT - 2) + 1;
        
        // 检查是否与食物重叠
        if ((newBarrier.x == food.x && newBarrier.y == food.y) ||
            (newBarrier.x == foods.x && newBarrier.y == foods.y) ||
            (newBarrier.x == foodss.x && newBarrier.y == foodss.y)) {
            flag = true;
            continue;
        }
        
        // 检查是否与蛇身重叠
        for (size_t i = 0; i < snakeBody.size() && i < (size_t)snakeLength; i++) {
            if (snakeBody[i].x == newBarrier.x && snakeBody[i].y == newBarrier.y) {
                flag = true;
                break;
            }
        }
        
        // 检查是否与现有障碍物重叠
        for (size_t i = 0; i < existingBarriers.size(); i++) {
            if (existingBarriers[i].x == newBarrier.x && existingBarriers[i].y == newBarrier.y) {
                flag = true;
                break;
            }
        }
    } while (flag);
    
    barriers.push_back(newBarrier);
    draw.gotoXY(newBarrier.x, newBarrier.y);
    cout << "*";
}