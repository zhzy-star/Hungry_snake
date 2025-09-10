#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

const int MAP_HEIGHT = 30;
const int MAP_WIDTH = 80;
const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const int MAX_SCORES = 100;

// 不同模式的排行榜文件
const std::string SCORE_FILE_ENDLESS = "scores_endless.txt";
const std::string SCORE_FILE_SPEED = "scores_speed.txt";
const std::string SCORE_FILE_BARRIER = "scores_barrier.txt";

enum GameMode {
    MODE_NORMAL = 0,    // 正常模式（不能穿墙）
    MODE_WALLPASS = 1,   // 穿墙模式
    MODE_INVINCIBLE = 2 // 无敌模式
};

enum GameType {
    TYPE_ENDLESS = 1,   // 无尽模式
    TYPE_SPEED = 2,     // 竞速模式
    TYPE_BARRIER = 3    // 障碍模式
};

const int GOD_MODE_DURATION = 15000;
const int SPEED_BOOST_DURATION = 20000;  
const int SPEED_BOOST_MULTIPLIER = 2;   


#endif
