// header files
#include "leaderboard_lib.h"

// main program
int main() 
{
    // pointer to the root of the leaderboard tree
    TreeNode *leaderboard; 

    // variables for menu selection and input data
    int option = 0, score, k, low, high, student1, student2; 

    // Task 1: initialize the leaderboard as an empty tree
    createLeaderboard(&leaderboard);

    while (option != 9) 
    {
        // display menu options
        printf("\n---- Leaderboard Menu ----\n");
        printf("1. Add a student score\n");
        printf("2. Remove a student score\n");
        printf("3. Print leaderboard\n"); 
        printf("4. Find the Kth smallest score\n");
        printf("5. Calculate range sum of scores\n"); 
        printf("6. Find common friend student\n");
        printf("7. Measure academic connectivity\n");
        printf("8. Identify Students Meeting Average Performance\n");
        printf("9. Exit\n"); 
        printf("Choose an option (1-10): "); 

        // read the option
        scanf("%d", &option); 
        // choose the case
        switch (option) 
        {
            // Task 2: add a student score
            case 1: 
                // prompt for the score
                printf("Enter student score to add: ");
                // read the score
                scanf("%d", &score);
                // add the score to leaderboard
                leaderboard = addStudent(leaderboard, score); 
                // confirm the added score
                printf("Score %d added to leaderboard.\n", score); 
                // end case
                break;
            // Task 3: Remove a student score
            case 2: 
                // prompt for score to remove
                printf("Enter student score to remove: "); 
                // read the score
                scanf("%d", &score); 
                // remove score from leaderboard
                leaderboard = removeStudent(leaderboard, score);
                // print a message
                printf("Score %d removed from leaderboard.\n", score); 
                // exit case
                break;
            // Task 4: Print leaderboard
            case 3:
                // print header for leaderboard
                printf("Current Leaderboard:\n"); 
                // print scores in leaderboard
                printLeaderboard(leaderboard);
                // cosmetics
                printf("\n");
                // exit case 
                break; 
            // Task 5: Find the Kth smallest score
            case 4:
                // prompt for K value
                printf("Enter the value of K: ");
                // read k value
                scanf("%d", &k); 
                // find the Kth smallest score
                int kthScore = findKthSmallestScore(leaderboard, k);
                // if valid Kth score found
                if (kthScore != -1) 
                {
                    // print Kth score
                    printf("The %dth smallest score is: %d\n", k, kthScore); 
                }
                // otherwise
                else 
                {
                    // error message for invalid K
                    printf("Invalid K value or leaderboard is empty.\n"); 
                }
                // exit case
                break;
            // Task 6: Calculate range sum of scores
            case 5:
                // prompt for lower bound of range
                printf("Enter low range: ");
                // read the low bound
                scanf("%d", &low);
                // prompt for upper bound of range
                printf("Enter high range: ");
                // read upper bound
                scanf("%d", &high);
                // calculate sum of scores in range
                int rangeSum = rangeSumScores(leaderboard, low, high);
                // print range sum
                printf("The sum of scores between %d and %d is: %d\n", 
                    low, high, rangeSum);
                // exit case
                break;
            // Task 7: Find common friend student
            case 6:
                // prompt for first score
                printf("Enter the first student score: ");
                // read the score for student 1
                scanf("%d", &student1);
                // Prompt for second score
                printf("Enter the second student score: ");
                // read the score for student 2
                scanf("%d", &student2);
                // find common friend
                int commonFriend = findCommonFriend(
                    leaderboard, student1, student2);
                // if common friend exists
                if (commonFriend != -1) 
                { 
                    // print common friend score
                    printf(
                        "The common friend student score between %d and %d is:" "%d\n", student1, student2, commonFriend); 
                }
                // otherwise
                else 
                {
                    // error if no common friend
                    printf("No common friend found or scores do not exist.\n"); 
                }
                // exit this case
                break;
            // Task 8: Measure academic connectivity
            case 7:
            {
                // find longest path between two nodes
                int academicConnectivity =
                    measureConnectivity(leaderboard);
                // print connectivity path length
                printf(
                    "The length of the longest path between students is: %d\n",
                    academicConnectivity);
                // exit case
                break; 
            }
            // Task 9: Identify Students Meeting Average Performance
            case 8:
            {
                // calculate the average performance
                int averageCount = averagePerformance(leaderboard);
                // print the message
                printf("Number of students meeting average performance: %d\n", 
                    averageCount);
                // end case
                break;
            }
            // exit case
            case 9:
                // print exit message
                printf("Exiting program. Goodbye!\n");
                // end case
                break;
            // default case
            default:
                // handle invalid options
                printf("Invalid option. Please choose again.\n");
                // end case
                break;
        }
    }
}
