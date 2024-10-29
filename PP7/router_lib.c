#include "router_lib.h"

/**
 * Task 1: Add a New Router
 * Input argument: root - a double pointer to the root of the network
 *                 router_id - the identification for the new router
 * Output argument: the last unfilled position of the last level contains a new 
 *                  router with id router_id
 * Return: none
 * Dependencies: createRouter, createQueue, isEmptyQueue, enqueue, dequeue
 */
void addRouter(RouterNode** root, int router_id)
{
    // Allocate memory for a newRouter node
    RouterNode* newRouter = createRouter(router_id);
	// Init an empty queue for our BFT
	Queue queue = createQueue();
	// Init current node for traversal
	RouterNode* current;
	
	// Make useful check for exiting future while loop
	bool check = false;
    
	
	
	// If an empty tryee was passed...
    if (*root == NULL)
    {
		// Set the root to the newRouter
        *root = newRouter;
    }
	// If not...
	else
	{
		// Enqueue the root node for BFT
		enqueue(&queue, *root);
		
		// Traverse the passed tree from the root node using BFT
		//(As long as our queue isn't empty and our check isn't true)
		while(!isEmptyQueue(queue) && !check)
		{
			
			// Get our current node from the queue
			current = dequeue(&queue);
			
			// If the left child of our current is NULL...
			if (current->left == NULL)
			{
				// Add the newrouter to the left
				current->left = newRouter;
				// Escape the while loop on next pass
				check = true;
			}
			// If left child is not null...
			else
			{
				// We have to add it to the queue for later loops
				enqueue(&queue, current->left);
			}
			
			// If the right child of our current is null
			//(and if we haven't already added the new router)...
			if(!check && current->right == NULL)
			{
				// Add the new router to the right
				current->right = newRouter;
				// Escape while loop on the next pass
				check = true;
			}
			// If we STILL haven't added our new router...
			else if (!check)
			{
				// We have to enqueue the right node for later loops, too
				enqueue(&queue, current->right);
			}
		}
		
		// Now we have added our new router to the tree
		
		// Free the entire queue in case there's still some of it left
		while(!isEmptyQueue(queue))
		{
			dequeue(&queue)
		}
	}
}


/**
 * Task 2: Remove a Faulty Router
 * Input argument: root - a double pointer to the root of the network
 *                 router_id - the identification for the new router
 * Output argument: the target router is replaced with the last router in the 
 *                   network (bottomost, rightmost node)
 * Return: none
 * Dependencies: createQueue, isEmptyQueue, enqueue, dequeue
 *               stdlib.h - free
 */
void removeRouter(RouterNode** root, int router_id)
{
	// Declare a target placeholder to hold the pointer
	//that matches the ID we're looking for
	RouterNode* target = NULL;
	// Declare last pointer to hold the address of the
	//bottom-right node
	RouterNode* last = NULL;
	// Declare last parent pointer to hold the address of the
	//parent of the bottom-right node
	RouterNode* lastParent = NULL;
	// Declare current node for traversal
	RouterNode* current;
	// Helpful check bool for escaping while loop
	bool check = false;
	
	// Init an empty queue
	Queue queue = createQueue();
	// The first element will be the root node, and will
	//propagate from there
	enqueue(&queue, *root);
	
	// Traverse the whole queue using BFT until we reach the end.
	while(!isEmptyQueue(&queue))
	{
		// Get our current traversal node via BFT
		current = dequeue(&queue);
		
		// If our current node matches what we're looking for...
		if( current->router_id == router_id)
		{
			// Get target node pointer
			target = current;
		}
		// Set last each loop. By the final loop, last will hold the
		//actual last pointer of the tree
		last = current;
		
		// Enqueue the left child of this node if it exists
		if (current->left != NULL)
		{
			enqueue(&queue, current->left);
		}
		// Enqueue the right child of this node if it exists
		if(current->right != NULL)
		{
			enqueue(&queue, current->right);
		}
	}
	
	// If we've found the target...
	if (target != NULL)
	{
		// Remove the target, and replace it with last.
		target->router_id = last->router_id;
		
		// Now we must remove last, so we have to find its
		//parent to unlink it from tree.
		
		// Free the entire queue in case there's still some of it left
		while(!isEmptyQueue(queue))
		{
			dequeue(&queue);
		}
		
		// Restart the traversal by enqueueing root node
		enqueue(&queue, *root);
		// Traverse the tree again using BFT
		while (!isEmptyQueue(&queue) && !check)
		{
			// Get our current traversal node via BFT
			current = dequeue(&queue);
			
			// Check if current node has last as a left child
			if(current->left == last)
			{
				// If so, free the memory
				free(last);
				// Unlink from the tree
				current->left = NULL;
				// Escape while loop using check value
				check = true;
			}
			// Check if current node has last as a right child
			else if(current->right == last && !check)
			{
				// If so, free the memory
				free(last);
				// Unlink from the tree
				current->right = NULL;
				// Escape while loop using check value
				check = true;
			}
			
			// Enqueue the left child if it exists (and if we haven't
			//already found last's parent)
			if (current->left != NULL && !check)
			{
				enqueue(&queue, current->left);
			}
			// Enqueue the right child if it exists (and if we haven't
			//already found last's parent)
			if(current->right != NULL && !check)
			{
				enqueue(&queue, current->right);
			}
		}
		
		// Free the entire queue in case there's still some of it left
		while(!isEmptyQueue(queue))
		{
			dequeue(&queue)
		}
	}
}


