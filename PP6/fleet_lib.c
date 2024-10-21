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
                return false;
            }
        }
		// If an invalid character was found...
		else
		{
			// Return false because there was a mismatch
			return false;
		}

        // Move to the next node using current
        current = current->next;
    }

    // At this point, a fully matched route will result in an empty stack.
	//This means that if our stack isn't empty, our route wasn't matched.
    if (!isEmptyStack(newStack))
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
    newNode->rear = NULL;
    
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