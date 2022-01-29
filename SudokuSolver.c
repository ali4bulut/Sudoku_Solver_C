#include "stdlib.h"
#include "stdio.h"

static int memCount = 0;
static int recursionCnt = 0;

int EmptyPlace(int *arr);
int isValid(int *arr, int index, int number);
int solve(int *arr, int *mem);
void undoImpl(int *arr, int *mem);
void impl(int *arr, int *mem, int index, int number);
void printTable(int *arr);

void printTable(int *arr)
{
    printf("___________SUDOKU SOLVER___________\n");
    for (int i = 0; i < 81; i++)
    {
        if (i != 0 && i % 9 == 0)
            printf("\n");
        printf(" %d ", *(arr + i));
    }
    printf("\n");
    printf("___________SUDOKU SOLVER___________\n");
}

int EmptyPlace(int *arr)
{
    for (int i = 0; i < 81; i++)
    {
        if (*(arr + i) == 0)
        {
            return i;
            // return (arr + i);
        }
    }
    return -1;
}

int isValid(int *arr, int index, int number)
{
    int rawNumber = 9 * (index / 9);
    for (int i = rawNumber; i < rawNumber + 8; i++)
    {
        if (*(arr + i) == number)
        {
            return 0;
        }
    }
    int colNumber = (index - rawNumber) < 0 ? (index - rawNumber) * (-1) : (index - rawNumber);
    for (int i = 0; i <= 72; i += 9)
    {
        if (*(arr + colNumber + i) == number)
        {
            return 0;
        }
    }
    int rowCube = ((rawNumber / 9) / 3);
    int colCube = (colNumber / 3);
    int CubeIndex = (3 * (((rowCube * 3) * 3) + colCube));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (*(arr + (CubeIndex + (i * 9)) + j) == number)
            {
                return 0;
            }
        }
    }

    return 1;
}

int solve(int *arr, int *mem)
{

    int emptyIndex = EmptyPlace(arr);
    if (emptyIndex == -1)
        return 1;

    for (int i = 1; i < 10; i++)
    {
        if (isValid(arr, emptyIndex, i))
        {
            //Without implementation
            // *(arr + emptyIndex) = i;
            // //impl(arr, mem, emptyIndex, i);

            //With implementation
            //*(arr + emptyIndex) = i;
            impl(arr, mem, emptyIndex, i);

            if (solve(arr, mem))
            {
                return 1;
            }

            recursionCnt++;
            *(arr + emptyIndex) = 0;
            //With implementation
            undoImpl(arr, mem);
        }
    }
    return 0;
}

void impl(int *arr, int *mem, int index, int number)
{
    int validCnt = 0;
    int onlyValue = 0;

    *(arr + index) = number;

    int emptyIndex = EmptyPlace(arr);
    if (emptyIndex != -1)
    {
        for (int k = 0; k < 9; k++)
        {
            for (int i = 0; i < 81; i++)
            {
                if (*(arr + i) == 0)
                {

                    for (int j = 1; j < 10; j++)
                    {

                        if (isValid(arr, i, j))
                        {
                            validCnt++;
                            onlyValue = j;
                        }
                    }
                    if (validCnt == 1)
                    {
                        // printf("i = %d and Possible : %d and Value: %d\n", i, validCnt, onlyValue);
                        *(mem + memCount++) = i;
                        *(arr + i) = onlyValue;
                    }
                    validCnt = 0;
                    onlyValue = 0;
                }
            }
            // printf("__________________________________\n");
        }
    }
}

void undoImpl(int *arr, int *mem)
{
    for (int i = 0; i < 81; i++)
    {
        if (*(mem + i) != 0)
        {
            *(arr + *(mem + i)) = 0;
            *(mem + i) = 0;
        }
    }
    memCount = 0;
}

int main(void)
{
    int mem[81] = {0};
    int sud[9][9] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                     {6, 0, 0, 1, 9, 5, 0, 0, 0},
                     {0, 9, 8, 0, 0, 0, 0, 6, 0},
                     {8, 0, 0, 0, 6, 0, 0, 0, 3},
                     {4, 0, 0, 8, 0, 3, 0, 0, 1},
                     {7, 0, 0, 0, 2, 0, 0, 0, 6},
                     {0, 6, 0, 0, 0, 0, 2, 8, 0},
                     {0, 0, 0, 4, 1, 9, 0, 0, 5},
                     {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    int sud2[9][9] = {{0, 0, 0, 8, 0, 0, 4, 2, 0},
                    {5, 0, 0, 6, 7, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 9, 0, 0, 5},
                    {7, 4, 0, 1, 0, 0, 0, 0, 0},
                    {0, 0, 9, 0, 3, 0, 7, 0, 0},
                    {0, 0, 0, 0, 0, 7, 0, 4, 8},
                    {8, 0, 0, 4, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 9, 8, 0, 0, 3},
                    {0, 9, 5, 0, 0, 3, 0, 0, 0}};

    printTable(&sud2[0][0]);

    // int temp = EmptyPlace(&sud[0][0]);
    // int valid = isValid(&sud[0][0], 34, 2);
    // printf("valid : %d\n", valid);

    solve(&sud2[0][0], mem);

    printTable(&sud2[0][0]);
    printf("Recursion Count: %d", recursionCnt);

    // impl(&sud[0][0], mem, 2, 4);
    // printTable(&sud[0][0]);

    // printf("{ ");
    // for (int i = 0; i < 81; i++)
    // {
    //     printf(" %d ", mem[i]);
    // }
    // printf("}\n");

    // undoImpl(&sud[0][0], mem);
    // printTable(&sud[0][0]);
    // printf("{ ");
    // for (int i = 0; i < 81; i++)
    // {
    //     printf(" %d ", mem[i]);
    // }
    // printf("}\n");

    return 0;
}

//  5  3  4  6  7  8  9  1  2
//  6  7  2  1  9  5  3  4  8
//  1  9  8  3  4  2  5  6  7
//  8  5  9  7  6  1  4  2  3
//  4  2  6  8  5  3  7  9  1
//  7  1  3  9  2  4  8  5  6
//  9  6  1  5  3  7  2  8  4
//  2  8  7  4  1  9  6  3  5
//  3  4  5  2  8  6  1  7  9