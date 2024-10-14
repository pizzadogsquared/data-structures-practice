// header files
#include "text_editor_lib.h"

// main program
int main() 
{
    // create a text editor
    TextEditor editor;
    // initialize the text editor
    initEditor(&editor);
    // declare supporting variables
    int i, k, choice = 0;
    // declare a character array to store user input text
    char text[MAX_TEXT];
    // begin loop
    do
    {
        // print the menu options
        printf("\n1. Add Text\n");
        printf("2. Delete Text (Backspace)\n");
        printf("3. Move Cursor Left\n");
        printf("4. Move Cursor Right\n");
        printf("5. Find and highlight the text\n");
        printf("6. Display Text\n");
        printf("7. Exit\n");

        // prompt user to enter a choice
        printf("Enter choice: ");
        // read user's choice
        scanf("%d", &choice);
        // consume the newline character
        getchar();
        // switch case to handle user's choice
        switch (choice) 
        {
            // case 1: add text to the editor
            case 1:
                printf("Enter text: ");
                // read the full line including spaces
                fgets(text, sizeof(text), stdin);

                // manually remove the newline character if present in the input
                    // create an index variable
                i = 0;
                    // while it is not the end of the string and
                    //   the character is not the newline character
                while(i < sizeof(text) && text[i] != '\n')
                {
                    // move to the next i
                    i++;
                }
                // if current character is newline
                if (text[i] == '\n')
                {
                    // replace newline with null terminator
                    text[i] = '\0';
                }
                // add the text at the cursor position
                addText(&editor, text);
                // end case
                break;

            // case 2: delete text (backspace functionality)
            case 2:
                // prompt for the number of characters
                printf("Enter number of characters to delete: ");
                // read the number of characters to delete from the user
                scanf("%d", &k);
                // delete k characters to the left of the cursor
                deleteText(&editor, k);
                // end case
                break; 

            // case 3: move the cursor left
            case 3:
                // prompt for the number of characters
                printf("Move cursor left by: ");
                // read the number of positions to move the cursor left
                scanf("%d", &k);
                // move the cursor left by k positions
                cursorLeft(&editor, k);
                // end case
                break;

            // case 4: move the cursor right
            case 4:
                // prompt for the number of characters
                printf("Move cursor right by: ");
                // read the number of positions to move the cursor right
                scanf("%d", &k);
                // move the cursor right by k positions
                cursorRight(&editor, k);
                // end case
                break;

            // case 5: find and highlight text in the editor
            case 5:
                // prompt for the string to highlight
                printf("Enter the text to search and highlight: ");
                // read the text to search for from the user
                fgets(text, sizeof(text), stdin);
                // manually remove the newline character if present in the input
                    // create an index variable
                i = 0;
                    // while it is not the end of the string and
                    //   the character is not the newline character
                while(i < sizeof(text) && text[i] != '\n')
                {
                    // move to the next i
                    i++;
                }
                // if current character is newline
                if (text[i] == '\n')
                {
                    // replace newline with null terminator
                    text[i] = '\0';
                }
                // call the function to find and highlight the text
                findAndHighlight(&editor, text);
                // end case
                break;

            // case 6: display the current text in the editor
            case 6:
                // call the function to display the text with cursor position
                displayText(&editor);
                // end case
                break;

            // case 7: exit the program
            case 7:
                // print a message
                printf("Exiting...\n");
                // end case
                break;
            // default case: handle invalid user input
            default:
                // print a message
                printf("Invalid choice.\n");
                // end case
                break;
        }
    }
    // while user did not choose exit
    while (choice != 7);
    // return success
    return 0;
}
