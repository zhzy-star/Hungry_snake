#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib> // 添加了cstdlib头文件

using namespace std;

const int MAP_HEIGHT = 30;
const int MAP_WIDTH = 80;
const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const int MAX_SCORES = 100;
const string SCORE_FILE = "scores.txt";

struct Position {
    int x;
    int y;
};

class Snake {
public:
    vector<Position> body;
    int length;
    int speed;
    char direction;
    
    Snake() : length(3), speed(250), direction(RIGHT) {
        body.resize(1000);
    }
};

class Game {
private:
    Snake snake;
    Position food;
    Position foods;
    Position foodss;
    vector<Position> barriers;
    char nowDir;
    bool gameOver;
    
    void gotoXY(int x, int y) {
        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cor;
        cor.X = x;
        cor.Y = y;
        SetConsoleCursorPosition(hout, cor);
    }
    
    void hideCursor() {
        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cor_info = {1, 0};
        SetConsoleCursorInfo(hout, &cor_info);
    }
    
    void drawBorder() {
        for (int i = 0; i < MAP_WIDTH; i++) {
            gotoXY(i, 0);
            cout << "-";
            gotoXY(i, MAP_HEIGHT - 1);
            cout << "-";
        }
        for (int i = 1; i < MAP_HEIGHT; i++) {
            gotoXY(0, i);
            cout << "|";
            gotoXY(MAP_WIDTH - 1, i);
            cout << "|";
        }
    }
    
    void generateFood(int type) {
        bool flag;
        Position newFood;
        
        do {
            flag = false;
            newFood.x = rand() % (MAP_WIDTH - 2) + 1;
            newFood.y = rand() % (MAP_HEIGHT - 2) + 1;
            
            for (size_t i = 0; i < snake.body.size() && i < (size_t)snake.length; i++) {
                if (snake.body[i].x == newFood.x && snake.body[i].y == newFood.y) {
                    flag = true;
                    break;
                }
            }
            
            for (size_t i = 0; i < barriers.size(); i++) {
                if (barriers[i].x == newFood.x && barriers[i].y == newFood.y) {
                    flag = true;
                    break;
                }
            }
            
            if ((type != 1 && newFood.x == food.x && newFood.y == food.y) ||
                (type != 0 && newFood.x == foods.x && newFood.y == foods.y) ||
                (type != 2 && newFood.x == foodss.x && newFood.y == foodss.y)) {
                flag = true;
            }
        } while (flag);
        
        switch (type) {
            case 1:
                food = newFood;
                gotoXY(food.x, food.y);
                cout << "$";
                break;
            case 0:
                foods = newFood;
                gotoXY(foods.x, foods.y);
                cout << "&";
                break;
            case 2:
                foodss = newFood;
                gotoXY(foodss.x, foodss.y);
                cout << "#";
                break;
        }
    }
    
    void generateBarrier() {
        bool flag;
        Position newBarrier;
        
        do {
            flag = false;
            newBarrier.x = rand() % (MAP_WIDTH - 2) + 1;
            newBarrier.y = rand() % (MAP_HEIGHT - 2) + 1;
            
            if ((newBarrier.x == food.x && newBarrier.y == food.y) ||
                (newBarrier.x == foods.x && newBarrier.y == foods.y) ||
                (newBarrier.x == foodss.x && newBarrier.y == foodss.y)) {
                flag = true;
                continue;
            }
            
            for (size_t i = 0; i < snake.body.size() && i < (size_t)snake.length; i++) {
                if (snake.body[i].x == newBarrier.x && snake.body[i].y == newBarrier.y) {
                    flag = true;
                    break;
                }
            }
            
            for (size_t i = 0; i < barriers.size(); i++) {
                if (barriers[i].x == newBarrier.x && barriers[i].y == newBarrier.y) {
                    flag = true;
                    break;
                }
            }
        } while (flag);
        
        barriers.push_back(newBarrier);
        gotoXY(newBarrier.x, newBarrier.y);
        cout << "*";
    }
    
    void initializeSnake() {
        snake.body[0].x = MAP_WIDTH / 2 - 1;
        snake.body[0].y = MAP_HEIGHT / 2 - 1;
        gotoXY(snake.body[0].x, snake.body[0].y);
        cout << "@";
        
        for (int i = 1; i < snake.length; i++) {
            snake.body[i].y = snake.body[i-1].y;
            snake.body[i].x = snake.body[i-1].x - 1;
            gotoXY(snake.body[i].x, snake.body[i].y);
            cout << "o";
        }
    }
    
    void updateSpeed() {
        int a = snake.length - snake.length % 3;
        switch (a) {
            case 6: snake.speed = 200; break;
            case 9: snake.speed = 180; break;
            case 12: snake.speed = 160; break;
            case 15: snake.speed = 140; break;
            case 18: snake.speed = 120; break;
            case 21: snake.speed = 100; break;
            case 24: snake.speed = 80; break;
            case 27: snake.speed = 60; break;
            case 30: snake.speed = 40; break;
            default: break;
        }
    }
    
    bool checkCollision() {
        if (snake.body[0].x == 0 || snake.body[0].y == 0 || 
            snake.body[0].x == MAP_WIDTH - 1 || snake.body[0].y == MAP_HEIGHT - 1) {
            return true;
        }
        
        for (size_t i = 0; i < barriers.size(); i++) {
            if (snake.body[0].x == barriers[i].x && snake.body[0].y == barriers[i].y) {
                return true;
            }
        }
        
        for (int i = 1; i < snake.length; i++) {
            if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
                for (int j = i; j < snake.length; j++) {
                    gotoXY(snake.body[j].x, snake.body[j].y);
                    cout << " ";
                }
                snake.length = i;
                gotoXY(MAP_WIDTH + 10, 5);
                cout << "当前得分：" << snake.length - 3;
                return false;
            }
        }
        
