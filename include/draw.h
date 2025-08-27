#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <string>

class Draw{
pubilc:
    void drawBorder();
    void gotoXY(int x, int y);
    void hideCursor();
};