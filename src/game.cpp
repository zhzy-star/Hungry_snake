#include "game.h"
#include "snake.h"
#include "draw.h"
#include "menu.h"
#include "food.h"
#include <iostream>
using namespace std;

Game::Game() : nowDir(RIGHT), gameOver(false) {
    snake = new Snake();
    menu = new Menu();
    draw = new Draw();
    food = new Food();
    srand((unsigned int)time(NULL));
}

Game::~Game() {
    delete snake;
    delete menu;
    delete draw;
    delete food;
}

void Game::handleInput() {
    if (_kbhit()) {
        char input = _getch();
        switch (input) {
            case UP:
                if (nowDir != DOWN) nowDir = input;
                break;
            case DOWN:
                if (nowDir != UP) nowDir = input;
                break;
            case LEFT:
                if (nowDir != RIGHT) nowDir = input;
                break;
            case RIGHT:
                if (nowDir != LEFT) nowDir = input;
                break;
        }
    }
}

void Game::saveScore(int score) {
    ofstream outFile(SCORE_FILE.c_str(), ios::app);
    if (!outFile) {
        cerr << "No Data" << endl;
        return;
    }
    outFile << score << endl;
    outFile.close();
}

void Game::runGame_one() { //无尽模式
    system("cls");
    food->barriers.clear();  
    snake->length = 3;      
    snake->speed = 250;     
    nowDir = RIGHT;
    gameOver = false;

    draw->drawBorder();     
    snake->initializeSnake(); 
    
    food->generateFood(rand() % 3, snake->body, snake->length, food->barriers);
    food->generateBarrier(snake->body, snake->length, food->barriers);

    draw->gotoXY(MAP_WIDTH + 10, 5);  
    cout << "Now Score: 0";
    
    while (!gameOver) {
        handleInput();
        snake->moveSnake(nowDir);  
        
        // 在游戏循环中添加食物检测
        if (snake->body[0].x == food->food.x && snake->body[0].y == food->food.y) {
            snake->length += 1;
            food->generateFood(rand() % 3, snake->body, snake->length, food->barriers);
            
            // 更新分数显示
            draw->gotoXY(MAP_WIDTH + 10, 5);
            cout << "Now Score: " << snake->length - 3;
        }
        else if (snake->body[0].x == food->foods.x && snake->body[0].y == food->foods.y) {
            snake->length += 3;
            food->generateFood(rand() % 3, snake->body, snake->length, food->barriers);
            
            draw->gotoXY(MAP_WIDTH + 10, 5);
            cout << "Now Score: " << snake->length - 3;
        }
        else if (snake->body[0].x == food->foodss.x && snake->body[0].y == food->foodss.y) {
            snake->length += 5;
            food->generateFood(rand() % 3, snake->body, snake->length, food->barriers);
            
            draw->gotoXY(MAP_WIDTH + 10, 5);
            cout << "Now Score: " << snake->length - 3;
        }
        
        gameOver = snake->checkCollision(food->barriers);  
        Sleep(snake->speed); 
    }
    
    system("cls");
    draw->gotoXY(45, 14); 
    cout << "Final Score: " << snake->length - 3;
    draw->gotoXY(45, 16);  
    cout << "Game Over!";
    draw->gotoXY(45, 18); 
    cout << "Press any key return to the ranking list";
    _getch();
    
    saveScore(snake->length - 3);
    menu->showRanking(); 
}

void Game::runGame_two(){ // 竞速模式

}

void Game::runGame_three(){ // 障碍模式

}

void Game::choose_runGame(){
    system("cls");
    draw->gotoXY(40, 12);
    cout << "Choose your mode:";
    draw->gotoXY(43, 14);
    cout << "Press 1 Endless Mode";
    draw->gotoXY(43, 16);
    cout << "Press 2 Speed Mode";
    draw->gotoXY(43, 18);
    cout << "Press 3 Barrier Mode";
    draw->gotoXY(43, 20);
    cout << "Press any other key to return to the main menu";
    
    char choice = _getch();
    switch (choice) {
        case '1':
            runGame_one();
            break;
        case '2':
            runGame_two();
            break;
        case '3':
            runGame_three();
            break;
        default:
            return;
    }
}


void Game::run() {
    while (true) {
        menu->showMenu();  
        char choice = _getch();
        switch (choice) {
            case '1':
                choose_runGame();
                break;
            case '2':
                menu->showHelp();  
                break;
            case '3':
                menu->showAbout();  
                break;
            default:
                return;
        }
    }
}