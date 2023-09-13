/******
 * Name : Pratik Basyal
 * UNM ID : 101952100
 * CS 241
 ******/ 

#include <stdio.h>
#include <string.h>
#include <ctype.h>


int solveSudoku(char board[9][9]);

int inRow(int row, char board[9][9], int num);

int inColumn(int row, char board[9][9], int num);

int inBox(int row, int column, char board[9][9], int num);

int printBoard(char board[9][9]);

int printInput(char input[100]);

int isValidBoard(char board[9][9]);

int repeat_num_inRow(int row, char board[9][9], int num);

int repeat_num_inColumn(int column, char board[9][9], int num);

int repeat_num_inBox(int row, int column, char board[9][9], int number);


/******
 * Defining isValid function to verify given input only contains integer from 1 to 9 and '.' character
 ******/    

int isValidInput(char input[100])
{
    int i;
    if(strlen(input) != 82)
    {
        return 0;
    }
    for (i = 0; i < strlen(input) - 1; i++) 
    {
        if (!isdigit(input[i]) &&  input[i] != '.') 
        {
            return 0;
        }
    }
    return 1;
}

/******
 * Here in our main function, we print and solve the sudoku board after validating the given input from different function
 * basically we are doing everything here
 ******/    
int main()
{
    
    int i, j, k;
    char input[100];
    char board[9][9];

    while (fgets(input, sizeof(input), stdin))
    {
        /**
         * checking if the input is valid or not
        */
        if(!isValidInput(input))
        {
            printInput(input);
            printf("Error\n\n");
            continue;
        }
    
        else
        {
            i = 0;
            for(j = 0; j < 9; j++)
            {
                for(k = 0; k < 9; k++)
                {
                        board[j][k] = input[i];
                        printf("%c", board[j][k]);
                        i++;
                }
            }
            if(!isValidBoard(board))
            {
                printf("\nError\n\n");
                continue;
            }
        }
            printf("\n");
            if(!solveSudoku(board))
            {
               printf("No solution\n\n");
               continue;
            }
            else{
                printBoard(board);
                printf("\n");
            }
    }
    return 0;
}

/******
 * this is just a function to print the given input
 * I used this so that my main function doesn't look too messy.
 ******/ 
int printInput(char input[100])
{
    int i;
    for(i = 0; i < strlen(input); i++)
    {
        printf("%c", input[i]);
    }
    return 0;
}

/******
 * This is also just a basic function to print board
 * Used it for the same purpose lol
 ******/ 
int printBoard(char board[9][9])
{
    int row, column;
    for(row = 0; row < 9; row++)
    {
        for(column = 0; column < 9; column++)
        {
            printf("%c", board[row][column]);
        }
    }
    printf("\n");
    return 0;
}

/******
 * This function checks if the number we are supposed to put is already present in row or not
 ******/ 
int inRow(int row, char board[9][9], int num)
{
    int i;
    for(i = 0; i < 9; i++)
    {
        if(board[row][i] == num)
        {
            return 1;
        }
    }
        return 0;
}

/******
 * Similarly this function also checks if the number we are supposed to put is already present in column or not
 ******/ 
int inColumn(int column, char board[9][9], int num)
{
    int i;
    for(i = 0; i < 9; i++)
    {
        if(board[i][column] == num)
        {
            return 1;
        }
    }
    return 0;
}

/******
 * And this function checks if the number we are supposed to put is already present in 3x3 box or not
 ******/ 
int inBox(int row, int column, char board[9][9], int number)
{
    int i, j;
    /**
     * setting range for row and column to keep track of the right box
    */
    int temp_row = row - row % 3;
    int temp_column = column - column % 3;

  for(i = temp_row; i < temp_row + 3; i++)
  {
    for(j = temp_column; j < temp_column + 3; j++)
    {
        if(board[i][j] == number)
        {
            return 1;
        }
    }
  }
    return 0;
}

/******
 * This function checks if the number we are placing is at right place by checking all three above conditions
 ******/ 
int isValidPlacement(int row, int column, char board[9][9], int number)
{
    if(!inRow(row, board, number) && !inColumn(column, board, number) && !inBox(row, column, board, number))
    {
        return 1;
    }
    return 0;
}

/******
 * This function is basically our most vital function.
 * This will check if we are placing the number in right place with reference from above "isValidPlacement" function.
 * After that I used recursion method, so everytime we place the number, it calls the function and go through the same process again.
 * And if it reaches at a point where it solves puzzle then it will return true, and if not :
 * then it will set back the previous position to '.' again and repeat the process by inputing number again.
 * And finally if its not solvable after going through all of this, function will return false.
 ******/ 
int solveSudoku(char board[9][9])
{
    int row, column;
    char num_to_try;

   for(row = 0; row < 9; row++)
   {
      for(column = 0; column < 9; column++)
      {
          if(board[row][column] == '.')
          {
            for(num_to_try = '1'; num_to_try <= '9'; num_to_try++)
            {
               if(isValidPlacement(row, column, board, num_to_try))
               {
                   board[row][column] = num_to_try;

                   if(solveSudoku(board))
                   {
                    return 1;
                   }
                   else
                   {
                    board[row][column] = '.';
                   }
                }
            }
           return 0;
          }
      }
   }
   return 1;
}

/******
 * This function checks if the sudoku board we made from the given input is valid or not, (after we check if the input has correct characters)
 * It checks if the number are repeated more than once in row, column and box.
 * If thats the case then it will return false or it will return true
 ******/ 
int isValidBoard(char board[9][9])
{
    int row, column, num;
    for(row = 0; row < 9; row++)
    {
        for(column = 0; column < 9; column++)
        {
            if(board[row][column] == '.')
            {
                continue;
            }
            if(board[row][column] != '.')
            {
                num = board[row][column];
            }
            if(repeat_num_inRow(row, board, num) > 1)
            {
                return 0;
            }
            if(repeat_num_inColumn(row, board, num) > 1)
            {
                return 0;
            }
            if(repeat_num_inBox(row, column, board, num) > 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

/******
 * So This function keeps track of how many times the numbers are repeated in ROW.
 ******/ 
int repeat_num_inRow(int row, char board[9][9], int num)
{
    int i;
    int count = 0;
    for(i = 0; i < 9; i++)
    {
        if(board[row][i] == num)
        {
            count++;
        }
    }
        return count;
}

/******
 * This function keeps track of how many times the numbers are repeated in COLUMN.
 ******/ 
int repeat_num_inColumn(int column, char board[9][9], int num)
{
    int i;
    int count = 0;
    for(i = 0; i < 9; i++)
    {
        if(board[i][column] == num)
        {
            count++;
        }
    }
    return count;
}

/******
 * This function keeps track of how many times the numbers are repeated in 3x3 BOX.
 ******/ 
int repeat_num_inBox(int row, int column, char board[9][9], int number)
{
    int i, j;
    int count = 0;
    int temp_row = row - row % 3;
    int temp_column = column - column % 3;

    for(i = temp_row; i < temp_row + 3; i++)
    {
        for(j = temp_column; j < temp_column + 3; j++)
        {
            if(board[i][j] == number)
            {
            count++;
            }
        }
    }
    return count;
}

