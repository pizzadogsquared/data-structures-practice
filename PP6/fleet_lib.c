// header files
#include "fleet_lib.h"

/**
 * Task 1: Validate Delivery Path
 * Input argument: routeHead - a pointer to the head node of a linked list
 *                  representing the delivery route
 * Output argument: none
 * Return: true if the path is valid, false otherwise
 * Dependencies: createStack, push, pop
 */
bool validateDeliveryPath(Node* routeHead)
{
    // Initialize empty stack to find matching brackets
    Stack* newStack = createStack();

    // Create a node to iterate through the passed route linked list
    Node* current = routeHead;
    
    // Create placeholder data value for linked list
    char* data;
    // Create placeholder top value for the popping stack
    char* top;
    // Create placeholder check so we can free stack memory before
    //returning false
    bool check = true;

    // Iterate through the linked list using current
    while(current != NULL)
    {
        // Get current data via current iterator
        data = current->data;

        // Check for opening brackets and push to the stack
        if(data[0] == '(' || data[0] == '[' || data[0] == '{')
        {
            // If our data is an opening bracket (start of stack),
            //push the data
            push(newStack, data);
        }
        // Check for closing brackets so we can validate the route
        else if(data[0] == ')' || data[0] == ']' || data[0] == '}' )
        {
            // Get top value
            top = pop(newStack);

            // If stack is empty, or if the top of the stack is not
            //a matching bracket of the same type...
            if(top == NULL || 
            !((top[0] == '(' && data[0] == ')') ||
              (top[0] == '[' && data[0] == ']') ||
              (top[0] == '{' && data[0] == '}')))
            {
                // Return false because there was a mismatch
                check = false;
            }
        }
        // If an invalid character was found...
        else
        {
            // Return false because there was a mismatch
            check = false;
        }

        // Move to the next node using current
        current = current->next;
    }

    // At this point, a fully matched route will result in an empty stack.
    //This means that if our stack isn't empty, our route wasn't matched.
    if (!isEmptyStack(newStack))
    {
        check = false;
    }
    
    while(!isEmptyStack(newStack))
    {
        pop(newStack);
    }
    
    if(!check)
    {
        return false;
    }
    
    // Return true if all of our checks passed
    return true;
}


/**
 * Task 2: Symmetric Route
 * Input argument: routeHead - a pointer to the head node of a linked list 
 *                  representing the delivery route
 * Output argument: none
 * Return: true if the delivery route is symmetric, false otherwise
 * Dependencies: createStack, push, pop
 *               string.h - strcmp
 */
bool isSymmetricRoute(Node* routeHead)
{
    // Initialize empty stack to find matching brackets
    Stack* newStack = createStack();

    // Create a node to iterate through the passed route linked list
    Node* current = routeHead;
    
    // Create placeholder data value for linked list
    char* data;
    // Create top value to hold the top of the stack
    char* top;
    // Init size with 0
    int size = 0;
    // Initialize index
    int i = 0;
    // Initialize check for escaping while loop
    bool check = true;
    
    // Iterate through list to get size
    while(current != NULL)
    {
        // Traverse the list
        current = current->next;
        
        // Increment size
        size++;
    }
    
    // Reset iterator to head of list
    current = routeHead;
    
    // Iterate through half the array (rounded down if odd)
    while(i < size / 2)
    {
        // Push to the stack
        push(newStack, current->data);
        
        // Traverse to next node in the linked list
        current = current->next;
        
        // Increment our index
        i++;
    }
    
    // Reset index
    i = 0;
    
    // If the size of our linked list was odd, run this
    if (size % 2 != 0)
    {    
        // Traverse forwards once because the middle of an odd-length
        //palindrome doesn't matter
        current = current->next;
    }    
    
    // Get to the start of the right half of the array
    current = current->next;
    
    // Iterate through half the array (rounded down if odd)
    while(i < size / 2)
    {
        // Get current data    
        data = current->data;
        
        // Get the top of the stack
        top = pop(newStack);
        
        // See if the reversed left half (top of stack) doesn't match
        //with the data of the right half
        if(strcmp(top, data) != 0)
        {
            // Set return check to false
            check = false;
        }
        
        // Traverse the array
        current = current->next;
        
        // Increment the index
        i++;
    }
    
    // Free the stack memory until it's empty just in case
    while(!isEmptyStack(newStack))
    {
        // Free current top
        pop(newStack);
    }
    
    // If failed the palindrome check...
    if(!check)
    {
        // Return false because of fail
        return false;
    }
    
    // Return true if all of our checks passed
    return true;
}


