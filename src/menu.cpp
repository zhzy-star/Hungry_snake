#include "menu.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

void Menu::showAbout() {
    system("cls");
    draw.gotoXY(30, 12);
    cout << "Week three";
    draw.gotoXY(43, 14);
    cout << "Hungry_Snake";
    draw.gotoXY(43, 16);
    cout << "Press any key return to the main menu";
    draw.hideCursor();
    _getch();
}

void Menu::showHelp() {
    system("cls");
    
    // 游戏标题
    draw.gotoXY(45, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "=== HUNGRY SNAKE HELP ===";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
    // 基本操作
    draw.gotoXY(35, 5);
    cout << "CONTROLS:";
    draw.gotoXY(35, 6);
    cout << "=========";
    
    draw.gotoXY(35, 8);
    cout << "W - Move Up";
    draw.gotoXY(35, 9);
    cout << "S - Move Down";
    draw.gotoXY(35, 10);
    cout << "A - Move Left";
    draw.gotoXY(35, 11);
    cout << "D - Move Right";
    draw.gotoXY(35, 12);
    cout << "ESC - Quit Game (during gameplay)";
    
    // 食物说明
    draw.gotoXY(35, 14);
    cout << "FOOD TYPES:";
    draw.gotoXY(35, 15);
    cout << "===========";
    
    draw.gotoXY(35, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "$";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << " - Basic Food (+1 point, +1 length)";
    
    draw.gotoXY(35, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "&";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << " - Premium Food (+3 points, +3 length)";
    
    draw.gotoXY(35, 19);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "#";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << " - Super Food (+5 points, +5 length)";
    
    draw.gotoXY(35, 20);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    cout << "%";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << " - Speed Boost (+1 point, 20s speed boost)";
    
    draw.gotoXY(35, 21);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "@";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << " - God Mode (15s invincibility + wall pass)";
    
    draw.gotoXY(35, 22);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "*";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << " - Barrier (Game over if hit)";
    
    // 游戏模式说明
    draw.gotoXY(35, 24);
    cout << "GAME MODES:";
    draw.gotoXY(35, 25);
    cout << "===========";
    
    draw.gotoXY(35, 27);
    cout << "1. Endless Mode - Survive as long as possible";
    draw.gotoXY(35, 28);
    cout << "2. Speed Mode - Reach 100 points quickly";
    draw.gotoXY(35, 29);
    cout << "3. Barrier Mode - Avoid increasing obstacles";
    
    // 游戏机制
    draw.gotoXY(35, 31);
    cout << "GAME MECHANICS:";
    draw.gotoXY(35, 32);
    cout << "===============";
    
    draw.gotoXY(35, 34);
    cout << "- Snake speeds up as it grows longer";
    draw.gotoXY(35, 35);
    cout << "- Higher levels spawn more food and barriers";
    draw.gotoXY(35, 36);
    cout << "- God mode makes you invincible to all hazards";
    draw.gotoXY(35, 37);
    cout << "- Speed boost doubles your movement speed";
    
    // 提示信息
    draw.gotoXY(35, 39);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "Tip: Plan your route to collect multiple foods at once!";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
    // 返回提示
    draw.gotoXY(45, 42);
    cout << "Press any key to return to main menu";
    
    draw.hideCursor();
    _getch();
}

void Menu::showRanking(GameType type) {
    string filename;
    string title;
    bool isSpeedMode = false;
    
    switch (type) {
        case TYPE_ENDLESS:
            filename = "scores_endless.txt";
            title = "Endless Mode Ranking:";
            break;
        case TYPE_SPEED:
            filename = "scores_speed.txt";
            title = "Speed Mode Ranking:";
            isSpeedMode = true;
            break;
        case TYPE_BARRIER:
            filename = "scores_barrier.txt";
            title = "Barrier Mode Ranking:";
            break;
        default:
            filename = "scores_endless.txt";
            title = "Ranking List:";
    }
    
    vector<int> scores;
    ifstream inFile(filename);
    
    if (!inFile) {
        system("cls");
        draw.gotoXY(40, 10);
        cout << "No Data for " << title;
        draw.gotoXY(40, 12);
        cout << "Press any key return to the main menu";
        _getch();
        return;
    }
    
    int score;
    while (inFile >> score && scores.size() < MAX_SCORES) {
        scores.push_back(score);
    }
    inFile.close();
    
    // 竞速模式需要按时间升序排列（时间越短越好）
    if (isSpeedMode) {
        sort(scores.begin(), scores.end());
    } else {
        // 其他模式按分数降序排列
        sort(scores.rbegin(), scores.rend());
    }
    
    system("cls");
    
    // 排行榜标题
    draw.gotoXY(45, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "=== " << title << " ===";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
    // 显示前10名
    for (size_t i = 0; i < min((size_t)10, scores.size()); i++) {
        draw.gotoXY(40, 5 + (int)i);
        
        // 前三名用不同颜色显示
        if (i == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // 金色
        else if (i == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 银色
        else if (i == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // 铜色
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); // 灰色
        
        if (isSpeedMode) {
            cout << i + 1 << ". " << scores[i] << " seconds";
        } else {
            cout << i + 1 << ". " << scores[i] << " points";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    
    if (scores.empty()) {
        draw.gotoXY(40, 10);
        cout << "No scores yet! Be the first to play!";
    }
    
    // 模式说明
    draw.gotoXY(35, 18);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    if (isSpeedMode) {
        cout << "Speed Mode: Complete 100 points in the shortest time";
    } else if (type == TYPE_ENDLESS) {
        cout << "Endless Mode: Get the highest score before game over";
    } else {
        cout << "Barrier Mode: Survive the increasing obstacles";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
    draw.gotoXY(45, 22);
    cout << "Press any key to return to menu";
    _getch();
}

void Menu::showMenu() {
    system("cls");
    
    // 游戏标题艺术字
    draw.gotoXY(35, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "  _   _ _   _ _   _ _____  __   _____           _     _   ";
    draw.gotoXY(35, 6);
    cout << " | | | | | | | \\ | |  _  \\/  | /  ___|         | |   | |  ";
    draw.gotoXY(35, 7);
    cout << " | | | | | | |  \\| | | | |`| | \\ `--.  ___ _ __| |_  | |  ";
    draw.gotoXY(35, 8);
    cout << " | | | | | | | . ` | | | | | |  `--. \\/ _ \\ '__| __| | |  ";
    draw.gotoXY(35, 9);
    cout << " | |_| | |_| | |\\  | |/ / _| |_/\\__/ /  __/ |  | |_  |_|  ";
    draw.gotoXY(35, 10);
    cout << "  \\___/ \\___/\\_| \\_/___/  \\___/\\____/ \\___|_|   \\__| (_)  ";
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
    // 菜单选项
    draw.gotoXY(45, 14);
    cout << "MAIN MENU";
    draw.gotoXY(45, 15);
    cout << "=========";
    
    draw.gotoXY(43, 17);
    cout << "1 - Start Game";
    draw.gotoXY(43, 18);
    cout << "2 - Game Help";
    draw.gotoXY(43, 19);
    cout << "3 - About";
    draw.gotoXY(43, 20);
    cout << "ESC - Exit Game";
    
    // 游戏提示
    draw.gotoXY(35, 25);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "Use W, A, S, D keys to control the snake";
    draw.gotoXY(35, 26);
    cout << "Collect different foods for special effects!";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    
    draw.hideCursor();
}