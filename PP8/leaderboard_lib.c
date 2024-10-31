// header files
#include "leaderboard_lib.h"

/**
* Task 1: Create leaderboard 
* Input argument: root - a pointer to the root of the leaderboard
* Output argument: none
* Return: none
* Dependencies: none
*/



/**
* Task 2: Add a new student 
* Input argument: root - a pointer to the root of the leaderboard
*                 score - the score to add to the leaderboard
* Output argument: none
* Return: a pointer to the root of the leaderboard
* Dependencies: rightRotate, leftRotate, maxHeight, height, getBalance
                addStudent (recursive)
*               stdlib.h - malloc
*/



/**
* Task 3: Remove a student 
* Input argument: root - a pointer to the root of the leaderboard
*                 score - the score to remove from the leaderboard
* Output argument: none
* Return: a pointer to the root of the leaderboard
* Dependencies: rightRotate, leftRotate, maxHeight, height, getBalance
*               removeStudent (recursive)
*/



/**
* Task 4: Print leaderboard 
* Input argument: root - a pointer to the root of the leaderboard
* Output argument: none
* Return: none
* Dependencies: printLeaderboard (recursive)
*               stdio.h - printf
*/



/**
* Function: findKthSmallestScore (provided)
* Input argument: root - a pointer to the root of the leaderboard
*                 k - integer value indicating the order of the smallest 
*                     element to be found
* Output argument: none
* Return: integer value representing the Kth smallest score or -1 if not found
* Dependencies: findKthSmallest
*/
int findKthSmallestScore(TreeNode *root, int k) 
{
    // initialize the count of visited nodes
    int count = 0;
    // initialize result to -1 (indicating not found)       
    int result = -1;
    
    // call the recursive function to perform the in-order traversal
    findKthSmallest(root, k, &count, &result);
    
    // return the Kth smallest score found
    return result;        
}


/**
* Task 5: Find the kth smallest score
* Input argument: root - a pointer to the root of the leaderboard
*                 k - integer value indicating the order of the smallest 
*                     element to be found
*                 count - a pointer to the number of visited nodes
*                 result - a pointer to the integer representing the kth 
*                          smallest score (or -1 if not found)
* Output argument: count and result are updated
* Return: none
* Dependencies: findKthSmallest (recursive)
*/



/**
* Task 6: Calculate the range sum of scores 
* Input argument: root - a pointer to the root of the leaderboard
*                 low, high - integer values to delimit the range
* Output argument: none
* Return: the sum of the scores in the range
* Dependencies: rangeSumScores (recursive)
*/



/**
* Task 7: Find common friend 
* Input argument: root - a pointer to the root of the leaderboard
*                 student1, student2 - integer values with student scores
* Output argument: none
* Return: score of the common friend
* Dependencies: findCommonFriendStudent (recursive)
*/



/**
 * Task 8: Measure Academic Connectivity
 * Input argument: root - a pointer to the root of the leaderboard
 * Output argument: none
 * Return: total academic connectivity as an integer
 * Dependencies: height
 */



/**
 * Function: countSubtree (for Task 9)
 * Input argument: root - a pointer to the root of the leaderboard
 *                 sum - a pointer to the sum of the scores in the subtree
 *                 count - a pointer to the number of nodes in a subtree
 * Output argument: sum and count contains the sum and count values for the 
 *                  given subtree
 * Return: none
 * Dependencies: countSubtree (recursive)
 */



/**
 * Task 9: Identify students meeting average performance
 * Input argument: root - a pointer to the root of the leaderboard
 * Output argument: none
 * Return: number of students meeting the average performance as an integer
 * Dependencies: calculateSubtree
 */



// utility functions to maintain the AVL trees
/**
* Function: height (provided)
* Input argument: node - a pointer to a node in an BST
* Output argument: none
* Return: the height of the node as an integer
* Dependencies: none
*/
int height(TreeNode *node) 
{
    // check if the node is NULL
    if (node == NULL)
    {
        // no height
        return 0;
    }
    // return the height attribute of the current node
    return node->height;
}

/**
* Function: maxHeight
* Input argument: left - the height of the left subtree of a node
*                 right - the height of the right subtree of a node
* Output argument: none
* Return: integer value representing the maximum of left and right values
* Dependencies: none
*/



/**
* Function: getBalance
* Input argument: node - a node in an AVL tree
* Output argument: none
* Return: the difference between the heights of the left and right children
* Dependencies: none
*/



/**
* Function: rightRotate
* Input argument: unbalancedNode - the unbalanced node to rotate in an AVL tree
* Output argument: the height of rotated nodes are updated
* Return: the new root of the rotated subtree
* Dependencies: maxHeight, height
*/



/**
* Function: leftRotate
* Input argument: unbalancedNode - the unbalanced node to rotate in an AVL tree
* Output argument: the height of rotated nodes are updated
* Return: the new root of the rotated subtree
* Dependencies: maxHeight, height
*/
