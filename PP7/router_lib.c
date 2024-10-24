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



/**
 * Task 3: Invert Router Network
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: the pointer to the root node, where the tree's left and right sides 
 *          are swapped
 * Dependencies: invertNetwork (recursive)
 */



/**
 * Task 4: Ensure Symmetrical Routing
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: true if the routing is symmetric, false otherwise
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 */



/**
 * Task 5: Analyze Maximum Network Depth
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: an integer value representing the maximum depth of the tree
 * Dependencies: getMaxNetworkDepth (recursive)
 */



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



/**
 * Function: findHighTrafficRouters
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: createQueue, enqueue, dequeue, isEmptyQueue
 *               stdio.h - printf
 */



/**
 * Task 8: Show Routers
 * Input argument: root - a pointer to the root of the network
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h - printf
 */



// utility functions
/**
 * Function: createRouter
 * Input argument: router_id - the router's identification
 * Output argument: none
 * Return: a pointer to the recently created router node with no children
 * Dependencies: stdlib.h - malloc
 */



/**
 * Function: createQueue
 * Input argument: none
 * Output argument: none
 * Return: a queue where front and rear pointers are set to NULL
 * Dependencies: none
 */



/**
 * Function: isEmptyQueue
 * Input argument: queue - a pointer to a queue
 * Output argument: none
 * Return: true if the queue is empty, false otherwise
 * Dependencies: none
 */



/**
 * Function: enqueue
 * Input argument: queue - a pointer to a queue
 *                 router - a pointer to the router node to enqueue
 * Output argument: the router is added at the rear of the queue
 * Return: none
 * Dependencies: stdlib.h - malloc
 */



/**
 * Function: dequeue
 * Input argument: queue - a pointer to a queue
 * Output argument: the front router is removed from the queue
 * Return: a pointer to the dequeued router node (not the queue node!)
 *         NULL if the queue is empty
 * Dependencies: isEmptyQueue
 *               stdlib.h - free
 */
