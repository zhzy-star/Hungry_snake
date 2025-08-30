#ifndef MENU_H
#define MENU_H

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
#include "draw.h"

class Menu{
public:
    Draw draw;
    void showAbout();
    void showHelp();
    void showRanking();
    void showMenu();
};

#endif