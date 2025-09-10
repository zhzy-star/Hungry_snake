#include "snake.h"
#include "draw.h"
#include <iostream>
using namespace std;

Snake::Snake() : length(3), speed(250), direction(RIGHT) {
    body.resize(1000);
}

void Snake::updateSpeed() {
    int a = length / 5;
    speed = 300 - a * 20; 
    if (speed < 50) speed = 50;
}

void Snake::moveSnake(char nowDir) {
    // 保存尾部位置用于清理
    Food::Position tail = body[length - 1];
    
    // 移动蛇身（从尾部向前移动）
    for (int i = length - 1; i >= 1; i--) {
        body[i] = body[i - 1];
    }
    
    // 根据方向移动蛇头
    switch (nowDir) {
        case UP: body[0].y--; break;
        case DOWN: body[0].y++; break;
        case LEFT: body[0].x--; break;
        case RIGHT: body[0].x++; break;
    }
    
    // 绘制新的蛇身
    draw.gotoXY(body[1].x, body[1].y);
    cout << "O";
    draw.gotoXY(body[0].x, body[0].y);
    cout << "Q";
    
    // 清理旧的尾部位置
    draw.gotoXY(tail.x, tail.y);
    cout << " ";
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

bool Snake::checkCollision(const std::vector<Food::Position>& barriers, GameMode mode) {
    if (mode == MODE_INVINCIBLE) {
        return false; // 无敌模式下不检测碰撞
    }

    if (mode == MODE_NORMAL){ //不可穿墙
        if (body[0].x == 0 || body[0].y == 0 || 
            body[0].x == MAP_WIDTH - 1 || body[0].y == MAP_HEIGHT - 1) {
            return true;
        }
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