// header files
#include "chronos_lib.h"

/**
 * Task 1: Uncovering the Unique Code
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the unique integer that appears only once in the array
 * Dependencies: none
 */
int unique_code(int array[], int size)
{
    // Iterate through the length of the array
    for (int i = 0; i < size; i++)
    {
        // Initialize check as true
        bool check = true;
        // Initialize through the length of array again to check
        //for a repeat element
        for (int j = 0; j < size; j++)
        {    
            //We must count out i == j to avoid counting the
            //same element as a repeat.
            if (i != j)
            {    
                // If a repeat element is found, then this traversal
                //is false.
                if ((array[i] == array[j]))
                {
                    // Set check to false
                    check = false;
                }
            }
            // If we are on the last case and check is still true,
            //we found an element without a repeat.
            if (check && j + 1 == size)
            {
                // Return the unique element
                return array[i];
            }
        }
    }
    // We checked all possible cases and didn't find a unique element.
    return NOT_FOUND;
}


/**
 * Task 2: Balancing the Array
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the index where the sum of elements on the left equals the sum
 *      on the right
 * Dependencies: none
 */
int balance(int array[], int size)
{
    // Initialize left and right placeholders with 0
    int left = 0;
    int right = 0;
    // Iterate through the length of the array, i will keep track
    //of balance point
    for (int i = 0; i < size; i++)
    {
        // Initialize again with 0
        left = 0;
        right = 0;
        // Iterate from i going forwards. This will track the right sum
        for (int j = i; j < size; j++)
        {
            // Add to right until end of array is found.
            right += array[j];
        }
        // Iterate from i going backwards. This will track the left sum.
        for (int j = i; j >= 0; j--)
        {
            // Add to left until start of array is found.
            left += array[j];
        }
        // After both for loops, we should have both left/right sums.
        if (left == right)
        {
            // If they match, then we found a balance point.
            // Return the index of the balance point found
            return i;
        }
    }
    // We have checked all possible cases, and a balance point
    //wasn't found
    return NOT_FOUND;
}


/**
 * Task 3: Decoding the Scrambled Message
 * Input argument: scrambled_message as a string, reference_message as a
 *      string
 * Output argument: none
 * Return: boolean value indicating if the messages are anagrams
 * Dependencies: none
 */
bool decode(const char *scrambled_message, const char *reference_message)
{
    // Create array copies, keep null in copy
        //func: strlen()
    char scrambled[strlen(scrambled_message) + 1];
    char reference[strlen(reference_message) + 1];
    
    // Copy arrays over
        //func: strcpy()
    strcpy(scrambled, scrambled_message);
    strcpy(reference, reference_message);
    
    // It's impossible for two messages to be anagrams if they aren't
    //the same length. Check case to avoid traversing incorrect array
    //size.
    if (strlen(scrambled_message) != strlen(reference_message))
    {
        // Strings aren't the same length, so it is impossible for
        //them to be anagrams
        return false;
    }
    
    // Iterate through the length of scrambled array
    for(int i = 0; i < strlen(scrambled_message); i++)
    {
        // Iterate through the length of reference array
        for(int j = 0; j < strlen(scrambled_message); j++)
        {
            // If an identical char was found somewhere in both arrays,
            //replace that char with a placeholder value
            if (scrambled[i] == reference[j])
            {
                scrambled[i] = '_';
                reference[j] = '_';
            }
        }
    }
    // Iterate through length of both arrays
    for(int i = 0; i < strlen(scrambled_message); i++)
    {
        // If the strings are anagrams, both strings will match now that
        //placeholders are placed.
        if (scrambled[i] != reference[i])
        {
            // Return false because a mismatch was found
            return false;
        }
    }
    
    // Return true because no mismatches were found, meaning
    //that the strings are anagrams.
    return true;
}

/**
 * Task 4: Uncovering the Maximum Sequence
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the maximum sum of a contiguous subarray
 * Dependencies: none
 */
int uncover(int array[], int size)
{
    // Set max to lowest possible value
    int max = 0;
    
    // Iterate through our array
    for (int i = 0; i < size; i++)
    {
        // Set tempsum to 0 for new traversal.
        int tempsum = 0;
        // Each array we check will move its starting index up from the OG
        //array by one. We do this with j = i.
        for (int j = i; j < size; j++)
        {
            // Add tempsum and array[j]. This will repeat.
            tempsum = tempsum + array[j];
            // Check if current tempsum is greater than max. If so,
            //this is a new max.
            if (tempsum > max)
            {
                max = tempsum;
            }
        }
    }
    // We should have the highest possible cont. subarray sum.
    return max;
}


