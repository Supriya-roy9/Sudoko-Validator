#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <time.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>



void display(int arr[9][9])
{
    printf("  ");
    for (int i = 0; i < 9; i++)
        printf(" %d. ", i + 1);

    printf("\n   ");
    for (int i = 0; i < 9; i++)
        printf(" __ ");

    printf("\n");
    for (int i = 0; i < 9; i++)
    {
        printf("%d. |", i + 1);
        for (int j = 0; j < 9; j++)
        {
            if (arr[i][j] == -1)
                printf("  | ");
            else
                printf(" %d| ", arr[i][j]);
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
        {
            printf("   ");
            for (int t = 0; t < 9; t++)
                printf(" ~~ ");
            printf("\n");
        }
    }
    printf("\n");
}



bool hasMinus(int arr[9][9])
{
    bool check = false;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (arr[i][j] == -1)
                check = true;
        }
    }
    return check;
}

void generate(int arr[9][9])
{
    int a = (rand() % 1000);
    int b = (rand() % 1000);
    int x = (rand() % 100);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            arr[i][j] = (arr[i][j] + ((a * b + x) % 9) + 1) % 9 + 1;
        }
    }

    int row, column, sgrad;
    char str[20] = "", c = 'a';

    do
    {
	printf("\n			 Select mode...\n");
        printf("\n			 (1) Beginner Mode \n");
        printf("			 (2) Medium Mode\n");
        printf("			 (3) Advance Mode\n\n			 ");
        fgets(str, 20, stdin);
        if (strlen(str) == 2)
        {
            c = str[0];
        }

        if (strlen(str) != 2 || !(c == '1' || c == '2' || c == '3'))
        {
            printf("\n\n			 Invalid entry!!!\n\n");
        }

    } while (!(c == '1' || c == '2' || c == '3'));

    sgrad = c - 48;
    sgrad = sgrad * 15 + 15;

    for (int i = 0; i < sgrad; i++)
    {
        row = (rand() % 9);
        column = (rand() % 9);

        if (arr[row][column] == (-1))
        {
            /*while (arr[row][column] != (-1))
            {
               if (row == 9 || column == 9)
                    break;
                row++;
                column++;
            }*/
            sgrad++;
        }
        if (arr[row][column] != (-1))
        {
            arr[row][column] = -1;
        }
    }
}

void provideBase(int arr[9][9], int arr1[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            arr[i][j] = arr1[i][j];
        }
    }
}

void insert(int arr[9][9])
{
    char rowch[20], columnch[20], valuech[20];
    int row, column, value;
    bool check = true;

    printf("			 Row: ");
    fgets(rowch, 20, stdin);
    if (strlen(rowch) == 2)
    {
        row = rowch[0];
        row -= 49;
    }
    else
        check = false;

    printf("			 Column: ");
    fgets(columnch, 20, stdin);
    if (strlen(columnch) == 2)
    {
        column = columnch[0];
        column -= 49;
    }
    else
        check = false;

    printf("			 Value: ");
    fgets(valuech, 20, stdin);
    if (strlen(valuech) == 2)
    {
        value = valuech[0];
        value -= 48;
    }
    else
        check = false;

    if ((row < 9 && row >= 0) && (column < 9 && column >= 0) && (value <= 9 && value > 0) && check)
{
	for(int i=0; i<9;i++)
	{
	for(int j=0; j<9; j++)
	{
	if(arr[i][j]==value)
		{
			printf("\n\n			 INVALID ENTRYYYY!!!!!!\n			 ENTRY HAS BEEN REPEATED!!!\n");
		printf("\n\n			 Program is terminating!!!\n\n");
		printf("\n\n			 Program is terminated!!!\n\n");
		exit(0);
		}
	}
	}
        arr[row][column] = value;
	

}
    else
        printf("			 Invalid entry! Please check your entry\n			 ");

    printf("\n");
}




/**
 * Structure that holds the parameters passed to a thread.
 * This specifies where the thread should start verifying.
 */
