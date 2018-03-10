#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define ROW_THREADS 1
#define COL_THREADS 1
#define SUB_THREADS 9

int board[9][9]; // sudoku board
int solution[11]; // array to hold returns from funcs

// struct to hold the start coordinated for the sub grid check
typedef struct{
    int row;
    int column;
} box;


// function to read the file
void readFile(FILE *fp){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            fscanf(fp, "%d", &board[i][j]);
        }
    }
}

// Check Row
void *rowCheck(){
    int *isValid = (int*)1; // if returns 1 the rows are valid
    for(int r=0;r<9;r++){ // for each row
        int used[9]={0}; // array to see which numbers are used
        for(int v=0;v<9;v++){ // check each element
            if(used[board[r][v]-1]==0){ // set element as used
                used[board[r][v]-1] =1;
            }
            else{ // if element has been used before
                isValid = 0;
                break;
            }
        }
    }
    return isValid;
}

// COlumn Check
void *colCheck(){
   int *colValid = (int*)1; // Return value for the function
   for(int c=0;c<9;c++){ // for each column
       int colUsed[9] = {0}; // array to see which numbers are used
       for(int b=0;b<9;b++){ // for each element in the column
           int cur = board[b][c];
           if(colUsed[cur-1]==0){ //if value has not been used
               colUsed[cur-1] = 1; // set it ot used
           }
           else{ // else value has been used
               colValid = 0;
               break;
           }
       }
    }
    return colValid;
}

// Check Subgrid
void *subCheck(void * grid){
    int *boxValid = (int*)1; // Return value for function
    int pos;
    int boxVal[9] = {0}; // array to see which numbers are used
    box *sub = grid; // make box struct
    int gcol = sub->column; // pass the values into struct
    int grow = sub->row;


    for(int col=0;col<3;col++){ // for each column in box
        for(int row=0;row,3;row++){ // for each row in box
            pos = board[row+grow][col+gcol]; //start index
            if(boxVal[pos -1]==0){ // if value has not been used
                boxVal[pos -1] =1; // set  it as used
            }
            else{ // else value has been used
                boxValid = 0;
                break;
            }
        }
    }
    return boxValid;
}

int check(int a[]){ //function to check solution array
    int fullValid = 1;

    // Loop that checks to see if all elements in the array are the same
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
    FILE *fp = fopen("puzzle.txt", "r"); // Open file
    readFile(fp); // call readFile function


    // Define the threads
    pthread_t r_thd;
    pthread_t c_thd;
    pthread_t b_thd[9];

    box box[9]; // create box struct

    // Create all threads
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

    // Join all threads and have the return values entered into the solutions array
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
    // Check if all elements in solution array are the same
    int isCorrect = check(solution);
    if(isCorrect){
        printf("Solution is valid\n");
    }
    else{
        printf("Solution is not valid\n");
    }



    fclose(fp);
    return 0;
}