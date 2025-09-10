#include "music.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <iostream>
using namespace std;

void Music::playBackgroundMusic() {
    // 检查文件是否存在，如果不存在则静默失败
    if (GetFileAttributes(TEXT("background.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
}

void Music::eat_food() {
    if (GetFileAttributes(TEXT("eat.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(1000, 100); // 备用音效
    }
}

void Music::eat_buff() {
    if (GetFileAttributes(TEXT("buff.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("buff.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(1500, 150); // 备用音效
    }
}

void Music::game_over() {
    if (GetFileAttributes(TEXT("gameover.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(500, 500); // 备用音效
    }
}

void Music::win() {
    if (GetFileAttributes(TEXT("win.wav")) != INVALID_FILE_ATTRIBUTES) {
        PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        Beep(2000, 300); // 备用音效
    }
}