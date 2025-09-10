#include "food.h"
#include <iostream>
using namespace std;

void Food::clearFoods() {
    foods.clear();
}

void Food::drawAllFoods() {
    for (const auto& food : foods) {
        draw.gotoXY(food.x, food.y);
        switch (food.type) {
            case 0: case 1: case 2: case 3:
                cout << "$"; break; // 1分食物
            case 4: case 5: case 6:
                cout << "&"; break; // 3分食物
            case 7:
                cout << "#"; break; // 5分食物
            case 8: case 9:
                cout << "%"; break; // 加速食物
            case 10:
                cout << "@"; break; // 无敌食物
        }
    }
}
void Food::generateFood(int type, const std::vector<Position>& snakeBody, int snakeLength, const std::vector<Position>& existingBarriers) {
    bool flag;
    Position newFood;
    newFood.type = type;
    
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
        for (const auto& existingFood : foods) {
            if (existingFood.x == newFood.x && existingFood.y == newFood.y) {
                flag = true;
                break;
            }
        }
    } while (flag);
    
    foods.push_back(newFood);
    
    // 立即绘制新食物
    draw.gotoXY(newFood.x, newFood.y);
    switch (type) {
        case 0: case 1: case 2: case 3: cout << "$"; break;
        case 4: case 5: case 6: cout << "&"; break;
        case 7: cout << "#"; break;
        case 8: case 9: cout << "%"; break;
        case 10: cout << "@"; break;
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
        for (const auto& food : foods) {
            if (food.x == newBarrier.x && food.y == newBarrier.y) {
                flag = true;
                break;
            }
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