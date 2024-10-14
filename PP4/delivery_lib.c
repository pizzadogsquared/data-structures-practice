// header files
#include "delivery_lib.h"

/**
 * Function: swapOrders (provided)
 * Input argument: two pointer to orders
 * Output argument: swapped orders
 * Return: none
 * Dependencies: none
 */
void swapOrders(Order* leftOrder, Order* rightOrder)
{
    // temporary order receives the left order
    Order temp = *leftOrder;
    // the left order is set to the right order
    *leftOrder = *rightOrder;
    // the right order is set to the temporary variable
    *rightOrder = temp;
}

/**
 * Task 1: Organizing Orders by Category (sortOrders)
 * Input argument: array of orders, an integer value representing the
 * array size
 * Output argument: array of orders sorted by category
 * Return: none
 * Dependencies: swapOrders (provided), stdio.h
 */
void sortOrders(Order orders[], int size)
{
    // Leftmost index for the while loop
    int start = 0;
    
    // Rightmost index for the whileloop
    int end = size - 1;
    
    // Start category checker at 0 (start of enum)
    Category checkCategory = 0;
    
    // Escape the while loop when the start index is past the end index
    while (start <= end)
    {
        // If the current leftmost element is in the right spot,
        // we can move on
        if (orders[start].category == checkCategory)
        {
            // Increment start index.
            start++;
        }
        
        // If the current rightmost element is in the right spot,
        //we can move on
        else if (orders[end].category != checkCategory)
        {
            //Decrement the end index
            end--;
        }
        
        // If neither of the previous cases are true, swap so
        //in future loops they will be skipped over until entire
        //orders[] array is sorted
        else
        {
            //Swap current leftmost and rightmost unsorted elements
            swapOrders(&orders[end], &orders[start]);
            
            //Move indices accordingly
            start++;
            end--;
        }
        
        // If we are out of scope for this category's sorting,
        //we can reset the end and increment the enum
        if(start > end && checkCategory < DESSERTS)
        {
            // Reset the rightmost index
            end = size - 1;
            
            //Increment the category enum to sort the next category
            checkCategory++;
        }
    }
    
}


/**
 * Task 2: Prioritizing High-Priority Deliveries (findKthHighestPriority)
 * Input argument: - array of orders
 *                 - an integer value representing the array size
 *                 - integer value representing k
 * Output argument: none
 * Return: integer value representing the k-th priority or an error code
 * Dependencies: mergesort, stdlib.h
 */
int findKthHighestPriority(const Order orders[], int size, int k)
{
    // Make space for priorities array
    int *priorities = (int*) malloc(size * sizeof(int));
    
    // Iterate through array of structs
    for(int i = 0; i < size; i++)
    {
        // Build new priorities array from array of structs' priorities
        priorities[i] = orders[i].priority;
        
    }
    
    // Sort priorities using mergeSort()
    mergeSort(priorities, 0, size - 1);
    
    // Now that the array is sorted, finding the kth biggest is as
    //simple as counting backwards
    int max = priorities[size - k];
    
    // Free dynamic array to avoid memory leaks
    free(priorities);
    
    // Return our max value
    return max;
}


/**
 * Task 2.1: merge (helper function)
 * Input argument: - array of integers
 *                 - left, middle and right indexes
 * Output argument: sorted array of integers
 * Return: none
 * Dependencies: stdlib.h
 */
