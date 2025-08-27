#include "snake.h"
#include "draw.h"

Snake::Snake() : length(3), speed(250), direction(RIGHT) {
    body.resize(1000);
}

void Snake::updateSpeed() {
    int a = snake.length - snake.length % 3;
    switch (a) {
        case 6: snake.speed = 200; break;
        case 9: snake.speed = 180; break;
        case 12: snake.speed = 160; break;
        case 15: snake.speed = 140; break;
        case 18: snake.speed = 120; break;
        case 21: snake.speed = 100; break;
        case 24: snake.speed = 80; break;
        case 27: snake.speed = 60; break;
        case 30: snake.speed = 40; break;
        default: break;
    }
}


void Snake::moveSnake() {
    Position tail = snake.body[snake.length - 1];
    
    for (int i = snake.length - 1; i >= 1; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    
    switch (nowDir) {
        case UP: snake.body[0].y--; break;
        case DOWN: snake.body[0].y++; break;
        case LEFT: snake.body[0].x--; break;
        case RIGHT: snake.body[0].x++; break;
    }
    
    draw.gotoXY(snake.body[1].x, snake.body[1].y);
    std::cout << "O";
    draw.gotoXY(snake.body[0].x, snake.body[0].y);
    std::cout << "Q";
    
    bool ateFood = false;
    int foodType = -1;
    
    if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
        ateFood = true;
        foodType = 1;
    } else if (snake.body[0].x == foods.x && snake.body[0].y == foods.y) {
        ateFood = true;
        foodType = 0;
    } else if (snake.body[0].x == foodss.x && snake.body[0].y == foodss.y) {
        ateFood = true;
        foodType = 2;
    }
    
    if (ateFood) {
        int growth = (foodType == 1) ? 1 : (foodType == 0) ? 3 : 5;
        snake.length += growth;
        
        foodm.generateFood(rand() % 3);
        foodm.generateBarrier();
        
        draw.gotoXY(MAP_WIDTH + 10, 5);
        std::cout << "Now score:" << snake.length - 3;
        
        updateSpeed();
    } else {
        draw.gotoXY(tail.x, tail.y);
        std::cout << " ";
    }
}

void Snake::initializeSnake() {
    snake.body[0].x = MAP_WIDTH / 2 - 1;
    snake.body[0].y = MAP_HEIGHT / 2 - 1;
    draw.gotoXY(snake.body[0].x, snake.body[0].y);
    std::cout << "Q";
    
    for (int i = 1; i < snake.length; i++) {
        snake.body[i].y = snake.body[i-1].y;
        snake.body[i].x = snake.body[i-1].x - 1;
        draw.gotoXY(snake.body[i].x, snake.body[i].y);
        std::cout << "O";
    }
}


bool Snake::checkCollision() {
    if (snake.body[0].x == 0 || snake.body[0].y == 0 || 
        snake.body[0].x == MAP_WIDTH - 1 || snake.body[0].y == MAP_HEIGHT - 1) {
        return true;
    }
    
    for (size_t i = 0; i < barriers.size(); i++) {
        if (snake.body[0].x == barriers[i].x && snake.body[0].y == barriers[i].y) {
            return true;
        }
    }
    
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            for (int j = i; j < snake.length; j++) {
                draw.gotoXY(snake.body[j].x, snake.body[j].y);
                std::cout << " ";
            }
            snake.length = i;
            draw.gotoXY(MAP_WIDTH + 10, 5);
            std::cout << "Now Score: " << snake.length - 3;
            return false;
        }
    }
    
    return false;
}