#include "menu.h"
#include <iostream>
#include <algorithm>
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
    draw.gotoXY(40, 8);
    cout << "w--Up";
    draw.gotoXY(40, 10);
    cout << "s--Down";
    draw.gotoXY(40, 12);
    cout << "a--Left";
    draw.gotoXY(40, 14);
    cout << "d--Right";
    draw.gotoXY(40, 16);
    cout << "";
    draw.gotoXY(40, 18);
    cout << "'$'- one_score";
    draw.gotoXY(40, 20);
    cout << "'&'- three_score";
    draw.gotoXY(40, 22);
    cout << "'#'- five_score";
    draw.gotoXY(40, 26);
    cout << "'*'- Game_over";   
    draw.gotoXY(45, 28);       
    cout << "Press any key return to the main menu";
    draw.hideCursor();
    _getch();
}

void Menu::showRanking() {
    vector<int> scores;
    ifstream inFile(SCORE_FILE.c_str());
    
    if (!inFile) {
        draw.gotoXY(40, 10);
        cout << "No Data";
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
    
    sort(scores.rbegin(), scores.rend());
    
    system("cls");
    draw.gotoXY(40, 10);
    cout << "Ranking List:";
    for (size_t i = 0; i < min((size_t)10, scores.size()); i++) {
        draw.gotoXY(40, 12 + (int)i);
        cout << i + 1 << ". " << scores[i];
    }
    draw.gotoXY(40, 8);
    cout << "Press any key return to the main menu";
    _getch();
}

void Menu::showMenu() {
    system("cls");
    draw.gotoXY(40, 12);
    cout << "Welcome to Hungry_Snake!";
    draw.gotoXY(43, 14);
    cout << "Press 1 Start Game";
    draw.gotoXY(43, 16);
    cout << "Press 2 Get the Help";
    draw.gotoXY(43, 18);
    cout << "Press 3 Get the Details";
    draw.gotoXY(43, 20);
    cout << "Press any key to exit the game";
    draw.hideCursor();
}