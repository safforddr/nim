/*
 * nim in C with minimax computer play.
 * This version of nim has four rows of 1, 3, 5, 7 items.
 * Each turn a player can remove 1, 2, or 3 items from one row.
 * This is a misere game in which the player who takes the last item loses.
 * This program looks at all possible boards, and lists winning ones 
 * (that is, boards you want to give to your opponent to make them lose.)
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1
#define MIN -1

/* sum of all rows */
int bsum(int b[4]) {
    return(b[0] + b[1] + b[2] + b[3]);
}

/* recursive play, maximize if max is 1, minimize if max is -1 */
int minimax(int board[4], int max) {
    
    int b[4];
    int score, thisscore, bestscore;
    int i, r, c;
    
    if (bsum(board) == 0){    
        return(max);
    } 
    /* for misere game, one item left is losing */
    if (bsum(board) == 1) {
        return(-1 * max);
    }      
    if (max == 1)
        bestscore = -2;
    else
        bestscore = 2;
    
    /* try all legal moves */
    for(r = 0; r < 4; r++) {
        for(c = 1; c < 4; c++) {  
            for(i = 0; i < 4; i++)
                b[i] = board[i];             
            if(b[r] >= c) {
                b[r] -= c;
                thisscore = minimax(b, max * -1);
                if (max == 1) {
                    if(thisscore > bestscore) {
                        bestscore = thisscore;
                    }  
                } else {
                    if (thisscore < bestscore) {
                        bestscore = thisscore;               
                    }
                }
            }
        }
    }
    if((bestscore == -2) || (bestscore == 2)) 
        return 0;
    return bestscore;
}

int main(int argc, char *argv[]) {
    static int board[4];
    int r0, r1, r2, r3, count = 1, total = 1; 
    
    /* for each possible state of each row, see if it is a winning board */
    for(r0 = 0; r0 < 2; r0++) {
        for(r1 = 0; r1 < 4; r1++) {
            for(r2 = 0; r2 < 6; r2++) {
                for(r3 = 0; r3 < 8; r3++) {
                    board[0] = r0;
                    board[1] = r1;
                    board[2] = r2;
                    board[3] = r3;
                    if(bsum(board) > 0) {
                        total++;
                        if(minimax(board, MAX) == -1) {
                            printf("Winning board %d {%d, %d, %d, %d}\n", 
                                count++, board[0], board[1], board[2], board[3]);
                        }
                    }
                }
            }
        }
    }
    printf("\nTotal winning boards %d of possible %d\n", count - 1, total);
}