void merge(int arr[], int left, int mid, int right)
{
    // We need three indices for merge():
    
    //leftIndex is for the left array:
    int leftIndex = 0;
    //rightIndex is for the right array:
    int rightIndex = 0;
    //arrIndex will track the main array of this call:
    int arrIndex = left;
    
    // leftSize will track the size of the left array:
    int leftSize = mid - left + 1;
    
    // rightSize will track the size of the right array:
    int rightSize = right - mid;
    
    // Dynamically allocate two arrays to split the main array into
    int *leftArray = (int*) malloc(leftSize * sizeof(int));
    int *rightArray = (int*) malloc(rightSize * sizeof(int));
    
    // Copy the split left array to temporary left array
    for (int i = 0; i < leftSize; i++)
    {
        //Assign each element tot he leftArray
        leftArray[i] = arr[left + i];
        
    }
    
    // Copy the split right array to temporary right array
    for(int i = 0; i < rightSize; i++)
    {
        //Assign each element to the rightArray
        rightArray[i] = arr[mid + 1 + i];
        
    }
    
    // This while loop will run as long as either index remains in
    //their array's scope
    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        // If the left element is less than or equal to right,
        //assign it accordingly to main array and increment leftIndex
        if (leftArray[leftIndex] <= rightArray[rightIndex])
        {
            // Merge the lower value (the one in the left array) to
            //the main array
            arr[arrIndex] = leftArray[leftIndex];
            //Increment the leftIndex
            leftIndex++;
        }
        //If previous case is false, this will run
        //i.e., if left element is greater than right:
        else
        {
            // Merge the lower value (the one in the right array) to
            //the main array
            arr[arrIndex] = rightArray[rightIndex];
            //Increment the rightIndex
            rightIndex++;
            
        }
        
        // An assignment occurred, so to avoid overwriting, we must
        //increment arrIndex
        arrIndex++;
    }
    
    // There could be elements left in leftArray
    while (leftIndex < leftSize)
    {
        //If so, assign them to next place in main array
        arr[arrIndex] = leftArray[leftIndex];
        //Increment leftIndex to catch any other bigger elements
        leftIndex++;
        //Increment main index to avoid overwriting
        arrIndex++;
    }
    
    // There could also be elements left in rightArray
    while (rightIndex < rightSize)
    {
        //If so, assign them to next place in main array
        arr[arrIndex] = rightArray[rightIndex];
        //Increment rightIndex to catch any other bigger elements
        rightIndex++;
        //Increment main index to avoid overwriting
        arrIndex++;
    }
    
    // Free temporary arrays to prevent memory leaks
    free(leftArray);
    free(rightArray);
}


/**
 * Task 2.2: mergesort (helper function)
 * Input argument: - array of integers
 *                 - left and right indexes
 * Output argument: sorted array of integers
 * Return: none
 * Dependencies: mergesort (recursive), merge
 */
void mergeSort(int arr[], int left, int right)
{
    // For recursive calls: Once the left index surpasses
    //the right, the function will begin to unwind
    if(left < right)
    {
        // Calculate mid value using formula Ana taught
        int mid = left + (right - left) / 2;
        
        // Divide current array into two
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        //Sort and merge these halves
        merge(arr, left, mid, right);
    }
}


/**
 * Task 3: Detecting Duplicate Orders (containsDuplicateOrder)
 * Input argument: array of orders, an integer value representing the
 * array size
 * Output argument: none
 * Return: true if there are duplicates, false otherwise
 * Dependencies: string.h
 */
bool containsDuplicateOrder(const Order orders[], int size)
{
    Order dupeOrder[1];
    bool isDupe = false;
    // Iterate through the array using an i index
    for (int i = 0; i < size; i++)
    {
        // Iterate through each iteration from i + 1to the end of the array
        for(int j = i + 1; j < size; j++)
        {
            // Check if compared elements (orders[i] and orders[j]) match
            if( strcmp(orders[i].clientName,
                orders[j].clientName) == 0 &&
                orders[i].category == orders[j].category &&
                orders[i].priority == orders[j].priority &&
                orders[i].staffScore == orders[j].staffScore &&
                strcmp(orders[i].cuisine, orders[j].cuisine) == 0 &&
                orders[i].customerSatisfaction
                == orders[j].customerSatisfaction)
            {
                // If so, print the duplicated array
                // Print user message
                printf("Duplicate found: ");
                
                // Copy struct over to a single index array
                dupeOrder[0] = orders[i];
                // Use this array to input our function for printing
                //orders
                printOrders(dupeOrder, 1);
                
                // We found a duplicate, so change bool to true
                isDupe = true;
            }
        }
    }
    
    // Return whether or not we found a duplicate.
    return isDupe;
}