/**
 * Task 3: Invert Router Network
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: the pointer to the root node, where the tree's left and right sides 
 *          are swapped
 * Dependencies: invertNetwork (recursive)
 */
RouterNode* invertNetwork(RouterNode* root)
{
	// Base case: if our root is null...
	if (root == NULL)
	{
		// Return null to "unwind" recursive call
		//(there are no children of this root)
		return NULL;
	}
	
	// Switch the left child address of current subtree root
	//with this root's right child
	RouterNode* temp = root->left;
	root->left = root->right;
	root->right = temp;
	
	
	// Recursively call for each side of subtree
	invertNetwork(root->left);
	invertNetwork(root->right);
	
	// Return address of this root
	return root;
}


/**
 * Task 4: Ensure Symmetrical Routing
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: true if the routing is symmetric, false otherwise
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 */
bool isRoutingSymmetric(RouterNode* root)
{
	// If our tree is just a root node...
	if (root == NULL)
	{
		// Return true because it is symmetric
		return true;
	}
	
	// Declare a placeholder node for nodes on the leftside
	//of the root
	RouterNode* leftNode;
	// Declare a placeholder node for nodes on the right side
	//of the root
	RouterNode* rightNode;
	// Useful check var for while loop condition
	bool check = true;
	
	// Init an empty queue to traverse the route and
	//match all nodes on either side
	Queue queue = createQueue();
	// Enqueue the root for left side traversal
	enqueue(&queue, root);
	// Enqueue the root AGAIN for right side traversal
	enqueue(&queue, root);
	
	
	
	// Iterate through the route
	while (!isEmptyQueue(&queue) && !check)
	{
		// Get node for left side check
		leftNode = dequeue(&queue);
		// Get node for right side check
		rightNode = dequeue(&queue);
		
		// If one of the nodes is null, but not the other...
		if(((leftNode == NULL) || (rightNode == NULL)) &&
		   (leftNode != rightNode))
		{
			// Then this tree isn't symmetric
			check = false;
		}
		
		// If the router IDs don't match...
		if((leftNode->router_id) != (rightNode->router_id))
		{
			// Then this tree isn't symmetric
			check = false;
		}
		
		// Enqueue left child on left side
		enqueue(&queue, leftNode->left);
		// Mirrored across the middle, we must enqueue
		//right child on right side
		enqueue(&queue, rightNode->right);
		//Enqueue right child on left side
		enqueue(&queue, leftNode->right);
		// Mirrored across the middle, we now must enqueue
		//the left child on the right side
		enqueue(&queue, rightNode->left);
	}
	
	// Free the entire queue in case there's still some of it left
	while(!isEmptyQueue(queue))
	{
		dequeue(&queue)
	}
	
	// If we found that our routing wasn't symmetric...
	if(!check)
	{
		// Return false
		return false;
	}
	
	// Otherwise, our symmetric checks passed, so return true
	return true;
}


