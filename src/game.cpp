#include "game.h"
#include "snake.h"
#include "draw.h"
#include "menu.h"
#include "food.h"
#include "music.h"
#include <iostream>
using namespace std;

Game::Game() : nowDir(RIGHT), gameOver(false) {
    snake = new Snake();
    menu = new Menu();
    draw = new Draw();
    food = new Food();
    music = new Music();
    srand((unsigned int)time(NULL));
}

void Game::setGameMode(GameMode mode) {
    currentMode = mode;
}

GameMode Game::getGameMode() const {
    return currentMode;
}

Game::~Game() {
    delete snake;
    delete menu;
    delete draw;
    delete food;
    delete music; 
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

void Game::handleWallPass() {
    if (snake->body[0].x <= 0) {
        snake->body[0].x = MAP_WIDTH - 2;
    } else if (snake->body[0].x >= MAP_WIDTH - 1) {
        snake->body[0].x = 1;
    } else if (snake->body[0].y <= 0) {
        snake->body[0].y = MAP_HEIGHT - 2;
    } else if (snake->body[0].y >= MAP_HEIGHT - 1) {
        snake->body[0].y = 1;
    }
}

// 激活无敌模式（通过食物触发）
void Game::activateGodMode() {
    if (!isGodModeActive) {
        isGodModeActive = true;
        godModeStartTime = clock();
        cout << "\a"; // 提示音
        // 视觉提示
        draw->gotoXY(MAP_WIDTH + 10, 12);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // 黄色
        cout << "GOD MODE ACTIVATED!";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 白色
    }
}

// 取消无敌模式
void Game::deactivateGodMode() {
    if (isGodModeActive) {
        isGodModeActive = false;
        setGameMode(MODE_NORMAL);
        // 视觉提示
        draw->gotoXY(MAP_WIDTH + 10, 12);
        cout << "                    "; // 清空提示
    }
}

// 获取无敌模式剩余时间
int Game::getGodModeRemainingTime() const {
    if (!isGodModeActive) return 0;
    int elapsed = (int)((clock() - godModeStartTime) * 1000 / CLOCKS_PER_SEC);
    return max(0, (GOD_MODE_DURATION - elapsed) / 1000);
}

// 无敌模式处理
void Game::handleGodMode() {
    if (isGodModeActive) {
        // 检查无敌模式是否结束
        setGameMode(MODE_INVINCIBLE);
        handleWallPass(); // 无敌模式下允许穿墙
        int elapsed = (int)((clock() - godModeStartTime) * 1000 / CLOCKS_PER_SEC);
        if (elapsed >= GOD_MODE_DURATION) {
            deactivateGodMode();
        }
        
        // 无敌模式下的视觉效果（闪烁）
        static int flashCounter = 0;
        flashCounter++;
        if (flashCounter % 5 == 0) { // 每5帧闪烁一次
            // 蛇头闪烁金色
            draw->gotoXY(snake->body[0].x, snake->body[0].y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // 黄色
            cout << "Q";
            // 蛇尾闪烁彩色
            for (int i = 1; i < snake->length; i++){
                draw->gotoXY(snake->body[snake->length - 1].x, snake->body[snake->length - 1].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand()%20); // 青色
                cout<<"O";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 恢复白色
            }

        }
    }
}

// 激活加速模式（通过食物触发）
void Game::activateSpeedBoost() {
    if (!isSpeedBoostActive) {
        isSpeedBoostActive = true;
        speedBoostStartTime = clock();
        originalSpeed = snake->speed; // 保存当前速度
        snake->speed /= SPEED_BOOST_MULTIPLIER; // 加速

        // 提示音
        cout << "\a";

        // 视觉提示
        draw->gotoXY(MAP_WIDTH + 10, 13);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // 绿色
        cout << "SPEED BOOST ACTIVATED!";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 白色
    }
}

// 取消加速模式
void Game::deactivateSpeedBoost() {
    if (isSpeedBoostActive) {
        isSpeedBoostActive = false;
        snake->speed = originalSpeed; // 恢复原始速度

        // 清空提示
        draw->gotoXY(MAP_WIDTH + 10, 13);
        cout << "                       "; // 清空提示
    }
}

// 获取加速模式剩余时间
int Game::getSpeedBoostRemainingTime() const {
    if (!isSpeedBoostActive) return 0;
    int elapsed = (int)((clock() - speedBoostStartTime) * 1000 / CLOCKS_PER_SEC);
    return max(0, (SPEED_BOOST_DURATION - elapsed) / 1000);
}

// 处理加速模式
void Game::handleSpeedBoost() {
    if (isSpeedBoostActive) {
        int elapsed = (int)((clock() - speedBoostStartTime) * 1000 / CLOCKS_PER_SEC);
        if (elapsed >= SPEED_BOOST_DURATION) {
            deactivateSpeedBoost();
        }

        // 视觉提示：蛇身闪烁绿色
        static int flashCounter = 0;
        flashCounter++;
        if (flashCounter % 5 == 0) {
            for (int i = 0; i < snake->length; i++) {
                draw->gotoXY(snake->body[i].x, snake->body[i].y);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // 绿色
                cout << (i == 0 ? "Q" : "O");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 白色
            }
        }
    }
}

void Game::check_level(){
    int dd = (snake->length - 3) / 10;
    switch (dd){
        case 0: food_level = 3; barrier_level = 1; break;
        case 4: food_level = 2; barrier_level = 2; break;
        default: food_level = 1; barrier_level = 3; break;
    }

}

void Game::initialize(){
    system("cls");
    food->barriers.clear();  
    snake->length = 3;      
    snake->speed = 250; 
    nowDir = RIGHT;
    gameOver = false;
    draw->drawBorder();     
    snake->initializeSnake(); 
    food->generateFood(rand() % 3, snake->body, snake->length, food->barriers);
}

void Game::food_check(int mode){
    // 检查蛇头是否与任何食物碰撞
    int flagg = 0;
    for (auto it = food->foods.begin(); it != food->foods.end(); ) {
        if (snake->body[0].x == it->x && snake->body[0].y == it->y) {
            // 根据食物类型处理
            switch (it->type) {
                case 0: case 1: case 2: case 3: // 1分食物
                    snake->length += 1;
                    music->eat_food();
                    break;
                case 4: case 5: case 6: // 3分食物
                    snake->length += 3;
                    music->eat_food();
                    break;
                case 7: // 5分食物
                    snake->length += 5;
                    music->eat_food();
                    break;
                case 8: case 9: // 加速食物
                    snake->length += 1;
                    music->eat_buff();
                    activateSpeedBoost();
                    break;
                case 10: // 无敌食物
                    music->eat_buff();
                    activateGodMode();
                    break;
            }
            flagg = 1;
            
           // 移除被吃的食物并在屏幕上清除
            draw->gotoXY(it->x, it->y);
            cout << " ";
            it = food->foods.erase(it);
            
            // 更新分数显示
            draw->gotoXY(MAP_WIDTH + 10, 5);
            cout << "Now Score: " << snake->length - 3;
            
            
        } else {
            ++it;
        }
    }
    if (flagg == 1){
        
        // 生成新食物（不要立即生成太多，避免屏幕被填满）
            if (food->foods.size() < 20) { // 控制食物数量
                for (int j = 0; j < food_level; j++){
                    food->generateFood(rand() % 11, snake->body, snake->length, food->barriers);
                }
            }
        // 只在障碍模式下生成新障碍物
            if (mode == 3){
                for (int i = 0; i < barrier_level; i++){
                    food->generateBarrier(snake->body, snake->length, food->barriers);
                }
            }
            

    }
    
}

void Game::end(){

}

void Game::saveScore(int score, GameType type) {
    std::string filename;
    switch (type) {
        case TYPE_ENDLESS:
            filename = SCORE_FILE_ENDLESS;
            break;
        case TYPE_SPEED:
            filename = SCORE_FILE_SPEED;
            break;
        case TYPE_BARRIER:
            filename = SCORE_FILE_BARRIER;
            break;
        default:
            filename = SCORE_FILE_ENDLESS;
    }
    
    ofstream outFile(filename.c_str(), ios::app);
    if (!outFile) {
        cerr << "无法保存分数到文件: " << filename << endl;
        return;
    }
    outFile << score << endl;
    outFile.close();
}

void Game::setGameType(GameType type) {
    currentType = type;
}

GameType Game::getGameType() const {
    return currentType;
}

void Game::runGame_one() { //无尽模式
    initialize();
    setGameMode(MODE_NORMAL);
    setGameType(TYPE_ENDLESS); // 设置游戏类型
    startTime = clock(); // 记录开始时间
    
    draw->gotoXY(MAP_WIDTH + 10, 5);  
    cout << "Now Score: 0";
    while (!gameOver) {
        music->playBackgroundMusic();
        handleInput();
        snake->moveSnake(nowDir);  
        snake->updateSpeed();
        handleGodMode();
        handleSpeedBoost(); 
        draw->drawBorder();
        check_level();

        food_check(1);

        gameOver = snake->checkCollision(food->barriers, getGameMode());  
        Sleep(snake->speed); 
    }
    
    system("cls");
    int finalScore = snake->length - 3;
    draw->gotoXY(45, 14); 
    cout << "Final Score: " << finalScore;
    draw->gotoXY(45, 16);  
    cout << "Game Over!";
    draw->gotoXY(45, 18); 
    cout << "Press any key return to the ranking list";
    _getch();
    
    saveScore(finalScore, TYPE_ENDLESS);
    menu->showRanking(TYPE_ENDLESS); 
}

void Game::runGame_two(){ // 竞速模式
    initialize();
    setGameMode(MODE_WALLPASS);
    setGameType(TYPE_SPEED); // 设置游戏类型
    startTime = clock(); // 记录开始时间
    
    draw->gotoXY(MAP_WIDTH + 10, 10);  
    cout << "Target Score: 100";
    draw->gotoXY(MAP_WIDTH + 10, 5);  
    cout << "Now Score: 0";
    draw->gotoXY(MAP_WIDTH + 10, 15);
    cout << "Time: 0s";

    while (!gameOver && !gameWin) {
        music->playBackgroundMusic();
        handleInput();
        handleWallPass();
        snake->moveSnake(nowDir);  
        snake->updateSpeed();
        handleGodMode();
        handleSpeedBoost(); 
        draw->drawBorder();
        
        food_check(2);
        check_level();

        // 更新计时器显示
        clock_t currentTime = clock();
        int elapsedSeconds = (int)((currentTime - startTime) / CLOCKS_PER_SEC);
        
        static int lastDisplayedSecond = -1;
        if (elapsedSeconds != lastDisplayedSecond) {
            draw->gotoXY(MAP_WIDTH + 10, 15);
            cout << "Time: " << elapsedSeconds << "s";
            lastDisplayedSecond = elapsedSeconds;
        }

        if (snake->length - 3 >= 100){
            gameWin = true;
            break;
        }
        
        gameOver = snake->checkCollision(food->barriers, getGameMode());  
        Sleep(snake->speed); 
    }
    
    system("cls");
    if (gameWin) {
        int elapsedSeconds = (int)((clock() - startTime) / CLOCKS_PER_SEC);
        draw->gotoXY(45, 14); 
        cout << "Congratulations! You Win!";
        draw->gotoXY(45, 16);  
        cout << "Time: " << elapsedSeconds << " seconds";
        draw->gotoXY(45, 18); 
        cout << "Press any key to view ranking";
        _getch();
        
        saveScore(elapsedSeconds, TYPE_SPEED); // 竞速模式保存时间（越小越好）
    } else {
        draw->gotoXY(45, 14); 
        cout << "Game Over!";
        draw->gotoXY(45, 16);  
        cout << "Final Score: " << snake->length - 3;
        draw->gotoXY(45, 18); 
        cout << "Press any key to continue";
        _getch();
    }
    
    menu->showRanking(TYPE_SPEED);
}

void Game::runGame_three(){ // 障碍模式
    initialize();
    setGameMode(MODE_NORMAL);
    setGameType(TYPE_BARRIER); // 设置游戏类型
    startTime = clock(); // 记录开始时间
    
    draw->gotoXY(MAP_WIDTH + 10, 5);  
    cout << "Now Score: 0";

    while (!gameOver) {
        music->playBackgroundMusic();
        handleInput();
        snake->moveSnake(nowDir);  
        snake->updateSpeed();
        handleGodMode();
        handleSpeedBoost(); 
        check_level();
        food_check(3);
        gameOver = snake->checkCollision(food->barriers, getGameMode());  
        Sleep(snake->speed); 
    }
    
    system("cls");
    int finalScore = snake->length - 3;
    draw->gotoXY(45, 14); 
    cout << "Final Score: " << finalScore;
    draw->gotoXY(45, 16);  
    cout << "Game Over!";
    draw->gotoXY(45, 18); 
    cout << "Press any key return to the ranking list";
    _getch();
    
    saveScore(finalScore, TYPE_BARRIER);
    menu->showRanking(TYPE_BARRIER);
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
    cout << "Press 4 View Endless Rankings";
    draw->gotoXY(43, 22);
    cout << "Press 5 View Speed Rankings"; 
    draw->gotoXY(43, 24);
    cout << "Press 6 View Barrier Rankings";
    draw->gotoXY(43, 26);
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
        case '4':
            menu->showRanking(TYPE_ENDLESS);
            break;
        case '5':
            menu->showRanking(TYPE_SPEED);
            break;
        case '6':
            menu->showRanking(TYPE_BARRIER);
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