/**
 * Task 5: Navigating the Rotated Array
 * Input argument: array as a 1D array of integers, size as an integer,
 *     data_element as an integer
 * Output argument: none
 * Return: the index of the data_element in the rotated sorted array
 * Dependencies: none
 */
int navigate(int array[], int size, int data_element)
{
    // Start index is first array index [0]
    int start = 0;
    // End is last [size - 1]
    int end = size - 1;
    // As soon as the start index moves past the end point, we are out
    //of scope, and the data element won't be able to be found.
    while (start <= end)
    {
        // Standard binary search method: move the middle to either
        //left or right depending on below conditions
        int middle = start + (end - start) / 2;
        
        // If our current middle is the data_element (goal)
        //then return the found element
        if (array[middle] == data_element)
        {
            // Return our found element
            return middle;
        }
        
        // We have a subgoal of finding which side could be closer
        // to array[middle]. Starting with if our start value is less
        // than/equal to middle value.
        // Current left half is sorted
        if(array[start] <= array[middle])
        {
            // Since start value is less than middle, it could be less
            //than the element we're trying to find.
            if(array[start] <= data_element && data_element < array[middle])
            {
            // Move end accordingly, which will move middle closer when
            //loop repeats
            end = middle - 1;
            }
            // If not, this block will pass
            else
            {
            // Move end so middle is closer when loop repeats
            start = middle + 1;
            }
        }
        // Now handle cases if start value is bigger than middle value
        // Current right half is sorted.
        else
        {
            // If the end value is higher than data element, move closer
            //to that case
            if (array[end] >= data_element && data_element > array[middle] )
            {
            //Move start accordingly, which will move middle closer when loop
            //repeats
            start = middle + 1;
            }
            // If not, move towards other case
            else
            {
            // Move middle closer
            end = middle - 1;
            }
        }
    }
    // The while loop was escaped, and we checked every possible case.
    //Element we're searching for doesn't exist.
    return NOT_FOUND;
    
}


/**
 * Task 6: Finding the Critical Minimum
 * Input argument: array as a 1D array of integers, size as an integer
 * Output argument: none
 * Return: the minimum value in a rotated sorted array
 * Dependencies: none
 */
int critical_minimum(int array[], int size)
{
    // Start index is first array index [0]
    int start = 0;
    // End is last [size - 1]
    int end = size - 1;
    // Set min to impossibly high placeholder value
    int min = 99999999;
    // As soon as the start index moves past the end point, we are out
    //of scope, and the data element won't be able to be found.
    // Since this is another rotated array searched using Binary method,
    //we use a very similar approach to Task 5
    while (start <= end)
    {
        // Standard binary search method: move the middle to either
        //left or right depending on below conditions
        int middle = start + (end - start) / 2;
        
        // If our current middle is less than current min,
        //then replace with new lowest value.
        if (array[middle] < min)
        {
            // New lowest value
            min = array[middle];
        }
        
        // We have a subgoal of finding which side could be closer
        // to array[middle]. Starting with if our start value is less
        // than/equal to middle value.
        // Current left half is sorted
        if(array[start] <= array[middle])
        {
            // Since start value is less than middle, it could be less
            //than the element we're trying to find.
            if(array[start] <= min && min < array[middle])
            {
            // Move end accordingly, which will move middle closer when
            //loop repeats
            end = middle - 1;
            }
            // If not, this block will pass
            else
            {
            // Move end so middle is closer when loop repeats
            start = middle + 1;
            }
        }
        // Now handle cases if start value is bigger than middle value
        // Current right half is sorted.
        else
        {
            // If the end value is higher than data element, move closer
            //to that case
            if (array[end] >= min && min > array[middle] )
            {
            //Move start accordingly, which will move middle closer when loop
            //repeats
            start = middle + 1;
            }
            // If not, move towards other case
            else
            {
            // Move middle closer
            end = middle - 1;
            }
        }
    }
    // We have checked all possible cases. The minimum we currently
    //hold is the lowest possible value in the array.
    return min;
}
