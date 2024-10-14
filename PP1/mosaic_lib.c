// header files
#include "mosaic_lib.h"

/**
 * Task 1: Reordering the Mosaic Tiles
 * Input argument: the mural as a 2D array of integer
 * Output argument: the tranposed mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void transpose(int matrix[SIZE][SIZE])
{
    // Iterate through rows
    for (int i = 0; i < SIZE; i++)
    {
        // Iterate through columns, stopping at the row count to ensure
        //double transposition does not occur
        for (int j = 0; j < i; j++)
        {
            // Switch the integers across diagonal reflection line
            //i.e. switch matrix[i][j] and matrix[j][i]
            matrix[i][j] = matrix[i][j] + matrix[j][i];
            matrix[j][i] = matrix[i][j] - matrix[j][i];
            matrix[i][j] = matrix[i][j] - matrix[j][i];
        }
    }
}

/**
 * Task 2: Realigning the Rotated Tiles
 * Input argument: the mural as a 2D array of integer
 * Output argument: the rotated mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void rotate(int matrix[SIZE][SIZE])
{
    // Iterate through rows
    for (int i = 0; i < SIZE; i++)
    {
        // Iterate through columns, stopping at the row count to ensure
        //double transposition does not occur
        for (int j = 0; j < i; j++)
        {
            // Switch the integers across diagonal reflection line
            //i.e. switch matrix[i][j] and matrix[j][i]
            matrix[i][j] = matrix[i][j] + matrix[j][i];
            matrix[j][i] = matrix[i][j] - matrix[j][i];
            matrix[i][j] = matrix[i][j] - matrix[j][i];
        }
    }
    
    // Iterate through rows
    for (int i = 0; i < SIZE; i++)
    {
        // Iterate through columns, stopping halfway to reflect
        //across vertically.
        for (int j = 0; j < SIZE / 2; j++)
        {
            // Switch the integers across a halfway vertical line.
            //i.e. switch matrix[i][j] and matrix[i][SIZE - j - 1]
            matrix[i][j] = matrix[i][j] + matrix[i][SIZE - j - 1];
            matrix[i][SIZE - j - 1] = matrix[i][j] - matrix[i][SIZE - j - 1];
            matrix[i][j] = matrix[i][j] - matrix[i][SIZE - j - 1];
        }
    }
}

/**
 * Task 3: Restoring the Blank Spaces
 * Input argument: the mural as a 2D array of integer
 * Output argument: the restored mural as a 2D array of integer
 * Return: none
 * Dependencies: none
 */
void zeroMatrix(int matrix[SIZE][SIZE])
{
    // Iterate through all rows
    for (int i = 0; i < SIZE; i++)
    {
        // Iterate through all columns
        for (int j = 0; j < SIZE; j++)
        {
            // Check if current integer is equal to 0.
            if (matrix[i][j] == 0)
            {
                // If so, iterate through k rows
                for (int k = 0; k < SIZE; k++)
                {
                    // Also iterate through l columns
                    for(int l = 0; l < SIZE; l++)
                    {
                        // Replace all integers in the same row as the 0
                        //with -1. This is a placeholder to be set to 0 later
                        matrix[i][l] = -1;
                    }
                    // Replace all integers in the same column as the 0
                    //with -1. This is a placeholder to be set to 0 later
                    matrix[k][j] = -1;
                }
            }
        }
    }
    
    // Iterate through all rows
    for (int i = 0; i < SIZE; i++)
    {
        // Iterate through all columns
        for (int j = 0; j < SIZE; j++)
        {
            // Check for earlier set placeholders
            if (matrix[i][j] == -1)
            {
                // Replace with 0
                matrix[i][j] = 0;
            }
        }
    }
}

/**
 * Task 4: Rotating the Mosaic Row
 * Input argument: the mural as a 2D array of integer, k number of steps
 * Output argument: the mural with a rotated row as a 2D array of integer
 * Return: none
 * Dependencies: stdlib.h - rand
 */
