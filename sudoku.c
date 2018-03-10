#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define ROW_THREADS 1
#define COL_THREADS 1
#define SUB_THREADS 9

int board[9][9];
int solution[11];

typedef struct{
    int row;
    int column;
} box;

void readFile(FILE *fp){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            fscanf(fp, "%d", &board[i][j]);
        }
    }
}
void *rowCheck(){
    int *isValid = (int*)1;
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
void *colCheck(){
   int *colValid = (int*)1;
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
void *subCheck(void * grid){
    int *boxValid = (int*)1;
    int pos;
    int boxVal[9] = {0};
    box *sub = grid; 
    int gcol = sub->column;
    int grow = sub->row;


    for(int col=0;col<3;col++){
        for(int row=0;row,3;row++){
            pos = board[row+grow][col+gcol];
            if(boxVal[pos -1]==0){
                boxVal[pos -1] =1;
            }
            else{
                boxValid = 0;
                break;
            }
        }
    }
    return boxValid;
}

int check(int a[]){
    int fullValid = 1;
    for(int i=0;i<8;i++){
        if(a[i] != a[i+1]){
            fullValid = 0;
        }
        else{
            fullValid =1;
        }
    }
    return fullValid;
        
}
int main(){
    FILE *fp = fopen("puzzle.txt", "r");
    readFile(fp);

    pthread_t r_thd;
    pthread_t c_thd;
    pthread_t b_thd[9];

    box box[9];

    pthread_create(&r_thd, 0, rowCheck, (void*) "Check Rows");
    pthread_create(&c_thd, 0, colCheck, (void*) "Column Check");
    int i=0;
    for(int cols=0;cols<=6;cols+=3){
        for(int rws=0;rws<=6;rws+=3){
            box[i].column = cols;
            box[i].row = rws;
            pthread_create(&b_thd[i], 0, subCheck, &box[i]);
        }
    }
    for(int j=0;j<3;j++){
        void *solution[j];
        if(j==0){
            pthread_join(r_thd,&solution[j]);
        }
        if(j==2){
            pthread_join(c_thd,&solution[j]);
        }
        else{
            pthread_join(b_thd[i],&solution[j]);
        }
    }

    int isCorrect = check(solution);
    if(isCorrect){
        printf("Solution is valid");
    }
    else{
        printf("Solution is not valid");
    }



    fclose(fp);
    return 0;
}