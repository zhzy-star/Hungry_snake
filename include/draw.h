#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <windows.h>
#include "constants.h"

class Draw{
public:
    void drawBorder();
    void gotoXY(int x, int y);
    void hideCursor();
};

#endif