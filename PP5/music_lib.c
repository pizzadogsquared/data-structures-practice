// header files
#include "music_lib.h"

/**
 * Function: createPlaylist (provided)
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: updated head of the playlist
 * Return: true if the playlist is successfully loaded, false if errors occur
 * Dependencies: addSong, stdio.h, string.h
 */
bool createPlaylist(Song **playlist) 
{
    // open the file
    FILE *file = fopen(FILENAME, "r");
    // if the file could not be open
    if (file == NULL)
    {
        // print a message
        printf("Could not open file %s\n", FILENAME);
        // end the function with an error code
        return false;
    }

    // create variables to hold the readings
    char line[256];
    char title[100];
    char artist[100];
    int genre;

    // if it is the end of the file after the header
    if (fgets(line, sizeof(line), file) == NULL)
    {
        // close the file
        fclose(file);
        // file is empty, return false
        return false;
    }

    // while there is another line to read
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // parse the line using the comma separator
        char *token = strtok(line, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy the data into the title
            strcpy(title, token);
        }
        // move to the next token
        token = strtok(NULL, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy the data into the artist
            strcpy(artist, token);
        }
        // move to the next token
        token = strtok(NULL, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy into genre as an integer
            genre = atoi(token);
        }

        // add the song to the playlist casting Genre to the correct enum
        addSong(playlist, title, artist, (Genre)genre);
    }
    // close the file
    fclose(file);
    // return success
    return true;
}

/**
 * Task 1: Play the Playlist
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h, ctype.h
 */
void play(Song *playlist, char* genres[])
{
    // Initialize index to traverse our linked list
    Song* current = playlist;
    
    // Initialize a limit to the songs played to check if the
    //max number of songs have played
    int songLimit = 0;
    
    // Declare an array to hold user's choice with a comfy buffer
    char choice[STR_LEN];
    
    // Initialize it with first char 'Y' to enter while loop
    choice[0] = 'Y';
    
    // While there are songs to play and we're not out of scope
    while (current != NULL && songLimit < MAX_SONGS
           && toupper(choice[0]) == 'Y')
    {
        //Print a message to the user
        printf("Playing '%s' by '%s' ", current->title, current->artist);
        printf("(Genre: %s)...\n", genres[current->genre]);
        
        //Traverse to the next song in the linked list
        current = current->next;
        
        //Increment our limit until it hits MAX_SONGS
        songLimit++;
        
        //If we've hit our limit
        if(songLimit >= MAX_SONGS)
        {
            //Ask the user and print a message
            printf("Are you still listening [Y|N]? ");
            scanf("%s", choice);
            
            //While the input the user gives is invalid...
            while (toupper(choice[0]) != 'Y' && toupper(choice[0]) != 'N')
            {
                printf("I didn't get that. Please type Y to continue");
                printf(" listening or N to stop: ");
                scanf("%s", choice);
            }
            
            //If the user gives a 'Y', allow them to keep listening
            //by resetting songLimit. If not, the function will exit
            if(toupper(choice[0]) == 'Y')
            {
                // Reset the song limit to 0
                songLimit = 0;
            }
        }
    }
}


/**
 * Task 2: Adding a New Song to the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 *                 artist - a string with the artist of the song
 *                 genre - a Genre enum for the genre of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully added, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */
bool addSong(
    Song **playlist, const char *title, const char *artist, Genre genre)
{
    // Initialize index to traverse the linked list
    Song* current = *playlist;
    
    // Dynamically allocate memory for a new Song struct
    Song* newSong = (Song*) malloc(sizeof(Song));
    
    // If the genre is out of scope, print and return error
    if(genre >= GENRE_COUNT)
    {
        printf("Invalid genre. Song not added. \n");
        return false;
    }
    
    // Otherwise, if the struct was created successfully,
    //this will run
    if (newSong != NULL)
    {
        // Create a title in the struct with the passed title
        strcpy(newSong->title, title);
        
        //Create an artist in the struct with the passed artist
        strcpy(newSong->artist, artist);
        
        //Create a genere in the struct with the passed genre
        newSong->genre = genre;
        
        //This will be the new end of the playlist, so next is NULL
        newSong->next = NULL;
        
        // Check if passed playlist was empty)
        if (current == NULL)
        {
            //We don't have to traverse the list since this is now the head
            *playlist = newSong;
            return true;
        }
        
        //Otherwise, this loop will run
        while (current->next != NULL)
        {
            //Iterate until we are at the last element
            current = current->next;
        }
        // Link the old last's next var to the new last address
        current->next = newSong;
        return true;
    }
    
    //The struct wasn't created successfully, so return false
    return false;
}


/**
 * Task 3: Removing a Song from the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully removed, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */
bool removeSong(Song **playlist, const char *title)
{
    Song* current = *playlist;
    Song* rear = NULL;
    // This while loop will run as long as the list isn't fully
    //traversed or the song hasn't been removed.
    while(current != NULL)
    {
        // If we found a match for song to remove (current) via titles
        if(strcmp(current->title, title) == 0)
        {
            //If the song to remove is the head
            if(current == *playlist)
            {
                // Update the head of the linked list to next song
                *playlist = current->next;
                // Free the old head song
                free(current);
                
                //We successfully removed the song, so return true
                return true;
            }
            //If the song is in any other position
            else
            {
                // Link the "next" address for rear to the current
                //song's next address, effectively cutting current out of
                //the list.
                rear->next = current->next;
                // Free the old head song
                free(current);
                
                //We successfully removed the song, so return true
                return true;
            }
        }
        // If we didn't find a match, continue to traverse the list
        else
        {
            // Set rear to old current
            rear = current;
            // Move current to the next element in linked list
            current = current->next;
        }
    }
    // We fully traversed the list without finding our song to remove,
    //so we return false.
    printf("Song '%s' is not in the list. \n", title);
    return false;
}


/**
 * Task 4: Shuffle Play
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdlib.h, stdio.h
 */
void playShuffle(Song *playlist, char* genres[])
{
    //Init newPlaylist with a null value. We will change this later
    Song* newPlaylist = NULL;
    
    // Moving index for copying passed playlist
    Song* current = playlist;
    
    //Array of pointers that store each element of the playlist
    Song* pointers[MAX_SONGS];
    
    //Movind index for deallocating shuffled playlist
    Song* newCurrent;
    
    // Useful temp value for shuffling and deallocating new playlist
    Song* temp;
    
    //Pointer index that will count through copied list elements
    int pointIndex = 0;
    
    //Rand index that will help with shuffling playlist
    int randIndex = 0;

    
    // Run this if playlist isn't null (empty)
    if(playlist != NULL)
    {
        //Pput the addresses of the linked list in an array
        while(current != NULL)
        {
            //Copy address to the array
            pointers[pointIndex] = current;
            //Increment the pointer array index
            pointIndex++;
            //Move to next element until we reach the end
            current = current->next;
        }
        

        // We should now have an array of pointers to each Song for
        //the copy we want to shuffle.
        //Also, pointIndex + 1 is effectively the pointers[] size.
        
        //Iterate through our array of pointers to shuffle them
        for(int i = 0; i < pointIndex; i++)
        {
            // Get a random value in bounds
            randIndex = rand() % pointIndex;
            // Swap pointers[i] and pointers[randIndex] using temp variable
            temp = pointers[i];
            pointers[i] = pointers[randIndex];
            pointers[randIndex] = temp;
        }
        
        //Build a newPlaylist using our array of pointers
        for(int i = 0; i < pointIndex; i++)
        {
            //Use predefined function addSong()
                //func: addSong()
            addSong(&newPlaylist, pointers[i]->title, 
            pointers[i]->artist, pointers[i]->genre);
        }
        
        //Play our playlist using predefined play() function
            //func: play()
        play(newPlaylist, genres);
        
        // Get new traversing variable for newPlaylist
        newCurrent = newPlaylist;
        // Loop through shuffled list to deallocate
        while(newCurrent != NULL)
        {
            // Set temp to the current element so we don't lose it when
            //traversing
            temp = newCurrent;
            //Traverse to next element in the list, or null if at the end
            newCurrent = newCurrent->next;
            //Free current list element until we reach the end
            free(temp);
        }
    }
    else
    {
        //Print message to the user
        printf("Nothing to be played right now. Add songs to continue.");
    }
}


/**
 * Task 5: Play Songs by Artist
 * Input argument: playlist - a pointer to a list of songs
 *                 artist - a string representing the artist name
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: string.h, stdio.h
 */
void playByArtist(Song *playlist, const char *artist, char* genres[])
{
    // Initialize variable to traverse the linked list
    Song* current = playlist;
    // Check if the playlist is empty
    if(playlist != NULL)
    {
        // While we aren't at the end of the linked list
        while(current != NULL)
        {
            //If our passed artist and current held artist match
            if(strcmp(current->artist, artist) == 0)
            {
                // Print a message to the user
                printf("Playing '%s' by '%s' ",
                current->title, current->artist);
                printf("(Genre: %s)...\n", genres[current->genre]);
            }
            // Traverse tot he next element in the linked list until
            //we reach the end
            current = current->next;
        }
    }
    //Otherwise, print a message to the user
    else
    {
        // Print a message that no artists were found
        printf("Nothing to be played by %s right now. ", artist);
        printf("Add songs to continue. \n");
    }
}


/**
 * Task 6: Sorting the Playlist by Genre
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist sorted by genre
 * Return: void
 * Dependencies: none
 */