/**
 * Task 5: Analyze Maximum Network Depth
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: an integer value representing the maximum depth of the tree
 * Dependencies: getMaxNetworkDepth (recursive)
 */
int getMaxNetworkDepth(RouterNode* root)
{
	// Our base case: if root is null...
	if (root == NULL)
	{
		// Then return 0
		return 0;
	}
	
	//We need a variable to hold the max depth we've found
	int max;
	
	// Get depth of left branch of our subtree
	int leftDepth = getMaxNetworkDepth(root->left);
	// Now we get depth of right branch of the subtree
	int rightDepth = getMaxNetworkDepth(root->right);
	
	// If our left side has a bigger depth than right...
	if(leftDepth > rightDepth)
	{
		// Hold the bigger value in max
		max = leftDepth;
	}
	// If they're equal, or if right side has greater depth...
	else
	{
		// Hold the bigger, or equal if equal, value in max
		max = rightDepth;
	}
	
	// Return max we found plus a single level for this one
	return max + 1;
}


/**
 * Task 6: Get a Right-Side View of the Router Network
 * Input argument: root - a pointer to the root of the network
 *                 level - an integer representing the current level (root is 
 *                         at level 0)
 *                  maxLevel - an integer value representing the last level 
 *                         (initially set to -1)
 * Output argument: none
 * Return: none
 * Dependencies: getRouterRightView (recursive)
 *               stdio.h - printf
 */
void getRouterRightView(RouterNode* root, int level, int* maxLevel)
{
	// Base case: As long as root of current subtree isn't null,
	//run the function
	if (root != NULL)
	{
		// If this is the first node we've seen from
		//this level, it is the rightmost
		if (*maxLevel < level + 1)
		{
			// Print its router ID
			printf("%d ", root->router_id);
			// Raise the max level for next print statement
			*maxLevel = level + 1
		}
		
		// Call right side traversal first so we try to see
		//if this has our rightmost node
		getRouterRightView(root->right, level + 1, maxLevel);
		// After right side unwinds, we can see if the leftside
		//has the node we're looking for, or if we have already found it
		getRouterRightView(root->left, level + 1, maxLevel);
	}
}


/**
 * Function: findHighTrafficRouters
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 *               stdio.h - printf
 */
void findHighTrafficRouters(RouterNode* root)
{
	// If our tree isn't empty...
	if(root != NULL)
	{
		// Init an empty queue
		Queue queue = createQueue();
		// The first element will be the root node, and will
		//propagate from there
		enqueue(&queue, root);
		// Temp value for processing size var
		QueueNode* temp;
		
		RouterNode* current;
		
		// The number of nodes at a level
		int size;
		// Max ID of a router per level
		int maxID;
		// Index for iterating through nodes
		int index;
		
		// Iterate through the tree's levels
		while (!isEmptyQueue(&queue))
		{
			// Reset size back to 0
			size = 0;
			// Reset maxID to a min value
			maxID = -1;
			
			// We need the size of the level we're on
			temp = queue.front;
			
			// Iterate through the queue
			while(temp != NULL)
			{
				// Increment size
				size++;
				// Go to next element in the queue
				temp = temp->next;
			}
			
			// Reset index for this level
			index = 0;
			// Now we will find which node is the max
			//on this level (iterate through level nodes)
			while(index < size)
			{
				// Get node at front of queue
				current = dequeue(&queue);
				
				
				// If this node is the greatest we've found on this level...
				if(current->router_id > maxID)
				{
					// Set max to the new biggest ID
					maxID = current->router_id;
				}
				
				
				// If this parent has a left child...
				if (current->left != NULL)
				{
					// Add it to the queue so we can check for max later
					enqueue(&queue, current->left);
				}
				// If this parent has a right child...
				if (current->right != NULL)
				{
					
					// Add it to the queue so we can check for max later
					enqueue(&queue, current->right);
				}
				
				//Increment index to process all nodes
				index++;
			}
			
			// Now we should have a max for this level
			
			// Print the max we found
			printf("%d ", maxID); 
		}
	}
}