typedef struct 
{
    // The starting row.
    int row;
    // The starting column.
    int col;
    // The pointer to the arr.
    int (* arr)[9];
} parameters;

// Prototype for the walk_rows function.
void * walk_rows(void * params);

// Prototype for the walk_cols function.
void * walk_cols(void * params);

// Prototype for 3x3 square function.
void * check_square(void * params);




int main()
{
    printf("\n");
    //srand(time(0));

    int arr[9][9] = {
        {2, 8, 6, 9, 3, 7, 1, 5, 4},
        {3, 4, 5, 6, 8, 1, 7, 9, 2},
        {7, 1, 9, 2, 4, 5, 3, 6, 8},
        {1, 7, 4, 5, 6, 8, 9, 2, 3},
        {6, 3, 8, 7, 2, 9, 4, 1, 5},
        {5, 9, 2, 3, 1, 4, 6, 8, 7},
        {4, 5, 3, 1, 9, 2, 8, 7, 6},
        {8, 2, 1, 4, 7, 6, 5, 3, 9},
        {9, 6, 7, 8, 5, 3, 2, 4, 1}};

    int temp[9][9];

    provideBase(temp, arr);
    printf("\n		     ----------------:SUDOKU GAME:----------------\n");
    printf("\n\n			 Warm welcome! Have fun with the game!\n\n");

    char str[20], check = 'N';
    bool checkingForGenerate = false;
    bool checkingforNew = false;

    do
    {
        if (check == 'N' && checkingForGenerate == true && checkingforNew == false)
        {
            provideBase(arr, temp);
            generate(arr);
            display(arr);
        }
        if (check == 'N' && checkingForGenerate == false)
        {
            generate(arr);
            display(arr);
            checkingForGenerate = true;
        }

        printf("\n\n			 For a new Sudoku please press 'N'\n");
        printf("			 To continue please press 'F'\n");
	printf("			 To exit please press 'X'\n");
	printf("\n			 ");

        fgets(str, 20, stdin);
        str[0] = toupper(str[0]);

        if (strlen(str) == 2 && (str[0] == 'F' || str[0] == 'N'))
        {
            check = str[0];
            checkingforNew = false;
        }
	else if (strlen(str) == 2 && (str[0] == 'X'))
	{
		printf("\n\n			 Program is terminating!!!\n\n");
		printf("\n			 Program is terminated!!!\n\n");
		exit(0);
	}
        else
        {
            printf("\n\n			 Invalid Input!\n\n");
            checkingforNew = true;
        }

    } while (check != 'F');

    printf("\n			 Now it really starts!\n");
    printf("\n			 In the following, you should first enter the row\n");
    printf("			 and column numbers and then insert your number. \n			 We wish you success!\n\n");

    while (check != 'P')
    {
        if (hasMinus(arr) == false)
        {
            printf("			 To check your solution please press 'P'\n");
            printf("			 To continue please press any other key ...\n			 ");
            fflush(stdin);
            fgets(str, 20, stdin);
          
            if (strlen(str) == 2 && (str[0] == 'P' || str[0] == 'p'))
            {
                break;
            }
        }
	
	

        insert(arr);
	system("clear");
        display(arr);
	char x;
	printf("\n			 To exit please press 'X'\n");
	printf("			 To continue press ENTER key!\n			 ");
	scanf("%c",&x);
	if (x=='x' || x=='X')
	{
		printf("\n\n			 Program is terminating!!!\n\n");
		printf("\n\n			 Program is terminated!!!\n\n");
		exit(0);
	}
    }


// =========================VALIDATOR================================

// ====== Create the parameter for the columns and rows check =======
    parameters * param0 = (parameters *) malloc(sizeof(parameters));
    param0->row = 0;
    param0->col = 0;
    param0->arr = arr;
    
    // ====== Create the parameters for the 3x3 threads ======
    
    // First 3x3
    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1->row = 0;
    param1->col = 0;
    param1->arr = arr;
    
    // Second 3x3
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2->row = 0;
    param2->col = 3;
    param2->arr = arr;
    
    // Third 3x3
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3->row = 0;
    param3->col = 6;
    param3->arr = arr;
    
    // Fourth 3x3
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4->row = 3;
    param4->col = 0;
    param4->arr = arr;
    
    // Fifth 3x3
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5->row = 3;
    param5->col = 3;
    param5->arr = arr;
    
    // Sixth 3x3
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6->row = 3;
    param6->col = 6;
    param6->arr = arr;
    
    // Seventh 3x3
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7->row = 6;
    param7->col = 0;
    param7->arr = arr;
    
    // Eighth 3x3
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->row = 6;
    param8->col = 3;
    param8->arr = arr;
    
    // Ninth 3x3
    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->row = 6;
    param9->col = 6;
    param9->arr = arr;
    
    // ====== Create the threads ======
    pthread_t thread_rows, thread_cols, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
    
    // ====== Create the return values for the threads ======
    void * all_rows;
    void * all_cols;
    void * square1;
    void * square2;
    void * square3;
    void * square4;
    void * square5;
    void * square6;
    void * square7;
    void * square8;
    void * square9;
    
    // ====== Initialize the threads ======
    pthread_create(&thread_rows, NULL, walk_rows, (void *) param0);
    pthread_create(&thread_cols, NULL, walk_cols, (void *) param0);
    pthread_create(&thread1, NULL, check_square, (void *) param1);
    pthread_create(&thread2, NULL, check_square, (void *) param2);
    pthread_create(&thread3, NULL, check_square, (void *) param3);
    pthread_create(&thread4, NULL, check_square, (void *) param4);
    pthread_create(&thread5, NULL, check_square, (void *) param5);
    pthread_create(&thread6, NULL, check_square, (void *) param6);
    pthread_create(&thread7, NULL, check_square, (void *) param7);
    pthread_create(&thread8, NULL, check_square, (void *) param8);
    pthread_create(&thread9, NULL, check_square, (void *) param9);

    // ======= Wait for all threads to finish their tasks =======
    pthread_join(thread_rows, &all_rows);
    pthread_join(thread_cols, &all_cols);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);
    
    // ====== Check whether the Sudoku Puzzle was solved ======
    if (    (int) all_rows == 1 &&
            (int) all_cols == 1 &&
            (int) square1 == 1 &&
            (int) square2 == 1 &&
            (int) square3 == 1 &&
            (int) square4 == 1 &&
            (int) square5 == 1 &&
            (int) square6 == 1 &&
            (int) square7 == 1 &&
            (int) square8 == 1 &&
            (int) square9 == 1 ) {
        printf("\n			 Well done! Your solution is correct!\n");
    }
    else {
        printf("\n			 Nice try! But unfortunately your solution is not correct!\n");
    }
    
    printf("\n");
    return 0;
}




/**
 * Checks each row if it contains all digits 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * walk_rows(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    for (int i = startRow; i < 9; ++i) {
        int row[10] = {0};
        for (int j = startCol; j < 9; ++j) {
            int val = data->arr[i][j];
            if (row[val] != 0) {
                return (void *) 0;
            }
            else{
                row[val] = 1;
            }
        }
    }
    return (void *) 1;
}

/**
 * Checks each column if it contains all digits 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * walk_cols(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    for (int i = startCol; i < 9; ++i) {
        int col[10] = {0};
        for (int j = startRow; j < 9; ++j) {
            int val = data->arr[j][i];
            if (col[val] != 0) {
                return (void *) 0;
            }
            else{
                col[val] = 1;
            }
        }
    }
    return (void *) 1;
}

/**
 * Checks if a square of size 3x3 contains all numbers from 1-9.
 * @param   void *      The parameters (pointer).
 * @return  void *      1 if all rows contain all digits from 1-9, 0 otherwise.
 */
void * check_square(void * params) {
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    int saved[10] = {0};
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            int val = data->arr[i][j];
            if (saved[val] != 0) {
                return (void *) 0;
            }
            else{
                saved[val] = 1;
            }
        }
    }
    return (void *) 1;
}