/**
 * Task 3: Decoding Drone Instructions
 * Input argument: instructionHead - a pointer to the head node of a linked 
 *                  list containing encoded drone instructions
 * Output argument: none
 * Return: none
 * Dependencies: createStack, push, pop, isEmptyStack
 *               stdlib.h - malloc, atoi
 *               string.h - strcmp, strcat, strcpy
 */
void decodeInstructions(Node* instructionHead)
{

}



/**
 * Task 4: Evaluate Delivery Paths
 * Input argument: expressionHead - a pointer to the head node of a linked list 
 *                 representing a Reverse Polish Notation expression
 * Output argument: none
 * Return: integer value representing the result of the evaluated expression
 * Dependencies: create, push, pop, intToStr
 *               stdlib.h - atoi
 */
int evaluatePathConditions(Node* expressionHead)
{
    // Create an empty stack to handle expressions
    Stack* newStack = createStack();
    
    // Create iterator to go through linked list
    Node* current = expressionHead;

    // Init a factor for the expressions
    int factor1;
    // Init another factor for the expressions
    int factor2;
    // Store the result of operations in result
    int result;
    char* resultString;
    
    // Iterate through the passed linked list
    while(current != NULL)
    {
        // Check for operations
        // First, check for addition
        if(current->data[0] == '+')
        {
            // Get one of our factors from the stack
            factor1 = atoi(pop(newStack));
            // Get next factor from the stack
            factor2 = atoi(pop(newStack));
            
            // Get the result by performing the operation we checked
            //for on our factors
            result = factor2 + factor1;
            
            // We need this to be a string
            resultString = intToStr(result);
            
            // Push the result onto the stack so we can use it
            //for future operations
            push(newStack, resultString);
        }
        else if(current->data[0] == '-')
        {
            // Get one of our factors from the stack
            factor1 = atoi(pop(newStack));
            // Get next factor from the stack
            factor2 = atoi(pop(newStack));
            
            // Get the result by performing the operation we checked
            //for on our factors
            result = factor2 - factor1;
            
            // We need this to be a string
            resultString = intToStr(result);
            
            // Push the result onto the stack so we can use it
            //for future operations
            push(newStack, resultString);
        }
        else if(current->data[0] == '*')
        {
            // Get one of our factors from the stack
            factor1 = atoi(pop(newStack));
            // Get next factor from the stack
            factor2 = atoi(pop(newStack));
            
            // Get the result by performing the operation we checked
            //for on our factors
            result = factor2 * factor1;
            
            // We need this to be a string
            resultString = intToStr(result);
            
            // Push the result onto the stack so we can use it
            //for future operations
            push(newStack, resultString);
        }
        else if(current->data[0] == '/')
        {
            // Get one of our factors from the stack
            factor1 = atoi(pop(newStack));
            // Get next factor from the stack
            factor2 = atoi(pop(newStack));
            
            // Get the result by performing the operation we checked
            //for on our factors
            result = factor2 / factor1;
            
            // We need this to be a string
            resultString = intToStr(result);
            
            // Push the result onto the stack so we can use it
            //for future operations
            push(newStack, resultString);
        }
        else
        {
            // If other checks were false, then we're on a factor
            //in our linked list traversal. Push it on the stack
            push(newStack, current->data);
        }
        
        // Traverse to next node in linked list
        current = current->next;
    }
    
    // Result should be on the top of the stack
    result = atoi(pop(newStack));
    
    // If we somehow have a non-empty stack, we must free it
    while(!isEmptyStack(newStack))
    {
        // Free all memory in the stack
        pop(newStack);
    }
    
    // Return our result as an int
    return result;
}


