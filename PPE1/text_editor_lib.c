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
	int textSize = sizeof(text)/sizeof(text[0]);
	
	// Iterate through the length of the string
	for (int i = 0; i < textSize; i++)
	{
		// Create a new node for the current character
		Node* newChar = createNode(text[i]);
		Node* behindCursor = editor->cursor->prev
		//Link the cursor's prev to the address of newChar
		behindCursor = newChar;
		
		behindCursor->next = newChar;
		//Link newChar to 
		newChar->prev = behindCursor;
		newChar->next = editor->cursor;
	
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
	for (int i = 0; i < k; i++)
	{
		Node* deleteMe = editor->prev;
		
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



/**
 * Task 4: Moving the Cursor Right
 * Input argument: editor - a pointer to the editor
 *                 k - the number of characters to move
 * Output argument: the editor with updated cursor
 * Return: none
 * Dependencies: none
 */



/**
 * Task 5: Displaying the Entire Text
 * Input argument: editor - a pointer to the editor
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */



/**
 * Task 6: Find and highlight the text
 * Input argument: editor - a pointer to the editor
 *                 searchText - a string with the text to search
 * Output argument: none
 * Return: none
 * Dependencies: string.h, stdio.h
 */

