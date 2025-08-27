#include "game.h"
#include "snake.h"
#include "draw.h"

Game::Game() : nowDir(RIGHT), gameOver(false) {
    srand((unsigned int)time(NULL));
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
    std::ofstream outFile(SCORE_FILE.c_str(), std::ios::app);
    if (!outFile) {
        std::cerr << "No Data" << std::endl;
        return;
    }
    outFile << score << std::endl;
    outFile.close();
}

void Game::runGame() {
    system("cls");
    barriers.clear();
    snake.length = 3;
    snake.speed = 250;
    nowDir = RIGHT;
    gameOver = false;
    
    draw.drawBorder();
    snake.initializeSnake();
    
    foodm.generateFood(rand() % 3);
    foodm.generateBarrier();
    
    draw.gotoXY(MAP_WIDTH + 10, 5);
    std::cout << "Now Score: 0";
    
    while (!gameOver) {
        handleInput();
        snake.moveSnake();
        gameOver = checkCollision();
        Sleep(snake.speed);
    }
    
    system("cls");
    draw.gotoXY(45, 14);
    std::cout << "Final Score: " << snake.length - 3;
    draw.gotoXY(45, 16);
    std::cout << "Game Over!";
    draw.gotoXY(45, 18);
    std::cout << "Press any key return to the ranking list";
    _getch();
    
    saveScore(snake.length - 3);
    menu.showRanking();
}

void Game::run() {
    while (true) {
        menu.showMenu();
        char choice = _getch();
        switch (choice) {
            case '1':
                runGame();
                break;
            case '2':
                menu.showHelp();
                break;
            case '3':
                menu.showAbout();
                break;
            default:
                return;
        }
    }
}