/**
 * Task 5: Reversing Delivery Routes
 * Input argument: queue - A pointer to a Queue representing the list of 
 *                  deliveries
 * Output argument: reversed delivery list
 * Return: none
 * Dependencies: createStack, push, pop, enqueue, dequeue, isEmptyQueue, 
 *               isEmptyStack
 */
void reverseDelivery(Queue* q)
{
    // Initialize empty stack to help reverse the queue
    Stack* newStack = createStack();
    // Initialize data var to hold data for reversing
    char* data;
    
    // Iterate through passed queue
    while(!isEmptyQueue(q))
    {
        // Dequeue the data at the front
        data = dequeue(q);
        
        // Push this data onto the stack
        push(newStack, data);
    }
    
    // Iterate through our newly created stack
    while(!isEmptyStack(newStack))
    {
        // Get data from stack
        data = pop(newStack);
        
        // Enqueue it back onto the queue
        //(It will be in reverse order now)
        enqueue(q, data);
    }
    
    // Our stack is empty, so we can safely escape the function
}


/**
 * Task 6: Rotating Delivery Schedules
 * Input argument: queue - a pointer to a Queue representing the list of 
 *                  deliveries
 *                 k - an integer indicating the number of positions to rotate
 * Output argument: rotated queue
 * Return: none
 * Dependencies: isEmptyQueue
 */
void rotateDelivery(Queue* queue, int k)
{
    // Initialize data var to help with dequeue/requeue to rotate queue
    char* data;
    // Hold initial front pointer to queue
    Node* front = queue->front;
    
    // Declare a size to hold size for queue
    int size = 0;
    
    // Useful check var to help with while conditions
    bool escape = false;
    
    // Get current front of queue
    data = dequeue(queue);
    // Enqueue back into queue
    enqueue(queue, data);
    // Increment size
    size++;
    
    // If queue has more than 1 node...
    if(queue->front != queue->rear)
    {
        // Iterate through the whole queue to get the size
        while(!escape)
        {
            // If we've reached the end of the queue
            if(front == queue->front)
            {
                enqueue = true;
            }
            // If not, traverse further into the queue
            else
            {
                // Get current front of queue
                data = dequeue(queue);
                // Enqueue back into queue
                enqueue(queue, data);
                // Increment size
                size++;
            }
        }
    }
    
    // Reduce k to the remainder
    k = k % size;

    // Now we have the size of the array, and it has been
    //rotated to the left once. From here, we can rotate to
    //the left by (size - k) % size logic using our information.
    //This is equivalent to rotating right by k.
    for(int i = 0; i < (size - k) % size; i++)
    {
        // Rotate k to the left
        data = dequeue(queue);
        enqueue(queue, data);
    }
}


/**
 * Task 7: Merging Delivery Routes
 * Input argument: queue1 - a pointer to the first Queue representing a 
 *                  delivery route
 *                 queue2 - s pointer to the second Queue representing a    
 *                  delivery route
 * Output argument: none
 * Return: a pointer to a new Queue containing the merged elements
 * Dependencies: createQueue, dequeue, enqueue, isEmptyQueue
 */
