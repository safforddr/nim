/*
 * nim in C with minimax computer play.
 * This version of nim has four rows of 1, 3, 5, 7 items.
 * Each turn a player can remove 1, 2, or 3 items from one row.
 * This is a misere game in which the player who takes the last item loses.
 * The computer uses minimax to play optimally. 
 * If the human goes first the computer should always win.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1
#define MIN -1

void draw_board(int b[4]) {
   int i, j;
   int skip[4] = {6, 4, 2, 0};
   for (i=0; i<4; i++) {
       printf("Row %d:  %.*s", i, skip[i], "         ");
       for(j=0; j<b[i]; j++) {
           printf("X ");
       }
       printf("\n");
   }
}

// a sum of 1 is a losing board
int bsum(int b[4]) {
    return(b[0] + b[1] + b[2] + b[3]);
}

// recursive play, maximize if max is 1, minimize if max is -1
int minimax(int board[4], int max, int *br, int *bc) {
    
    int b[4];
    int score, thisscore, bestscore, bestr = -1, bestc = -1;
    int i, r, c;
    
    if (bsum(board) == 0){    
        return(max);
    }
  
    if (bsum(board) == 1) {
        return(-1 * max);
    }
        
    if (max == 1)
        bestscore = -2;
    else
        bestscore = 2;
    
    // try all legal moves
    for(r = 0; r < 4; r++) {
        for(c = 1; c < 4; c++) {  
            for(i = 0; i < 4; i++)
                b[i] = board[i];             
            if(b[r] >= c) {
                b[r] -= c;
                thisscore = minimax(b, max * -1, NULL, NULL);
                if (max == 1) {
                    if(thisscore > bestscore) {
                        bestscore = thisscore;
                        bestr = r;
                        bestc = c;
                    }  
                } else {
                    if (thisscore < bestscore) {
                        bestscore = thisscore;
                        bestr = r;
                        bestc = c;                  
                    }
                }
            }
        }
    }
    if(bestr == -1) 
        return 0;
    
    board[bestr] -= bestc;
    if (br)
        *br = bestr;
    if (bc)
        *bc = bestc;
    return bestscore;
}

void chosen_move(int b[4]){
    int r, c;
    for (;;) {
        printf("Enter row (0..3) and count (1..3): ");
        scanf("%d %d", &r, &c);
        if((r < 0) || (r > 3))
            continue;
        if((c < 1) || (c > 3))
            continue;
        if(b[r] < c)
            continue;
        b[r] -= c;
        return;
    }
}

void computer_move(int b[4]) {
    int br, bc;
    minimax(b, MAX, &br, &bc);    
}

void human_move(int b[4]) {
    printf("Human turn\n ");
    chosen_move(b); 
}

int main(int argc, char *argv[]) {
    static int board[4] = {1, 3, 5, 7};
    int player=0;
    unsigned turn;
    
    srand(time(NULL));
    if (argc == 2) {
        printf("Computer going first\n");
        player = 1;
    } else {
        printf("Human Going First\n");       
    } 

    printf("Starting board\n");
    draw_board(board);
    printf("\n");
    for(turn = 0; bsum(board) > 1; ++turn) {
        if((turn + player) % 2 == 1) {
            computer_move(board);
            if (bsum(board) == 1) {
                draw_board(board);
                printf("computer wins in %d turns!\n", turn + 1);
                break;
            }
        } else {
            human_move(board);
            if (bsum(board) == 1) {
                draw_board(board);
                printf("Human wins in %d turns!\n", turn + 1);
                break;
            }
        }
        draw_board(board);
        printf("\n");
    }
}
