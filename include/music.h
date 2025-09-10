#ifndef MUSIC_H
#define MUSIC_H

#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class Music {
public:
    void playBackgroundMusic();
    void eat_food();
    void eat_buff();
    void game_over();
    void win();
};

#endif