// header files
#include "text_editor_lib.h"

/**
 * Function: createNode (provided)
 * Input argument: data - a character to include in the node
 * Output argument: none
 * Return: a pointer to the newly created node
 * Dependencies: stdlib.h
 */
Node* createNode(char data)
{
    // allocate memory for the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    // set the character data for the node
    newNode->data = data;
    // initialize the previous pointer as NULL
    newNode->prev = NULL;
    // initialize the next pointer as NULL
    newNode->next = NULL;
    // return the newly created node
    return newNode;  
}

/**
 * Function: initEditor (provided)
 * Input argument: editor - a pointer to the editor
 * Output argument: an initialized editor
 * Return: none
 * Dependencies: 
 */
void initEditor(TextEditor* editor) 
{
    // initialize the head of the list with a null-terminator to the left
    editor->head = createNode('\0');
    // initialize the head of the list with a null-terminator to the right
    editor->tail = createNode('\0');
    // link the head and tail
    editor->head->next = editor->tail;
    editor->tail->prev = editor->head;
    // initialize the cursor as the tail
    //  so the cursor points to the the last valid position
    editor->cursor = editor->tail;
}

/**
 * Task 1: Adding Text at the Cursor Position
 * Input argument: editor - a pointer to the editor
 *                 text - a constant with the string to add to the text
 * Output argument: the editor with updated text
 * Return: none
 * Dependencies: createNode
 */
void addText(TextEditor* editor, const char* text)
{
    // Get the size of the passed string
    int textSize = strlen(text);
    
    // Iterate through the length of the string
    for(int i = 0; i < textSize; i++)
    {
        // Create a new node for the current character
        Node* newChar = createNode(text[i]);
        
        
        // Store the address of the node behind the cursor
        Node* behindCursor = editor->cursor->prev;
        
        // Set previous cursor's next value to add of newChar (if prev exists)
        if (behindCursor != NULL)
        {
            
            //Link the next value
            behindCursor->next = newChar;
        }
        // Set newChar's prev value to address of behindCursor
        newChar->prev = behindCursor;
        
        // Set newChar's next to the cursor
        newChar->next = editor->cursor;
        // Set cursor's prev value to newChar
        editor->cursor->prev = newChar;
    }
}


/**
 * Task 2: Deleting Text with Backspace Behavior
 * Input argument: editor - a pointer to the editor
 *                 k - the number of characters to delete
 * Output argument: the editor with updated text
 * Return: none
 * Dependencies: free
 */
void deleteText(TextEditor* editor, int k)
{
    //Iterate through how many chars the user wants to delete (k)
    for (int i = 0; i < k; i++)
    {
        // Get the address of the node to delete
        Node* deleteMe = editor->cursor->prev;
        
        if(deleteMe->prev != NULL)
        {
            // Have the node before deleteMe change its next to point
            //to the cursor now instead
            deleteMe->prev->next = editor->cursor;
            
            // Have the cursor's previous value point to the node
            //before deleteMe
            editor->cursor->prev = deleteMe->prev;
            
            //Free deleteMe so that we aren't using up unnecessary memory
            free(deleteMe);
        }
    }
}


/**
 * Task 3: Moving the Cursor Left
 * Input argument: editor - a pointer to the editor
 *                 k - the number of characters to move
 * Output argument: the editor with updated cursor
 * Return: none
 * Dependencies: none
 */
void cursorLeft(TextEditor* editor, int k)
{
    // Iterate through how many nodes the user wants to traverse
    //to the left with
    for (int i = 0; i < k; i++)
    {
        // Store the address of the current node to the left of the cursor
        Node* prevNode = editor->cursor->prev;

        // Check if the previous node has reached the start
        if (prevNode != editor->head)
        {
            // If not, then traverse 1 node to the left
            editor->cursor = prevNode;
        }
    }    
}


/**
 * Task 4: Moving the Cursor Right
 * Input argument: editor - a pointer to the editor
 *                 k - the number of characters to move
 * Output argument: the editor with updated cursor
 * Return: none
 * Dependencies: none
 */
