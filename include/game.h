#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include "constants.h"
#include "music.h"

// 前向声明
class Snake;
class Menu;
class Draw;
class Food;
class Music;

class Game {
private:
    Snake* snake;
    Menu* menu;
    Draw* draw;
    Food* food;
    Music* music;
    clock_t startTime;
    GameMode currentMode;
    GameType currentType;
    bool isGodModeActive = false;
    clock_t godModeStartTime;
    bool isSpeedBoostActive = false;
    clock_t speedBoostStartTime;
    int originalSpeed; 
    int food_level = 6;
    int barrier_level = 1;
    char nowDir;
    bool gameOver;
    bool gameWin;
    void handleInput();
    void saveScore(int score, GameType type);
    
public:
    Game();
    ~Game();
    void check_level();
    void runGame();
    void initialize();
    void food_check(int modde);
    void end();
    void runGame_one();
    void runGame_two();
    void runGame_three();
    void choose_runGame();
    void setGameMode(GameMode mode);
    GameMode getGameMode() const;
    void setGameType(GameType type);
    GameType getGameType() const;
    void handleWallPass();
    void handleGodMode();
    void handleSpeedBoost();
    void run();
    // 无敌模式
    void activateGodMode();
    void deactivateGodMode();
    int getGodModeRemainingTime() const;
    // 加速模式
    void activateSpeedBoost();
    void deactivateSpeedBoost();
    int getSpeedBoostRemainingTime() const;
};

#endif
