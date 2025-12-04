/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 10      // width of game field
#define H 8       // height of game field
#define MAX_B 3   // maximum bullets on screen

int main() {
    srand(time(NULL)); 
    int px = W/2, score = 0, gameOver = 0;
    int bx[MAX_B] = {0}, by[MAX_B] = {0}, ba[MAX_B] = {0};

    // Single enemy x and y
    int ex = rand() % W, ey = 0;

    int i;
    while(!gameOver){
        printf("\n======== MINI SHOOTER ========\n");
        printf("Score: \033[33m%d\033[0m  Controls: 4=Left 6=Right 5=Shoot\n",score);

        // Draw the game field
        int x,y;
        for(y=0; y<H; y++){
            for(x=0; x<W; x++){
                if(x==px && y==H-1) 
				printf("\033[32m^\033[0m ");
                else if(x==ex && y==ey) 
				printf("\033[31mX\033[0m "); // Enemy in red
                else {
                    int draw=0;
                    // Draw bullets in yellow
                    for(i=0;i<MAX_B;i++)
                        if(ba[i] && bx[i]==x && by[i]==y)
						{ printf("\033[33m|\033[0m "); draw=1; break; }
                    if(!draw) printf("\033[34m.\033[0m "); //  for Background in blue
                }
            }
            printf("\n");
        }
        for(i=0;i<MAX_B;i++){
            if(ba[i]){      
            
                by[i]--;      
                if(by[i]<0) ba[i]=0;
            }
        }


        ey++; 
        if(ey>=H){ gameOver=1; break; } // if enemy reaches bottom -> game over

        for(i=0;i<MAX_B;i++)
            if(ba[i] && bx[i]==ex && by[i]==ey){ // bullet hits enemy
                score++;               // increase score
                ba[i]=0;               // deactivate bullet
                ey=0; ex=rand()%W;    
                printf("\a");          
            }

        int m;
        printf("Move: "); scanf("%d",&m);
        if(m==4 && px>0) px--;          // move left
        else if(m==6 && px<W-1) px++;   // move right
        else if(m==5)                    // shoot
            for(i=0;i<MAX_B;i++){
                if(!ba[i]){         
                    ba[i]=1; bx[i]=px; by[i]=H-2; // activate bullet above player
                    printf("\a");        // for shoot sound
                    break;
                }
            }
    }

    
    printf("\n\033[31mGAME OVER!\033[0m\nFinal Score: %d\n",score);

    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 10
#define H 8
#define MAX_B 3
#define ENEMIES 3

// Colors
#define RED   "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE   "\033[34m"
#define MAGNETA   "\033[35m"
#define RESET "\033[0m"

void clear(){
    system("clear");  // or "CLS" on windows
}

int main() {
    srand(time(NULL));

    int px = W/2, score = 0, gameOver = 0;

    // bullets
    int bx[MAX_B] = {0}, by[MAX_B] = {0}, ba[MAX_B] = {0};

    // multiple enemies
    int ex[ENEMIES], ey[ENEMIES];
    int e;
    for(e=0; e<ENEMIES; e++){
        ex[e] = rand() % W;
        ey[e] = 0;
    }

    while(!gameOver){
        clear();
        printf("Score: \033[33m%d\033[0m  Controls: 4=Left 6=Right 5=Shoot\n",score);
        printf(MAGNETA "====== MINI SHOOTER ======\n" RESET);
        printf("Score: " YELLOW "%d\n\n" RESET, score);

        // -------- DRAW FIELD --------
        int x,y;
        for(y=0; y<H; y++){
            for(x=0; x<W; x++){

                // Player
                if(x==px && y==H-1){
                    printf(GREEN "^ " RESET);
                }
                else {
                    int drawn = 0;

                    // enemies
                    for(e=0; e<ENEMIES; e++){
                        if(ex[e]==x && ey[e]==y){
                            printf(RED "X " RESET);
                            drawn = 1;
                            break;
                        }
                    }

                    // bullets
                    if(!drawn){
                        int i;
                        for(i=0;i<MAX_B;i++){
                            if(ba[i] && bx[i]==x && by[i]==y){
                                printf(YELLOW "| " RESET);
                                drawn = 1;
                                break;
                            }
                        }
                    }

                    // background
                    if(!drawn) printf(BLUE ". " RESET);
                }
            }
            printf("\n");
        }

        // -------- MOVE BULLETS --------
		int i;
        for(i=0;i<MAX_B;i++){
            if(ba[i]){
                by[i]--;
                if(by[i] < 0) ba[i] = 0;
            }
        }

        // -------- MOVE ENEMIES --------
        for(e=0; e<ENEMIES; e++){
            ey[e]++;

            if(ey[e] >= H){
                gameOver = 1;
            }
        }

        // -------- COLLISIONS --------
        for(e=0; e<ENEMIES; e++){
        	int i;
            for(i=0;i<MAX_B;i++){
                if(ba[i] && bx[i] == ex[e] && by[i] == ey[e]){
                    ba[i] = 0;

                    printf(RED "\nBOOM!\a\n" RESET);

                    score++;

                    // respawn enemy
                    ex[e] = rand() % W;
                    ey[e] = 0;
                }
            }
        }

        // -------- INPUT --------
        int m;
        printf("\nMove: ");
        scanf("%d",&m);

        if(m==4 && px>0) px--;
        else if(m==6 && px<W-1) px++;
        else if(m==5){
        	int i;
            for(i=0;i<MAX_B;i++){
                if(!ba[i]){
                    ba[i] = 1;
                    bx[i] = px;
                    by[i] = H-2;
                    printf("\a");
                    break;
                }
            }
        }
    }

    clear();
    printf(RED "\nGAME OVER\n" RESET);
    printf("Final Score: " YELLOW "%d\n" RESET, score);

    return 0;
}