/**
 * Task 8: Show Routers
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */
void printNetwork(RouterNode* root)
{
	// If our tree is empty...
	if(root == NULL)
	{
		// Print a statement to the user
		printf("The route is empty!\n");
	}
	// Otherwise...
	else
	{
		// Declare current node for BFT traversal
		RouterNode* current;
		
		// Init an empty queue
		Queue queue = createQueue();
		// The first element will be the root node, and will
		//propagate from there
		enqueue(&queue, *root);
		
		// Traverse the whole queue using BFT until we reach the end.
		while(!isEmptyQueue(&queue))
		{
			// Get our current traversal node via BFT
			current = dequeue(&queue);
			
			// Print current node's router id
			printf("%d ", current->router_id);
			
			// Enqueue the left child of this node if it exists
			if (current->left != NULL)
			{
				enqueue(&queue, current->left);
			}
			// Enqueue the right child of this node if it exists
			if(current->right != NULL)
			{
				enqueue(&queue, current->right);
			}
		}
	
		// Print newline to separate lines
		printf("\n");
	}
}


// utility functions
/**
 * Function: createRouter
 * Input argument: router_id - the router's identification
 * Output argument: none
 * Return: a pointer to the recently created router node with no children
 * Dependencies: stdlib.h - malloc
 */
RouterNode* createRouter(int router_id)
{
    // Allocate memory for the new node
    RouterNode* newNode = (RouterNode*)malloc(sizeof(RouterNode));
    // Set the router_id field
    newNode->router_id = router_id;
    // Initialize the left/right pointers to NULL
    newNode->left = NULL;
	newNode->right = NULL;
    // Return the new node
    return newNode;
}


/**
 * Function: createQueue
 * Input argument: none
 * Output argument: none
 * Return: a queue where front and rear pointers are set to NULL
 * Dependencies: none
 */
Queue createQueue()
{
    // Create new queue
    Queue newQueue;
    // Initialize the front to NULL
    newQueue.front = NULL;
    // Initialize the rear to NULL
    newQueue.rear = NULL;
    // Return the new queue
    return newQueue;
}


/**
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a queue
 * Output argument: none
 * Return: true if the queue is empty, false otherwise
 * Dependencies: none
 */
bool isEmptyQueue(Queue* queue)
{
	// Check if both front and rear are null...
    if (queue->front == NULL && queue->rear == NULL)
    {
		// If so, this queue is empty. Return true.
        return true;
    }
	// If not, this queue is not empty. Return false
    return false;
}


/**
 * Function: enqueue
 * Input argument: queue - a pointer to a queue
 *                 router - a pointer to the router node to enqueue
 * Output argument: the router is added at the rear of the queue
 * Return: none
 * Dependencies: stdlib.h - malloc
 */
void enqueue(Queue* queue, RouterNode* router)
{
    // Allocate memory for the new node
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	// Set new node's router value
	newNode->router = router;
	// Set next to NULL, since this will be at the end
	newNode->next = NULL;

	// If the queue is empty, run this:
    if(isEmptyQueue(queue))
    {
		// Set new front to the only node
        queue->front = newNode;
		// Set new rear to the only node
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
 * Input argument: queue - a pointer to a queue
 * Output argument: the front router is removed from the queue
 * Return: a pointer to the dequeued router node (not the queue node!)
 *         NULL if the queue is empty
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
RouterNode* dequeue(Queue* queue)
{
    // Check if queue is empty
    if(isEmptyQueue(queue))
    {
        // If so, return NULL, as we can't dequeue something that
        //doesn't exist
        return NULL;
    }

    // Get address of node to remove
    QueueNode* removeMe = queue->front;
    
    // Get data we need to dequeue
    RouterNode* router = removeMe->router;
    
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
    return router;
}