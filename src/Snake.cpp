#include "snake.h"
#include "draw.h"
#include <iostream>
using namespace std;

Snake::Snake() : length(3), speed(250), direction(RIGHT) {
    body.resize(1000);
}

void Snake::updateSpeed() {
    int a = length - length % 3;
    switch (a) {
        case 6: speed = 200; break;
        case 9: speed = 180; break;
        case 12: speed = 160; break;
        case 15: speed = 140; break;
        case 18: speed = 120; break;
        case 21: speed = 100; break;
        case 24: speed = 80; break;
        case 27: speed = 60; break;
        case 30: speed = 40; break;
        default: break;
    }
}

void Snake::moveSnake(char nowDir) {
    Food::Position tail = body[length - 1];
    
    for (int i = length - 1; i >= 1; i--) {
        body[i] = body[i - 1];
    }
    
    switch (nowDir) {
        case UP: body[0].y--; break;
        case DOWN: body[0].y++; break;
        case LEFT: body[0].x--; break;
        case RIGHT: body[0].x++; break;
    }
    
    draw.gotoXY(body[1].x, body[1].y);
    cout << "O";
    draw.gotoXY(body[0].x, body[0].y);
    cout << "Q";
    
    bool ateFood = false;
    int foodType = -1;
    
    if (ateFood) {
        int growth = (foodType == 1) ? 1 : (foodType == 0) ? 3 : 5;
        length += growth;
        
        // foodm.generateFood(rand() % 3);
        // foodm.generateBarrier();
        
        draw.gotoXY(MAP_WIDTH + 10, 5);
        cout << "Now score:" << length - 3;
        
        updateSpeed();
    } else {
        draw.gotoXY(tail.x, tail.y);
        cout << " ";
    }
}

void Snake::initializeSnake() {
    body[0].x = MAP_WIDTH / 2 - 1;
    body[0].y = MAP_HEIGHT / 2 - 1;
    draw.gotoXY(body[0].x, body[0].y);
    cout << "Q";
    
    for (int i = 1; i < length; i++) {
        body[i].y = body[i-1].y;
        body[i].x = body[i-1].x - 1;
        draw.gotoXY(body[i].x, body[i].y);
        cout << "O";
    }
}

bool Snake::checkCollision(const std::vector<Food::Position>& barriers) {
    if (body[0].x == 0 || body[0].y == 0 || 
        body[0].x == MAP_WIDTH - 1 || body[0].y == MAP_HEIGHT - 1) {
        return true;
    }
    
    for (size_t i = 0; i < barriers.size(); i++) {
        if (body[0].x == barriers[i].x && body[0].y == barriers[i].y) {
            return true;
        }
    }
    
    for (int i = 1; i < length; i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y) {
            return true;
        }
    }
    
    return false;
}