/**
 * Task 4: Balancing Customer Satisfaction (findTriplets)
 * Input argument: array of orders, an integer value representing the
 * array size
 * Output argument: none
 * Return: error code when memory allocation fails; success code otherwise
 * Dependencies: quicksort, stdlib.h - malloc, free
 */
int findTriplets(const Order orders[], int size)
{
    // Create empty scores array
    int *scores = (int*) malloc(size * sizeof(int));
    
    // Check if the array couldn't be created due
    if (scores == NULL)
    {
        // If so, return an error, and don't proceed with the function
        //to avoid unpredictable behavior.
        return ERROR;
    }
    
    // Iterate through the array of structs
    for (int i = 0; i < size; i++)
    {
        // Copy the customer satisfaction rating to scores
        scores[i] = orders[i].customerSatisfaction;
    }
    
    // Sort the array using quicksort
    quicksort(scores, 0, size - 1);
    
    // Iterate through the array until there isn't space for a possible
    //triplet.
    for (int i = 0; i < size - 2; i++)
    {
        // Check for duplicates in scores[i].
        //If i > 0 and scores[i] is equal to scores[i - 1], we are
        //bound to find a duplicate. So, invert this
        if (!(i > 0 && scores[i] == scores[i - 1]))
        {
        // The middle will begin as the iteration index + 1
        int mid = i + 1;
        // The right will begin at the end
        int right = size - 1;
        
        // The start will effectively be i
        
        // The while loop will run until the middle surpassses right
        while (mid < right)
        {
            // Check if our current indices equal a sum of 0
            int sum = scores[i] + scores[mid] + scores[right];
            // Check sum == 0:
            if (sum == 0)
            {
                // Print message to user
                printf("Triplet found: [%d, ", scores[i]);
                printf("%d, ", scores[mid]);
                printf("%d]\n", scores[right]);
                // Move middle index to the right 
                mid++;
                // Move right index to the left
                right--;
                
                // Check for duplicate values for middle
                while (mid < right && scores[mid] == scores[mid + 1])
                {
                    // Increment middle index to avoid dupe
                    mid++;
                }
                
                //Check for duplicate values for right
                while (mid < right && scores[right] == scores[right - 1])
                {
                    //Decrement right index to avoid dupe
                    right--;
                }
                
                // Increment mid and decrement right indices.
                mid++;
                right--;
            }
            // If our sum is less than 0, since we know our array
            //is sorted, we know we must move mid to the right to
            //raise our sum.
            else if (sum < 0)
            {
                //Move mid index tot he right
                mid++;
            }
            // If sum is greater than or equal to 0, we must move
            //right to the left to lower the sum.
            else
            {
                // Move right index to the left
                right--;
            }
        }
        }
    }
    
    // Free scores array to avoid memory leaks.
    free(scores);
    
    // Return function success.
    return SUCCESS;
}


/**
 * Task 4.1: partition (helper function)
 * Input argument:  - array of integers
 *                  - left and right indexes, representing the range of the
 *                  array to partition
 * Output argument: array partitioned at the pivot value
 * Return: the index of the pivot element after partitioning
 * Dependencies: none
 */
int partition(int arr[], int left, int right)
{
    // Declare pivot as left element in the array
    int pivot = arr[left];
    
    // Let left be passed to our leftIndex value
    int leftIndex = left;
    
    //Let right be passed to our rightIndex value
    int rightIndex = right;
    
    // Declare temp variable for swapping variables
    int temp = 0;
    
    // The while loop will run while the leftIndex hasn't surpassed
    //the right.
    while (leftIndex < rightIndex)
    {
        // Check if left side is less than pivot and leftIndex
        //is less than right - 1
        while(arr[leftIndex] <= pivot && leftIndex <= right - 1)
        {
            // Increment leftIndex until this condition is false
            leftIndex++;
        }
        // Previous condition, but reversed
        while (arr[rightIndex] > pivot && rightIndex >= left + 1)
        {
            // Decrement rightIndex until we escape this condition
            rightIndex--;
        }
        
        // If leftIndex still hasn't surpassed rightIndex,
        //run this block
        if (leftIndex < rightIndex)
        {
            // Swap arr[leftIndex] and arr[rightIndex] to sort
            temp = arr[leftIndex];
            arr[leftIndex] = arr[rightIndex];
            arr[rightIndex] = temp;
        }
    }
    
    // Swap arr[left and arr[rightIndex] to move pivot
    temp = arr[left];
    arr[left] = arr[rightIndex];
    arr[rightIndex] = temp;
    
    // Return swapped pivot for recursive call
    return rightIndex;
}


