//Code by Elijah Sprouse
// header files
#include "puzzle_lib.h"  

/**
 * Task 1: Fill the container box
 * Arguments: - the size of the container
 *            - an array of boxes to be placed in the container
 *            - the number of boxes in the array
 *            - the index in the array where the placement should start
 * Return: true if a combination of boxe's sizes is equal to the container size
 *         false otherwise
 * Dependencies: fillContainerBox (recursive)
 */
bool fillContainerBox(
    int containerSize, int* boxSizes, int numBoxes, int index)
{    
    // Base case:
    // If we were able to subtract enough factors from containerSize to
    //equal 0, then that means that those factors could also add up to the
    //containerSize.
    // This means that we found factors that added up to equal containerSize
    if (containerSize == 0)
    {
        // Return true because base case is achieved.
        return true;
    }

    // If we fell below 0, meaning our factors exceeded containerSize,
    //or if the index falls outside of the array, then we weren't able to
    //find factors that added up to the containerSize during this call.
    if(containerSize < 0 || index >= numBoxes)
    {
        // Return false because sum wasn't found in bounds.
        return false;
    }
    
    // Iterate through the boxSizes array
    for (int i = index; i < numBoxes; i++)
    {
        // Check if this statement is true. This will "unravel" the recursive
        //function until true is returned to main.
        if(fillContainerBox(
        containerSize-boxSizes[i], boxSizes, numBoxes, i + 1))
        {
            // Return true to main.
            return true;
        }
        
    }
    
    // Return false if no previous cases have been caught.
    return false;
}

/**
 * Task 2: The labyrinth challenge
 * Arguments: - the maze size
 *            - the maze
 *            - the coordinates (x,y) for the current position in the maze
 *            - the path
 *            - the position to add the value in the path
 *            - the matrix of visited positions
 * Return: none
 * Dependencies: puzzle_lib.h - solveMaze (recursive), isSafe (provided)
 */
void solveMaze(
    int size, int maze[size][size], int x, int y, char *path, int pathIndex,
    bool visited[size][size])
{
    // Baes Case:
    // If we're at the end, the bottom-right position, then terminate our
    //path and print. We have solved the maze.
    if(x == size - 1 && y == size - 1)
    {
        // We have to add null to the end of the string because we are
        //manually modifying it. Otherwise, the string will continue to
        //print garbage until the next null terminator is found in memory
        path[pathIndex] = '\0';
        
        //Print the way to the end of the maze
            //func: printf();
        printf("Path: %s\n", path);
    }
    
    //If the base case wasn't achieved, this will run...
    else
    {
        
    // Set the current spot in the maze as visited, so that we don't end up
    //going back and forth.
    visited[x][y] = true;
    
    // Check if we can go to the right by checking one unit right
    if(isSafe(size, maze, x, y + 1, visited))
    {

        //Add our next traversal to the path traveled.
        path[pathIndex] = 'R';
        // Go right by incrementing y and the pathIndex, then call function.
            //func: solveMaze();
        solveMaze(size, maze, x, y + 1, path, pathIndex + 1, visited);
    }    

    // Check if we can go down by checking the position one unit below us.
    if(isSafe(size, maze, x + 1, y, visited))
    {
        //Add our next traversal to the path traveled.
        path[pathIndex] = 'D';
        // Go down by incrementing x and the pathIndex, then call function.
            //func: solveMaze();
        solveMaze(size, maze, x + 1, y, path, pathIndex + 1, visited);
    }

    
    //Check if we can go to the left by checking one unit left.
    if(isSafe(size, maze, x, y - 1, visited))
    {
        //Add our next traversal to the path traveled.
        path[pathIndex] = 'L';
        // Go left by decremeneting y and the incrementing pathIndex.
        //Call function.
            //func: solveMaze();
        solveMaze(size, maze, x, y - 1, path, pathIndex + 1, visited);
    }
    // Check if we can go up by checking one unit above us.
    if(isSafe(size, maze, x - 1, y, visited))
    {
        // Add our next traversal to the path traveled.
        path[pathIndex] = 'U';
        // Go up by decrementing x and incrementing pathIndex, then call func
            //func: solveMaze();
        solveMaze(size, maze, x - 1, y, path, pathIndex + 1, visited);
    }

    // If no previous cases have been achieved, set current position
    //as not visited as failsafe.
    visited[x][y] = false;
    }
}


/**
 * Function: isSafe (provided)
 * Arguments: - the maze size
 *            - the maze
 *            - the coordinates (x,y) for the current position in the maze
 *            - the matrix of visited positions
 * Return: true if matrix in the given coordinate (x,y) is within bounds,
 *              it is an open path and it is not visited
 *         false otherwise
 * Dependencies: none
 */
bool isSafe(int size, int maze[size][size], int x, int y,
    bool visited[size][size])
{
    // Check if the position provided is not a wall, is in bounds, and hasn'tan
    //been visited before. Return true/false. 
    return (x >= 0
        && x < size
        && y >= 0
        && y < size
        && maze[x][y] == 1
        && (!visited[x][y] || visited == NULL));
}

/**
 * Task 3: The financial puzzle
 * Arguments: - the list of investments
 *            - the number of available options
 *            - the target sum the investments must achieve
 *            - the index for the next considered investment
 *            - the current sum
 *            - the current subset of selected investments
 *            - the index representing the size of the current subset
 * Return: none
 * Dependencies: puzzle_lib.h - findSubsets (recursive)
 */
void findSubsets(
    int investments[], int numInvestments, int target, int index,
    int currentSum, int currentSubset[], int subsetIndex)
{
    // Base case:
    // If our sum matches the target, we can print the factors
    //we used via the currenSubset array and subsetIndex.
    if (currentSum == target)
    {
        
        // Print a curly brace for formatting
            //func: printf();
        printf("{");
        
        // Iterate through the subset Index
        for (int i = 0; i < subsetIndex; i++)
        {
            
            // Print current index in the subset array
                //func: printf();
            printf("%d", currentSubset[i]);
            
            // If the current element isn't the last, print a comma for
            //formatting.
            if(i != subsetIndex - 1)
            {
                // Print a comma for formatting
                    //func: printf();
                printf(", ");
            }
        }
    // Print last curly brace for formatting
        //func: printf();
    printf("}\n");
    }

    // Check if the array hasn't been fully traversed (index < numInvestments)
    // Also if the current sum in this call is less than or equal to
    //target value
    if(index < numInvestments && currentSum <= target)
    {
        // Loop through possible elements for combination, with goal of
        //reaching base case
        for (int i = index; i < numInvestments; i++) {

        // Add current investment element to possible list of factors
        //to sum. This will be printed if it can reach target
        currentSubset[subsetIndex] = investments[i];
        
        // Call function recursively while adding next investment
            // func: findSubsets();
        findSubsets(investments, numInvestments, target, i + 1,
        currentSum + investments[i], currentSubset, subsetIndex + 1);
        }
    }
}