Queue* mergeDeliveryRoutes(Queue* q1, Queue* q2)
{
    // Create a new queue to hold our merged queue.
    Queue* newQueue = createQueue();
    
    // Create a front var to hold the pointer to q1's initial front.
    // This will help check the condition in the while loop for if we've
    //looped through the entire while loop.
    Node* front = q1->front;
    
    // Initialize data var to hold dequeued values for copying
    char* data;
    
    // Useful check var to help with while conditions
    bool escape = false;

    // Get current front of q1
    data = dequeue(q1);
    // Enqueue back into q1
    enqueue(q1, data);
    // Copy into our newQueue
    enqueue(newQueue, data);
    
    // If q1 has more than 1 node...
    if(q1->front != q1->rear)
    {
        // Iterate through the whole queue to get the size
        while(!escape)
        {
            // If we've wrapped around the entirety of q1,
            //then we have copied all of q1, so we can escape
            if(strcmp(q1->front, front) == 0)
            {
                escape = true;
            }
            // If not, copy this node and requeue to move on
            else
            {
                // Get current front of q1
                data = dequeue(q1);
                // Enqueue back into q1
                enqueue(q1, data);
                // Copy into our newQueue
                enqueue(newQueue, data);
            }
        }
    }
    
    
    // We must do something similar for q2:
    
    // Re-init front with q2's initial front pointer
    Node* front = q2->front;
    // Re-init escape condition
    bool escape = false;
    
    // Get current front of q2
    data = dequeue(q2);
    // Enqueue back into q2
    enqueue(q2, data);
    // Copy into our newQueue
    enqueue(newQueue, data);
    
    // If q2 has more than 1 node...
    if(q2->front != q2->rear)
    {
        // Iterate through the whole queue to get the size
        while(!escape)
        {
            // If we've wrapped around the entirety of q2,
            //then we have copied all of q1, so we can escape
            if(q2->front == front)
            {
                escape = true;
            }
            // If not, copy this node and requeue to move on
            else
            {
                // Get current front of q2
                data = dequeue(q2);
                // Enqueue back into q2
                enqueue(q2, data);
                // Copy into our newQueue
                enqueue(newQueue, data);
            }
        }
    }
    
    // We have a merged queue, and our q1 and q2 remain the same as
    //they were passed to us. Return our merged queue pointer.
    return newQueue;
}


// Stack & Queue implementations
/**
 * Function: createStack
 * Input argument: none
 * Output argument: none
 * Return: a pointer to a newly allocated Stack structure
 * Dependencies: stdlib.h - malloc
 */
Stack* createStack()
{
    // Allocate memory for the new stack
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    
    // Set the newStack's top to null to init as empty
    newStack->top = NULL;
    
    // Return the new stack
    return newStack;    
}


/**
 * Function: push
 * Input argument: stack - a pointer to a Stack structure
 *                 value - a pointer to a string to be pushed onto the stack
 * Output argument: the stack contains an additional node at the top
 * Return: none
 * Dependencies: createNode
 */
void push(Stack* stack, char* value)
{
    // Create a new node and store address
    Node* newNode = createNode(value);
    
    // Link the newNode's next to the old top, making newNode the head
    newNode->next = stack->top;
    
    // Make newNode the new top
    stack->top = newNode;
}


/**
 * Function: pop
 * Input argument: stack - a pointer to a Stack structure
 * Output argument: stack's top element is removed
 * Return: a pointer to the string popped from the top of the stack
 *         NULL if the stack is empty
 * Dependencies: isEmptyStack
 *               stdlib.h - free
 */
char* pop(Stack* stack)
{    
    // Check if stack is empty
    if(isEmptyStack(stack))
    {
        // If so, return NULL, as we can't pop something that doesn't exist
        return NULL;
    }

    // Get address of node to remove
    Node* removeMe = stack->top;
    // Get data we need to pop
    char* data = removeMe->data;
    
    // Set new top to next value in the stack
    stack->top = stack->top->next;
    
    // Free the dynamic memory
    free(removeMe);
    
    // Return the data popped.
    return data;
}