void rotateRow(int matrix[SIZE][SIZE], int k)
{
    // Assign a random integer between 0 and 5 to randRow.
    ////////////////////////////////////////////////////////////////
    // THIS MUST BE DONE IN MEMORY! Unexpected behavior occurs when
    // generating new random values while switching in the for loop.
    ////////////////////////////////////////////////////////////////
    //     func: rand()
    int randRow = rand() % SIZE;
    
    // Iterate through rotations.
    for (int i = 0; i < k; i++)
    {
        // Decrement downwards through the length of the array.
        // (Decrementing is important to a right rotation)
        for (int j = SIZE - 1; j > 0; j--)
        {
            // Switch current integer with the integer to its left.
            // If it's the leftmost integer, the rightmost will switch.
            // i.e. switch matrix[randRow][j] and matrix[randRow][j - 1]
            matrix[randRow][j - 1] += + matrix[randRow][j];
            matrix[randRow][j] = matrix[randRow][j - 1] - matrix[randRow][j];
            matrix[randRow][j - 1] -= matrix[randRow][j];
        }
    }
}

/**
 * Task 5: Unveiling the Spiral Mural
 * Input argument: the mural as a 2D array of integer
 * Output argument: none
 * Return: dynamically allocated array of integers
 * Dependencies: none
 */
int* spiralOrder(int matrix[SIZE][SIZE])
{
    // Allocate memory for return value.
    // This must be done in local scope.
    //    func: malloc()
    int* spiral = malloc(SIZE * SIZE * sizeof(int));

    // Assign 0 values to "k" and "l"
    // Assign 0 values to "top" and "left
    int top = 0;
    int left = 0;
    
    // Assign length values to "m" and "n"
    // Assign length values to "bottom" and "right
    int bottom = SIZE;
    int right = SIZE;
    
    // Assign 0 to "counter" value. This will track where the integers
    //will be placed in the return array, and will increment as integers
    //are addded.
    int counter = 0;

    // Iterate through all integers in the matrix
    while (top < bottom && left < right)
    {
        // Iterate through the next outermost part of the matrix
        //from the top left, going to the right.
        for (int i = left; i < right; i++)
        {
            spiral[counter] = matrix[top][i];
            counter++;
        }
        // Increment top value until it meets bottom value.
        top++;
        
        // Iterate through the next outermost part of the matrix from the
        //top right, going down.
        for (int i = top; i < bottom; i++)
        {
            spiral[counter] = matrix[i][right - 1];
            counter++;
        }
        // Decrement right value until it meets left value.
        right--;
        
        // If an untracked bottom row exists, execute this code block.
        if (top < bottom)
        {
            // Iterate through the next outermost part of the matrix from the
            //bottom right to left.
            for (int i = right - 1; i >= left; i--)
            {
                spiral[counter] = matrix[bottom - 1][i];
                counter++;
            }
            // Decrement bottom value until it meets top value.
            bottom--;
        }

        // If an untracked left column exists, execute this code block.
        if (left < right)
        {
            // Iterate through the next outermost part of the matrix
            //from the bottom left to the top left.
            for (int i = bottom - 1; i >= top; i--)
            {
                spiral[counter] = matrix[i][left];
                counter++;
            }
            // Incremenet left value until it meets right value.
            left++;
        }
    }

    // Return array of matrix integers, ordered in a spiral going clockwise
    //from the top left.
    return spiral;
}

/**
 * Function: printMatrix (provided)
 * Input argument: the mural as a constant 2D array of integer
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void printMatrix(const int matrix[SIZE][SIZE])
{
    // traverse the mural rows
    for (int i = 0; i < SIZE; i++)
    {
        // traverse the mural columns
        for (int j = 0; j < SIZE; j++)
        {
            // print the current row-column value
            printf("%3d ", matrix[i][j]);
        }
        // break a line at the end of the row
        printf("\n");
    }
}