#include "draw.h"

void Draw::drawBorder() {
    for (int i = 0; i < MAP_WIDTH; i++) {
        gotoXY(i, 0);
        if (i % 2 == 0){
            std::cout << "=";
        }else{
            std::cout << "*";
        }
        gotoXY(i, MAP_HEIGHT - 1);
        if (i % 2 != 0){
            std::cout << "=";
        }else{
            std::cout << "*";
        }
        
    }
    for (int i = 1; i < MAP_HEIGHT; i++) {
        gotoXY(0, i);
        std::cout << "[";
        gotoXY(MAP_WIDTH - 1, i);
        std::cout << "]";


    }
}

void Draw::gotoXY(int x, int y) {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cor;
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

void Draw::hideCursor() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = {1, 0};
    SetConsoleCursorInfo(hout, &cor_info);
}