/**
 * Function: isEmptyStack
 * Input argument: stack - a pointer to a Stack
 * Output argument: none
 * Return: true if the stack is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyStack(Stack* stack)
{
    if(stack->top == NULL)
    {
        return true;
    }
    return false;
}


/**
 * Function: createQueue
 * Input argument: none
 * Output argument: none
 * Return: a pointer to a newly allocated Queue
 * Dependencies: stdlib.h - malloc
 */
Queue* createQueue()
{
    // Allocate memory for the new queue
    Queue* newQueue = (Queue*)malloc(sizeof(Queue));
    
    // Initialize the front to point to NULL
    newQueue->front = NULL;
    
    // Initialize the rear to point to NULL
    newQueue->rear = NULL;
    
    // Return the new queue
    return newQueue;
}


/**
 * Function: enqueue
 * Input argument: queue - a pointer to a Queue
 *                 value - a pointer to a character string to be added to the 
 *                  rear of the queue
 * Output argument: an updated queue
 * Return: none
 * Dependencies: createNode, isEmptyQueue
 */
void enqueue(Queue* queue, char* value)
{
    // Create a new node and store address
    Node* newNode = createNode(value);

    if(isEmptyQueue(queue))
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        // Point the old rear to newNode
        queue->rear->next = newNode;
    
        // Make newNode be the new rear
        queue->rear = newNode;
    }
}


/**
 * Function: dequeue
 * Input argument: queue - a pointer to a Queue
 * Output argument: an updated queue
 * Return: A pointer to the character string removed from the front of the queue.
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
char* dequeue(Queue* queue)
{
    // Check if queue is empty
    if(isEmptyQueue(queue))
    {
        // If so, return NULL, as we can't dequeue something that
        //doesn't exist
        return NULL;
    }

    // Get address of node to remove
    Node* removeMe = queue->front;
    
    // Get data we need to dequeue
    char* data = removeMe->data;
    
    // Set new front to next value in the queue
    queue->front = queue->front->next;
    
    // If this dequeue results in an empty queue, front will be NULL now
    if(queue->front == NULL)
    {
        // We must also set rear to NULL to reflect that this queue is empty
        queue->rear = NULL;
    }
    
    // Free the dynamic memory
    free(removeMe);
    
    // Return the data dequeued.
    return data;
}


/**
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a Queue
 * Output argument: none
 * Return: true if the queue is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyQueue(Queue* queue)
{
    if (queue->front == NULL && queue->rear == NULL)
    {
        return true;
    }
    return false;
}


/**
 * Function: createNode (provided)
 * Input argument: value - a pointer to a string to be stored in the new node
 * Output argument: none
 * Return: a pointer to a newly allocated Node with the given value
 * Dependencies: stdlib.h - malloc
 */
Node* createNode(char* value)
{
    // allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    // set the data field
    newNode->data = value;
    // initialize the next pointer to NULL
    newNode->next = NULL;
    // return the new node
    return newNode;
}

/**
 * Function: intToStr (provided)
 * Input argument: num - an integer value to be converted to a string
 * Output argument: none
 * Return: a pointer to a dynamically allocated string representing the integer
 * Dependencies: stdlib.h - malloc
 */
char* intToStr(int num)
{
    // declare a variable to hold the lenght of the number (#digits)
    int len = 0;
    // declare a variable to help calculating the # of digits
    int temp = num;

    // if the number is 0
    if (num == 0)
    {
        // the length is 1
        len = 1;
    }
    // otherwise
    else
    {
        // while the temporary variable is greater than 0
        while (temp > 0)
        {
            // count a digit
            len++;
            // divide the number by 10
            temp /= 10;
        }
    }
    
    // allocate memory for the string
    char* str = (char*)malloc((len + 1) * sizeof(char));
    // null-terminate the string
    str[len] = '\0';

    // while there are digits in the number
    while (len > 0)
    {
        // decrement the length
        len--;
        // convert the rightmost digit to a character
        //      and assign to current position len in the string
        str[len] = (num % 10) + '0';
        // divide the number by 10
        num /= 10;
    }
    // return the string
    return str;
}