#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define ROW_THREADS 1
#define COL_THREADS 1
#define SUB_THREADS 9

int board[9][9];
int rowCheck(FILE *fp, int lineNum){
    int isValid = 1;
    for(int r=0;r<9;r++){
        int used[9]={0};
        for(int v=0;v<9;v++){
            if(used[board[r][v]-1]==0){
                used[board[r][v]-1] =1;
            }
            else{
                isValid = 0;
                break;
            }
        }
    }
    return isValid;
}
int colCheck(FILE *fp, int colNum){
   int colValid = 1;
   for(int c=0;c<9;c++){
       int colUsed[9] = {0};
       for(int b=0;b<9;b++){
           int cur = board[c][b];
           if(colUsed[cur-1]==0){
               colUsed[cur-1] = 1;
           }
           else{
               colValid = 0;
               break;
           }
       }
    }
    return colValid;
}
int subCheck(int startRow, int startCol, FILE *fp){
    for(int r = startRow; r<startRow+3; r++){
        rowCheck(fp, r);
    }
    for(int c = startCol; c<startCol+3;c++){
        colCheck(fp, c);
    }
}


int main(){

    int checked[11]; // array to hold check validation

    FILE *fp = fopen("puzzle.txt", "r");
    int line = 0;
    rowCheck(fp, 1);

    fclose(fp);
    return 0;
}