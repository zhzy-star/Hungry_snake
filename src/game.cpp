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

void Game::runGame() {
    system("cls");
    food->barriers.clear();  // 使用箭头操作符
    snake->length = 3;       // 使用箭头操作符
    snake->speed = 250;      // 使用箭头操作符
    nowDir = RIGHT;
    gameOver = false;
    
    draw->drawBorder();      // 使用箭头操作符
    snake->initializeSnake(); // 使用箭头操作符
    
    food->generateFood(rand() % 3, snake->body, snake->length, food->barriers);
    food->generateBarrier(snake->body, snake->length, food->barriers);
    
    draw->gotoXY(MAP_WIDTH + 10, 5);  // 使用箭头操作符
    cout << "Now Score: 0";
    
    while (!gameOver) {
        handleInput();
        snake->moveSnake(nowDir);  // 使用箭头操作符并传递参数
        gameOver = snake->checkCollision(food->barriers);  // 使用箭头操作符
        Sleep(snake->speed);  // 使用箭头操作符
    }
    
    system("cls");
    draw->gotoXY(45, 14);  // 使用箭头操作符
    cout << "Final Score: " << snake->length - 3;  // 使用箭头操作符
    draw->gotoXY(45, 16);  // 使用箭头操作符
    cout << "Game Over!";
    draw->gotoXY(45, 18);  // 使用箭头操作符
    cout << "Press any key return to the ranking list";
    _getch();
    
    saveScore(snake->length - 3);  // 使用箭头操作符
    menu->showRanking();  // 使用箭头操作符
}

void Game::run() {
    while (true) {
        menu->showMenu();  // 使用箭头操作符
        char choice = _getch();
        switch (choice) {
            case '1':
                runGame();
                break;
            case '2':
                menu->showHelp();  // 使用箭头操作符
                break;
            case '3':
                menu->showAbout();  // 使用箭头操作符
                break;
            default:
                return;
        }
    }
}