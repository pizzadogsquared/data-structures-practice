#ifndef TEXT_EDITOR_LIB_H
#define TEXT_EDITOR_LIB_H

// header files
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// global definitions
#define MAX_TEXT 100

// data types
typedef struct Node 
{
    char data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct TextEditor
{
    Node* head; 
    Node* tail; 
    Node* cursor;
} TextEditor;

// function prototypes
/**
 * Function: createNode (provided)
 * Input argument: data - a character to include in the node
 * Output argument: none
 * Return: a pointer to the newly created node
 * Dependencies: stdlib.h
 */
Node* createNode(char data);

/**
 * Function: initEditor (provided)
 * Input argument: editor - a pointer to the editor
 * Output argument: an initialized editor
 * Return: none
 * Dependencies: 
 */
void initEditor(TextEditor* editor);

/**
 * Function: addText
 * Input argument: editor - a pointer to the editor
 *                 text - a constant with the string to add to the text
 * Output argument: the editor with updated text
 * Return: none
 * Dependencies: createNode
 */
void addText(TextEditor* editor, const char* text);

/**
 * Function: deleteText
 * Input argument: editor - a pointer to the editor
 *                 k - the number of characters to delete
 * Output argument: the editor with updated text
 * Return: none
 * Dependencies: free
 */
void deleteText(TextEditor* editor, int k);

/**
 * Function: cursorLeft
 * Input argument: editor - a pointer to the editor
 *                 k - the number of characters to move
 * Output argument: the editor with updated cursor
 * Return: none
 * Dependencies: none
 */
void cursorLeft(TextEditor* editor, int k);

/**
 * Function: cursorRight
 * Input argument: editor - a pointer to the editor
 *                 k - the number of characters to move
 * Output argument: the editor with updated cursor
 * Return: none
 * Dependencies: none
 */
void cursorRight(TextEditor* editor, int k);

/**
 * Function: displayText
 * Input argument: editor - a pointer to the editor
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h
 */
void displayText(const TextEditor* editor);

/**
 * Function: findAndHighlight
 * Input argument: editor - a pointer to the editor
 *                 searchText - a string with the text to search
 * Output argument: none
 * Return: none
 * Dependencies: string.h, stdio.h
 */
void findAndHighlight(TextEditor* editor, const char* text);

#endif  // TEXT_EDITOR_LIB_H