/**
 * Task 4.2: quicksort (helper function)
 * Input argument:  - array of integers
 *                  - left and right indexes, representing the range of the
 *                  array to partition
 * Output argument: sorted array
 * Return: none
 * Dependencies: partition, quicksort
 */
void quicksort(int arr[], int left, int right)
{
    // If this condition is false, the recursive function will
    //unravel.
    if (left < right)
    {
        // Get pivot for recursive calls
        int pivot = partition(arr, left, right);
        
        // Call for left partition
        quicksort(arr, left, pivot - 1);
        
        // Call for right partition.
        quicksort(arr, pivot + 1, right);
    }
}


/**
 * Task 5: Grouping Orders by Cuisine (groupOrders)
 * Input argument: array of orders, an integer value representing the
 * array size
 * Output argument: array of orders sorted by cuisine
 * Return: none
 * Dependencies: insertionsort, string.h, stdio.h
 */
void groupOrders(Order orders[], int size)
{
    // To start, we have to sort the orders
    insertionsort(orders, size);
    
    // Create temporary arrays for different groups and namesInGroup
    char **groups = (char**) malloc(size * sizeof(char*));
    int *sizeGroups = (int*) malloc(size * sizeof(int));
    
    int numOfGroups = 0;
    
    // Iterate through the array of structs
    for (int i = 0; i < size; i++)
    {
        // If this is the first time running, or if we found a new cuisine,
        //run this function
        if (numOfGroups == 0 ||
            strcmp(orders[i].cuisine, groups[numOfGroups - 1]) != 0)
        {
            // Make a new group for the new cuisine
            groups[numOfGroups] = orders[i].cuisine;
            // Set the size of this new group to 1
            sizeGroups[numOfGroups] = 0;
            // Raise the number of groups by 1
            numOfGroups++;
        }
        // Increment count in current group based on numOfGroups
        sizeGroups[numOfGroups - 1]++;
        
    }
    
    //Print the orders in groups of cuisine to the user
    for (int i = 0; i < numOfGroups; i++) {
        
        //Print the cuisine name to the user
        printf("%s: [", groups[i]);
        
        for (int j = 0; j < sizeGroups[i]; j++) {
            
            if (j > 0) {
                
                //Print a formatted comma if we aren't at the end yet
                printf(", ");
                
            }
            
            // Print the name of the client with that cuisine
            printf("%s", orders[j].clientName);
        }
        
        // Print a formatted newline break
        printf("]\n");
        
    }
    
    
    
    // Free the allocated arrays
    free(groups);
    free(sizeGroups);
}


/**
 * Task 5.1: insertionsort (helper function)
 * Input argument: array of orders, an integer value representing the
 * array size
 * Output argument: array of orders sorted by cuisine
 * Return: none
 * Dependencies: string.h
 */
void insertionsort(Order orders[], int size)
{
    // Iterate through array of structs
    for (int i = 1; i < size; i++)
    {
        // Initialize element to insert in sorted position
        Order insert = orders[i];
        
        // Initialize left value
        int left = i - 1;
        
        // While we aren't at the end, and our element will be
        //sorted if placed (comparison using strcmp)
        while (left >= 0 && strcmp(orders[left].cuisine, insert.cuisine) > 0)
        {
            // Shift the elements over in the while loop
            orders[left + 1] = orders[left];
            
            // Decrement left index to keep shifting
            left--;
        }
        // Finally, insert our sorted element into its correct place
        orders[left + 1] = insert;
    }
}


