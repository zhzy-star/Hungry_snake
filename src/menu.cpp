#include "menu.h"

void Menu::showAbout() {
    system("cls");
    draw.gotoXY(30, 12);
    std::cout << "Week three";
    draw.gotoXY(43, 14);
    std::cout << "Hungry_Snake";
    draw.gotoXY(43, 16);
    std::cout << "Press any key return to the main menu";
    draw.hideCursor();
    _getch();
}

void Menu::showHelp() {
    system("cls");
    draw.gotoXY(40, 8);
    std::cout << "w--Up";
    draw.gotoXY(40, 10);
    std::cout << "s--Down";
    draw.gotoXY(40, 12);
    std::cout << "a--Left";
    draw.gotoXY(40, 14);
    std::cout << "d--Right";
    draw.gotoXY(40, 16);
    std::cout << "";
    draw.gotoXY(40, 18);
    std::cout << "'$'- one_score";
    draw.gotoXY(40, 20);
    std::cout << "'&'- three_score";
    draw.gotoXY(40, 22);
    std::cout << "'#'- five_score";
    draw.gotoXY(40, 26);
    std::cout << "'*'- Game_over";   
    draw.gotoXY(45, 28);       
    std::cout << "Press any key return to the main menu";
    draw.hideCursor();
    _getch();
}

void Menu::showRanking() {
    std::vector<int> scores;
    std::ifstream inFile(SCORE_FILE.c_str());
    
    if (!inFile) {
        draw.gotoXY(40, 10);
        std::cout << "No Data";
        draw.gotoXY(40, 12);
        std::cout << "Press any key return to the main menu";
        _getch();
        return;
    }
    
    int score;
    while (inFile >> score && scores.size() < MAX_SCORES) {
        scores.push_back(score);
    }
    inFile.close();
    
    std::sort(scores.rbegin(), scores.rend());
    
    system("cls");
    draw.gotoXY(40, 10);
    std::cout << "Ranking List:";
    for (size_t i = 0; i < std::min((size_t)10, scores.size()); i++) {
        draw.gotoXY(40, 12 + (int)i);
        std::cout << i + 1 << ". " << scores[i];
    }
    draw.gotoXY(40, 8);
    std::cout << "Press any key return to the main menu";
    _getch();
}


void Menu::showMenu() {
    system("cls");
    draw.gotoXY(40, 12);
    std::cout << "Welcome to Hungry_Snake!";
    draw.gotoXY(43, 14);
    std::cout << "Press 1 Start Game";
    draw.gotoXY(43, 16);
    std::cout << "Press 2 Get the Help";
    draw.gotoXY(43, 18);
    std::cout << "Press 3 Get the Details";
    draw.gotoXY(43, 20);
    std::cout << "Press any key to exit the game";
    draw.hideCursor();
}

