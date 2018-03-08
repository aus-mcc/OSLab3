#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define ROW_THREADS 1
#define COL_THREADS 1
#define SUB_THREADS 9


int rowCheck(FILE *fp, int lineNum){
    int count = 0;
    if(fp != NULL){
        char line[256];
        while(fgets(line, sizeof line, fp) != NULL){
            if (count == lineNum){
                // do the check
            }
            else{
                count++;
            }
        }
    }
}
int colCheck(FILE *fp, int colNum){
    int count = 0;
    if(fp!=NULL){
        char word[30];
        while(!feof(fp)){
            fscanf(fp, "%s%*[^\n]", word);
            // do check
        }
    }
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

    fclose(fp);
    return 0;
}