/**
 * Task 6: Ranking Delivery Staff by Performance (sortStaffFromOrders)
 * Input argument: array of orders, an integer value representing the
 * array size
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void sortStaffFromOrders(Order orders[], int size)
{
    // Create a new empty array of structs for copying
    Order sortedOrders[size];
    
    // Iterate through the size of the arrays
    for (int i = 0; i < size; i++)
    {
        // Copy each struct in orders[] to sortedOrders[]
        sortedOrders[i] = orders[i];    
    }
    
    // Iterate through the size of the array
    for (int i = 0; i < size; i++)
    {
        // Iterate through each iteration
        for(int j = 0; j < size - i - 1; j++)
        {
            // If an unsorted element is found, swap them.
            if(sortedOrders[j].staffScore > sortedOrders[j + 1].staffScore)
            {
                // Swap sortedOrders[j] and sortedOrders[j + 1]
                Order tempScore = sortedOrders[j];
                sortedOrders[j] = sortedOrders[j + 1];
                sortedOrders[j + 1] = tempScore;
            }
        }
    }
    
    // Iterate backwards through the size of the array
    for(int i = size - 1; i >= 0; i--)
    {
        // Print the client name and score, from highest to lowest.
        printf("%s: ", sortedOrders[i].clientName);        
        printf("%d\n", sortedOrders[i].staffScore);
    }
}


/**
 * Function: displayMenu (provided)
 * Input argument: none
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void displayMenu() 
{
    // print the title of the order management system
    printf("\nQuickBite Order Management System\n");
    // print the option to view orders
    printf("1. View Orders\n");
    // print the option to reset orders to the original state
    printf("2. Reset Orders to Original\n");
    // print the option to sort orders by category
    printf("3. Sort Orders by Category\n");
    // print the option to find the k-th highest priority order
    printf("4. Find k-th Highest Priority\n");
    // print the option to detect duplicate orders
    printf("5. Detect Duplicate Orders\n");
    // print the option to find route triplets among orders
    printf("6. Find Customer Service Score Triplets\n");
    // print the option to group orders by cuisine
    printf("7. Sort and Group Orders by Cuisine\n");
    // print the option to sort staff by performance
    printf("8. Print Staff by Performance\n");
    // print the option to exit the program
    printf("9. Exit\n");
}

/**
 * Function: readCSV (provided)
 * Input argument: filename, array of orders, a pointer to the array size
 * Output argument: filled array of orders, updated array size
 * Return: success or error code
 * Dependencies: stdio.h
 */
int readCSV(const char* filename, Order orders[], int* size) 
{
    // open the file for reading
    FILE* file = fopen(filename, "r");
    // if the file is open
    if (!file) 
    {
        // print the error
        perror("Failed to open file");
        // return the error code
        return ERROR;
    }

    // start an index at 0
    int i = 0;
    // while there's data to read in the file
    while (fscanf(file, "%d,%49[^,],%d,%d,%d,%49[^,],%d", 
                  &orders[i].id, 
                  orders[i].clientName,
                  (int*)&orders[i].category, 
                  &orders[i].priority, 
                  &orders[i].staffScore, 
                  orders[i].cuisine, 
                  &orders[i].customerSatisfaction) == 7) 
    {
        // increment the index
        i++;
    }
    // set the size pointer to index
    *size = i;
    // close the file
    fclose(file);
    // return success
    return SUCCESS;
}

/**
 * Function: printOrders (provided)
 * Input argument: array of orders, an integer value representing the
 * array size
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void printOrders(const Order orders[], int size)
{
    // traverse the array
    for (int i = 0; i < size; i++) 
    {
        // print details of each order
        printf("Order #%d - %s, Category: %d, Priority: %d, Staff Score: %d,"
            "Cuisine: %s, Customer Satisfaction Score: %d\n", orders[i].id, 
            orders[i].clientName, orders[i].category, orders[i].priority,
            orders[i].staffScore, orders[i].cuisine, 
            orders[i].customerSatisfaction); 
    }
}