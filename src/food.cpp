#include "food.h"

void Food::generateFood(int type) {
    bool flag;
    Position newFood;
    
    do {
        flag = false;
        newFood.x = rand() % (MAP_WIDTH - 2) + 1;
        newFood.y = rand() % (MAP_HEIGHT - 2) + 1;
        
        for (size_t i = 0; i < snake.body.size() && i < (size_t)snake.length; i++) {
            if (snake.body[i].x == newFood.x && snake.body[i].y == newFood.y) {
                flag = true;
                break;
            }
        }
        
        for (size_t i = 0; i < barriers.size(); i++) {
            if (barriers[i].x == newFood.x && barriers[i].y == newFood.y) {
                flag = true;
                break;
            }
        }
        
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
            std::cout << "$";
            break;
        case 0:
            foods = newFood;
            draw.gotoXY(foods.x, foods.y);
            std::cout << "&";
            break;
        case 2:
            foodss = newFood;
            draw.gotoXY(foodss.x, foodss.y);
            std::cout << "#";
            break;
    }
}

void Food::generateBarrier() {
    bool flag;
    Position newBarrier;
    
    do {
        flag = false;
        newBarrier.x = rand() % (MAP_WIDTH - 2) + 1;
        newBarrier.y = rand() % (MAP_HEIGHT - 2) + 1;
        
        if ((newBarrier.x == food.x && newBarrier.y == food.y) ||
            (newBarrier.x == foods.x && newBarrier.y == foods.y) ||
            (newBarrier.x == foodss.x && newBarrier.y == foodss.y)) {
            flag = true;
            continue;
        }
        
        for (size_t i = 0; i < snake.body.size() && i < (size_t)snake.length; i++) {
            if (snake.body[i].x == newBarrier.x && snake.body[i].y == newBarrier.y) {
                flag = true;
                break;
            }
        }
        
        for (size_t i = 0; i < barriers.size(); i++) {
            if (barriers[i].x == newBarrier.x && barriers[i].y == newBarrier.y) {
                flag = true;
                break;
            }
        }
    } while (flag);
    
    barriers.push_back(newBarrier);
    draw.gotoXY(newBarrier.x, newBarrier.y);
    std::cout << "*";
}