void cursorRight(TextEditor* editor, int k)
{
    // Iterate through how many nodes the user wants to traverse
    //to the right with
    for (int i = 0; i < k; i++)
    {
        //Store the address of the current node to the right of the cursor
        Node* nextNode = editor->cursor->next;
        
        // Check if next node has reached the end of the list
        if(nextNode != NULL)
        {
            //If not, traverse 1 node to the right
            editor->cursor = nextNode;
        }
    }
}


/**
 * Task 5: Displaying the Entire Text
 * Input argument: editor - a pointer to the editor
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void displayText(const TextEditor* editor)
{
    // Get the head node
    Node* start = editor->head;
    
    // Initialize current node to traverse the deque,
    //starting at the left
    Node* current = start;
    
    // Traverse the whole deque from start to end
    while(current->next != NULL)
    {
        // Check if the current held value is the cursor
        if(current == editor->cursor)
        {
            // If so, print a cursor indicator before printing our char
            printf("|");
        }
        
        //Print the character of the current held pointer
        printf("%c", current->data);
        
        // Traverse to next item in the deque
        current = current->next;
    }
    
    // If the cursor is at the end, print it
    if(editor->cursor == editor->tail)
    {
        // Print cursor indicator
        printf("|");
    }
    
    //Print a newline char
    printf("\n");
}


/**
 * Task 6: Find and highlight the text
 * Input argument: editor - a pointer to the editor
 *                 searchText - a string with the text to search
 * Output argument: none
 * Return: none
 * Dependencies: string.h, stdio.h
 */
void findAndHighlight(TextEditor* editor, const char* text)
{
    // Initialize start pointer for head
    Node* start = editor->head;
    // Initialize current pointer to traverse the deque from left to right
    Node* current = start;
    // Initialize a helper var to hold the size of the passed text to
    //search for
    int textSize = strlen(text);
    // Initialize an array to hold the pointers of our matched search
    Node* textArray[textSize];
    
    // Initialize an index to iterate through textArray
    int textIndex = 0;
    // Initialize a variable to indicate if we've successfully found abort
    //match in the search
    bool foundText = false;
    
    // If the user didn't enter a search...
    if(textSize == 0)
    {
        // Print this message to the user
        printf("Invalid search text. Please provide a text to search for.");
    }
    // If the user DID enter a valid search
    else
    {
        // Traverse the deque while we haven't found a match
        while(current != editor->tail && !foundText)
        {
            // If the current value matches a sequential part of our search
            if(current->data == text[textIndex] )
            {
                // Assign it to our array of pointers
                textArray[textIndex] = current;
                // Increment the index
                textIndex++;
                
                // If our textIndex matches the size of our text, then we've
                //found a full match
                if(textIndex == textSize)
                {
                    // Update our bool to indicate this
                    foundText = true;
                }
            }
            else
            {
                // If at any point in our sequential matching process,
                //we find a mismatched char, reset the textIndex.
                textIndex = 0;
            }
            
            // Traverse to the next address in the deque
            current = current->next;
        }
    
        // If we haven't found our match...
        if(!foundText)
        {
            // Print a message to the user.
            printf("String is not found in the text. Please try again.");
        }
        // If we HAVE found our match
        else
        {
            // Re-init current pointer
            current = start;
            // Reset textIndex int
            textIndex = 0;
            // Iterate through the deque again to start the
            //printing process
            while(current != editor->tail)
            {
                // If we've found the start of our match...
                if(current == textArray[0])
                {
                    // Start our highlight in the output
                    printf("[");
                }
                
                // Print the current char to the user.
                printf("%c", current->data);
                
                // If we've found the end of our match...
                if(current == textArray[textSize - 1])
                {
                    // End our highlight in the output
                    printf("]");
                }
                // Traverse to the next pointer in the deque
                current = current->next;
            }
        }
    }
    
    // Print a newline char here so I don't have to type it in all of
    //the printfs
    printf("\n");
}
