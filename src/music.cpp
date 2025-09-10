#include "music.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <iostream>
using namespace std;

void Music::playBackgroundMusic() {
    if (GetFileAttributes(TEXT("sound/background.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("sound/background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
}

void Music::eat_food() {
    if (GetFileAttributes(TEXT("sound/eat.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("sound/eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(1000, 100); // 备用音效
    }
}

void Music::eat_buff() {
    if (GetFileAttributes(TEXT("sound/eat_buff.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("sound/eat_buff.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(1500, 150); // 备用音效
    }
}

void Music::game_over() {
    if (GetFileAttributes(TEXT("sound/gameover.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("sound/gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(500, 500); // 备用音效
    }
}

void Music::win() {
    if (GetFileAttributes(TEXT("sound/win.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("sound/win.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(2000, 300); // 备用音效
    }
}