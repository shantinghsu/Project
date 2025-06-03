#include <iostream>
#include <conio.h>      // 用於 _kbhit() 和 _getch()（Windows 專用）
#include <windows.h>    // 用於 Sleep()
#include <string>
#include <time.h>

using namespace std;

const int HEIGHT = 4;
const int WIDTH = 32;
const int JUMP_HOLD = 2;

/*
0 - sky - cloud
1 - sky
2 - dino/obstacle
3 - ground

<demo>
0                    ~
1 
2 R                       @
3 /\/\/\/\/\/\/\/\/\/\/\/\/\
*/


int main() {
    srand(time(0));

    int fps = 100;
    int score = 0;
    int last_speedup_score = 0;
    bool game_over = false;

    char cloud = '~';
    int cloud_x = WIDTH - 1;
    int cloud_y = 0;
    
    char dino = 'R';
    int dino_x = 2;
    int dino_y = 2;
    int jump_timer = 0;

    char box = '@';
    int box_x = WIDTH - 1;
    int box_y = 2;
    int box_delay = rand() % 20 + 10;

    string ground = "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\";

    //every movement in one fps
    while (!game_over)
    {
        //catch user keyboard - space
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == ' ')
                jump_timer = JUMP_HOLD; // start jump
        }

        //dino position control - jump
        if (jump_timer == JUMP_HOLD && dino_y > 0)
        {
            dino_y--; // jump up
            cout << "dinoY: " << dino_y << endl;
        }

        //cloud position - translation - move left
        if (cloud_x < WIDTH && cloud_x > 0)
        {
            cloud_x--;
        }
        else
        {
            cloud_x = WIDTH - 1;
        }

        //obstacle
        if (box_x < WIDTH && box_x > 0)
        {
            box_x--;
            box_delay--;
        }
        else
        {
            if (box_delay > 0)
            {
                box_delay--;
            }
            else
            {
                box_delay = rand() % 20 + 10;
                box_x = WIDTH - 1;
            }
        }
            

        //update gaming status & score
        if (dino_x == box_x)
        {   
            if (dino_y == box_y)
                game_over = true;
            else
                score++;
        }

        system("cls");

        //background
        for (int y = 0; y < HEIGHT - 1; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                if (cloud_x == x && cloud_y == y)
                    cout << cloud;
                else if (dino_x == x && dino_y == y)
                    cout << dino;
                else if (box_x == x && box_y == y)
                    cout << box;
                else
                    cout << " ";
            }
            cout << endl;
        }
        ground.erase(0, 1);
        ground += (ground[0] == '/') ? '\\' : '/';
        cout << ground << endl;

        cout << "score: " << score << endl;
        cout << "last score: " << last_speedup_score << endl;
        cout << "fps: " << fps << endl;

        if (jump_timer > 0)
        {
            jump_timer--;
        }
        else if (dino_y < 2)
            dino_y++;

        //speed of fps
        if ((score - last_speedup_score) >= 5 && fps > 10)
        {
            if (score % 5 == 0)
            {
                last_speedup_score = score;
            }
            fps -= 10;
        }
        Sleep(fps);
    }


    cout << "\nGame Over! \nFinal Score: " << score << endl;
    return 0;
}