void sortByGenre(Song **playlist)
{
    // Initialize an end variable with NULL
    Song* end = NULL;
    
    // Declare next variable to hold the address of the element after the
    //current held one
    Song* next;
    
    // Declare traversal var to hold the address of each element in the
    //linked list
    Song* current;
    
    // Declare a temp string to help swap structs in-place
    //(needed for artist and title swapping)
    char tempStr[STR_LEN];
    
    // Declare a genre variable to swap genres in-place
    Genre tempGenre;
    
    // Swap bool will help escape the loop as soon as the list is
    //traversed without swapping any structs
    bool swap = true;
    
    //If the playlist isn't empty
    if(*playlist != NULL)
    {
        // While the previous loop had swapped structs
        while(swap)
        {
            // Initialize next while loop iteration with a false swap.
            //The loop will escape when this is unchanged
            swap = false;
            
            // Set the current value back to the head
            current = *playlist;
            
            //While the next element isn't the end
            while(current->next != end)
            {
                next= current->next;
                
                // If current element is greater than next
                //(Two adjacent elements are unsorted)
                if(current->genre > next->genre)
                {
                    //Swap the title of the adjacent elements
                    strcpy(tempStr, current->title);
                    strcpy(current->title, next->title);
                    strcpy(next->title, tempStr);
                    
                    //Swap the artist of the adjacent elements
                    strcpy(tempStr, current->artist);
                    strcpy(current->artist, next->artist);
                    strcpy(next->artist, tempStr);
                    
                    //Swap the gener of the adjacent elements
                    tempGenre = current->genre;
                    current->genre = next->genre;
                    next->genre = tempGenre;
                    
                    // We swapped in this loop, so set the bool to true
                    swap = true;
                }
                // Traverse to the next element in the list
                current = current->next;
            }
            // Move end marker back once because one more element is sorted
            end = current;
        }
        
        //Print message to the user.
        printf("Playlist will play by genre from here on!\n");
    }
    else
    {
        //Print a message to the user
        printf("It is quiet here. Add songs to continue.\n");
    }
}


/**
 * Task 7: Detecting a Cycle in the Playlist
 * Input argument: playlist - a pointer to a list of songs
 * Output argument: none
 * Return: true if the last song points to the head of the playlist,
 *         false otherwise
 * Dependencies: none
 */
bool detectCycle(Song *playlist)
{
    //Initialize current index to playlist head
    Song* current = playlist;
    
    //While we're not at the end of the playlist
    //(loop will break if the loop is continuous anyways)
    while(current != NULL)
    {
        //If the head pointer is detected in next, the list is
        //circular.
        if(current->next == playlist)
        {
            return true;
        }
        //Keep traversing either until the end of the playlist
        //is found, or the head pointer is found
        current = current->next;
    }
    
    //At this point, we've fully traversed the list until the end,
    //so it is not circular.
    return false;
}


/**
 * Task 8: Play Non-Stop
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be circular
 * Return: void
 * Dependencies: detectCycle
 */
void makePlaylistCircular(Song **playlist)
{
    //Initialize current index to playlist head
    Song* current = *playlist;
    //Check if playlist is empty
    if (current == NULL)
    {
        //Print message to the user
        printf("It is quiet here. Add songs to continue.\n");
    }
    //Check if the playlist is already circular
    else if(detectCycle(*playlist))
    {
        //Print message to the user
        printf("Music is already playing continuously!\n");
    }
    else
    {
        //While we're not at the end of the playlist
        while(current->next != NULL)
        {
            // Traverse so our current pointer will hold the last
            //list element address
            current = current->next;
        }
        
        //Make playlist circular by changing next from NULL to
        //link back to start
        current->next = *playlist;

        //Print a message to the user
        printf("Music will play continuously from here on!\n");
    }
}

/**
 * Task 9: Play Up to the End
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be linear (last points to null)
 * Return: void
 * Dependencies: detectCycle
 */
void makePlaylistLinear(Song **playlist)
{
    //Initialize current index to playlist head
    Song* current = *playlist;
    //Check if playlist is empty
    if (current == NULL)
    {
        //Print message to the user
        printf("It is quiet here. Add songs to continue.\n");
    }
    //Check if the playlist is already linear (opposite of circular)
    else if(!(detectCycle(*playlist)))
    {
        //Print message to the user
        printf("Music is already playing up to the last song!\n");
    }
    else
    {
        //While we're not at the circular point of playlist
        //(next points to head)
        while(current->next != *playlist)
        {
            // Traverse so our current pointer will hold the last
            //list element address before repeat
            current = current->next;
        }
        
        // Make playlist linear by changing next from head
        //to NULL
        current->next = NULL;
        
        //Print a message to the user
        printf("Music will stop playing when the playlist is over!\n");
    }
}


/**
 * Task 10: Reversing the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is reversed
 * Return: void
 * Dependencies: detectCycle
 */
void reversePlaylist(Song **playlist)
{
    // Initialize a rear and next value for traversing our
    //linked list
    Song* rear = NULL;
    Song* next = NULL;
    Song* current = *playlist;
    
    while(current != NULL)
    {
        //Get next node and store it
        next = current->next;
        
        // Have the current node point to the one
        //before it rather than the next one.
        //(This is why we need to stash next)
        current->next = rear;
        
        // MOve rear one position up
        rear = current;
        
        //Move current one position up
        current = next;
    }
    
    // Change the head to what was the last element, which is now the
    //first element.
    *playlist = rear;
    
}

