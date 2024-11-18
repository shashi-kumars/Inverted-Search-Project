#include "main.h"

/*
 * Function: Search_database
 * 1. Check if the database has been created (using the `created` flag).
 * 2. Prompt the user to enter a word to search in the database.
 * 3. Compute the hash index for the word based on its first character.
 * 4. Check if the hash table entry at the computed index has any mainNode linked to it:
 *    a. If no mainNode is linked, print an error message and return FAILURE.
 * 5. Traverse the linked list of mainNodes at the computed index:
 *    a. Compare each mainNode's word with the user-input word.
 *    b. If a match is found, print the number of files the word is present in.
 *    c. Traverse the subNode list of that mainNode and print the file name and 
 *       word count for each subNode.
 *    d. Return SUCCESS once the word is found and its details are printed.
 * 6. If the word is not found after traversing the entire list, print an error message 
 *    indicating that the word is not present in the database.
 * 7. Return FAILURE if the word is not found.
 *
 * Searches for a word in the hash table (database) and prints the files in which
 * the word is present along with the count of occurrences in each file. If the word
 * is not found, it prints an appropriate message.
 */
int Search_database(Hash *hash, int created) 
{
    /* check database is created or not */
    if (created != 0)
    {
        printf("Database not created.\n");
        return FAILURE;
    }

    char word[10];
    /* read word that want to be searched */
    printf("Enter the word to be searched in database: ");
    scanf("%s", word);

    /* Find the index of the word based on its first letter */
    int idx = tolower(word[0]) - 97;  
    
    /* Check if that index link is not null (i.e., no mainNode exists) */
    if (hash[idx].Mlink == NULL)  
    {
        printf("Database for that index is empty.\n");
        return FAILURE;
    }

    mainNode *tempMnode = hash[idx].Mlink;
    
    /* Traverse each mainNode and compare word with the input word */
    while (tempMnode != NULL)
    {
        if (strcmp(word, tempMnode->word) == 0) 
        {
            printf("\nWord (%s) is present in %d file(s)", tempMnode->word, tempMnode->fileCount);
            
            subNode *tempSnode = tempMnode->Slink;
            /* treversing each sub nodes for word count */
	    while (tempSnode != NULL)
            {
                printf("\nIn file (%s) %d time(s)\n", tempSnode->fileName, tempSnode->wordCount);
                tempSnode = tempSnode->Slink;
            }
            return SUCCESS;
        }
        tempMnode = tempMnode->Mlink;
    }

    printf("Entered word not present in database.\n");
    return FAILURE;
}