        return false;
    }
    
    void handleInput() {
        if (_kbhit()) {
            char input = _getch();
            switch (input) {
                case UP:
                    if (nowDir != DOWN) nowDir = input;
                    break;
                case DOWN:
                    if (nowDir != UP) nowDir = input;
                    break;
                case LEFT:
                    if (nowDir != RIGHT) nowDir = input;
                    break;
                case RIGHT:
                    if (nowDir != LEFT) nowDir = input;
                    break;
            }
        }
    }
    
    void moveSnake() {
        Position tail = snake.body[snake.length - 1];
        
        for (int i = snake.length - 1; i >= 1; i--) {
            snake.body[i] = snake.body[i - 1];
        }
        
        switch (nowDir) {
            case UP: snake.body[0].y--; break;
            case DOWN: snake.body[0].y++; break;
            case LEFT: snake.body[0].x--; break;
            case RIGHT: snake.body[0].x++; break;
        }
        
        gotoXY(snake.body[1].x, snake.body[1].y);
        cout << "o";
        gotoXY(snake.body[0].x, snake.body[0].y);
        cout << "@";
        
        bool ateFood = false;
        int foodType = -1;
        
        if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
            ateFood = true;
            foodType = 1;
        } else if (snake.body[0].x == foods.x && snake.body[0].y == foods.y) {
            ateFood = true;
            foodType = 0;
        } else if (snake.body[0].x == foodss.x && snake.body[0].y == foodss.y) {
            ateFood = true;
            foodType = 2;
        }
        
        if (ateFood) {
            int growth = (foodType == 1) ? 1 : (foodType == 0) ? 3 : 5;
            snake.length += growth;
            
            generateFood(rand() % 3);
            generateBarrier();
            
            gotoXY(MAP_WIDTH + 10, 5);
            cout << "当前得分：" << snake.length - 3;
            
            updateSpeed();
        } else {
            gotoXY(tail.x, tail.y);
            cout << " ";
        }
    }
    
    void saveScore(int score) {
        ofstream outFile(SCORE_FILE.c_str(), ios::app);
        if (!outFile) {
            cerr << "无法打开得分文件" << endl;
            return;
        }
        outFile << score << endl;
        outFile.close();
    }
    
    void showRanking() {
        vector<int> scores;
        ifstream inFile(SCORE_FILE.c_str());
        
        if (!inFile) {
            gotoXY(40, 10);
            cout << "暂无排行榜数据！";
            gotoXY(40, 12);
            cout << "按任意键返回主菜单";
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
        gotoXY(40, 10);
        cout << "积分排行榜";
        for (size_t i = 0; i < min((size_t)10, scores.size()); i++) {
            gotoXY(40, 12 + (int)i);
            cout << i + 1 << ". " << scores[i];
        }
        gotoXY(40, 8);
        cout << "按任意键返回主菜单";
        _getch();
    }
    
public:
    Game() : nowDir(RIGHT), gameOver(false) {
        srand((unsigned int)time(NULL));
    }
    
    void showMenu() {
        system("cls");
        gotoXY(40, 12);
        cout << "欢迎来到贪吃蛇小游戏";
        gotoXY(43, 14);
        cout << "1.开始游戏";
        gotoXY(43, 16);
        cout << "2.帮助";
        gotoXY(43, 18);
        cout << "3.关于";
        gotoXY(43, 20);
        cout << "其他任意键退出游戏";
        hideCursor();
    }
    
    void showHelp() {
        system("cls");
        gotoXY(40, 8);
        cout << "w 上";
        gotoXY(40, 10);
        cout << "s 下";
        gotoXY(40, 12);
        cout << "a 左";
        gotoXY(40, 14);
        cout << "d 右";
        gotoXY(40, 16);
        cout << "当蛇撞到自身或撞墙时游戏结束";
        gotoXY(40, 18);
        cout << "'$' 得一分";
        gotoXY(40, 20);
        cout << "'&' 得三分";
        gotoXY(40, 22);
        cout << "'#' 得五分";
        gotoXY(40, 26);
        cout << "'*' 游戏结束";   
        gotoXY(45, 24);       
        cout << "按任意键返回上级菜单";
        hideCursor();
        _getch();
    }
    
    void showAbout() {
        system("cls");
        gotoXY(30, 12);
        cout << "算法组培训第二周";
        gotoXY(43, 14);
        cout << "贪吃蛇游戏";
        gotoXY(43, 16);
        cout << "按任意键返回上级菜单";
        hideCursor();
        _getch();
    }
    
    void runGame() {
        system("cls");
        barriers.clear();
        snake.length = 3;
        snake.speed = 250;
        nowDir = RIGHT;
        gameOver = false;
        
        drawBorder();
        initializeSnake();
        
        generateFood(rand() % 3);
        generateBarrier();
        
        gotoXY(MAP_WIDTH + 10, 5);
        cout << "当前得分：0";
        
        while (!gameOver) {
            handleInput();
            moveSnake();
            gameOver = checkCollision();
            Sleep(snake.speed);
        }
        
        system("cls");
        gotoXY(45, 14);
        cout << "最终得分：" << snake.length - 3;
        gotoXY(45, 16);
        cout << "你输了！";
        gotoXY(45, 18);
        cout << "按任意键查看排行榜";
        _getch();
        
        saveScore(snake.length - 3);
        showRanking();
    }
    
    void run() {
        while (true) {
            showMenu();
            char choice = _getch();
            
            switch (choice) {
                case '1':
                    runGame();
                    break;
                case '2':
                    showHelp();
                    break;
                case '3':
                    showAbout();
                    break;
                default:
                    return;
            }
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}