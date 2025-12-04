#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_OBS 5      // number of obstacles

void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

int main() {

START_GAME:               // Restart label

    system("cls");
    system("color 1F");   // Blue background, white text

    srand(time(NULL));

    int x = 1;            // player lane: 0 left, 1 middle, 2 right
    int score = 0;
    int speed = 120;
    int minSpeed = 40;

    int obsLane[TOTAL_OBS];
    int obsStep[TOTAL_OBS];

    // initialize obstacles
    int i;
    for (i = 0; i < TOTAL_OBS; i++) {
        obsLane[i] = rand() % 3;
        obsStep[i] = rand() % 10;
    }

    // GAME LOOP ----------------------------------------------------
    while (1) {

        // INPUT ----------------------------------------------------
        if (_kbhit()) {
            char ch = getch();
            if (ch == 75 && x > 0) x--;      // left arrow
            if (ch == 77 && x < 2) x++;      // right arrow
        }

        // DRAW -----------------------------------------------------
        clear_screen_fast();

        printf("Score: %d\n", score);
        printf("|--- --- ---|\n");

        int row;
        for (row = 0; row < 10; row++) {

            int printed = 0;
            int k;
            for (k = 0; k < TOTAL_OBS; k++) {

                if (obsStep[k] == row) {

                    if (obsLane[k] == 0)
                        printf("| %c        |\n", 219);
                    else if (obsLane[k] == 1)
                        printf("|     %c    |\n", 219);
                    else
                        printf("|        %c |\n", 219);

                    printed = 1;
                    break;
                }
            }

            if (!printed)
                printf("|           |\n");
        }

        // PLAYER ---------------------------------------------------
        if (x == 0)
            printf("| %c         |\n", 30);
        else if (x == 1)
            printf("|     %c     |\n", 30);
        else
            printf("|        %c  |\n", 30);

        // COLLISION ------------------------------------------------
        int k;
        for (k = 0; k < TOTAL_OBS; k++) {
            if (obsStep[k] == 10 && obsLane[k] == x) {

                system("color 4F");   // red screen
                
                printf("\n\a\aGAME OVER!\n");   // beep sound
                printf("Final Score: %d\n", score);
                printf("\nPress R to Restart or Q to Quit\n");

                while (1) {
                    if (_kbhit()) {
                        char c = getch();
                        if (c == 'r' || c == 'R') {
                            system("color 1F");
                            goto START_GAME;
                        }
                        if (c == 'q' || c == 'Q')
                            return 0;
                    }
                }
            }
        }

        // DELAY ----------------------------------------------------
        Sleep(speed);

        // MOVE OBSTACLES -------------------------------------------
        for (k = 0; k < TOTAL_OBS; k++) {
            obsStep[k]++;

            if (obsStep[k] > 10) {        
                obsStep[k] = 0;
                obsLane[k] = rand() % 3;

                score++;
                printf("\a");             // small beep on score

                if (speed > minSpeed)
                    speed -= 2;
            }
        }
    }

    return 0;
}

