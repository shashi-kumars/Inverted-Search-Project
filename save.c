#include "main.h"

/*
 * Function: Save_database
 * 1. Check if the database has been created (using the `created` flag).
 *    a. If not created, print an error message and return FAILURE.
 * 2. Open the destination file in write mode.
 *    a. If the file cannot be opened, print an error message and return FAILURE.
 * 3. Loop through each index of the hash table:
 *    a. If the `Mlink` at the current index is not NULL, traverse the linked list of mainNodes.
 *    b. For each mainNode, write its index, word, and file count to the destination file.
 *    c. Traverse the linked list of subNodes for that mainNode and write each file name and word count to the file.
 *    d. After writing the data for each mainNode, move to the next mainNode.
 * 4. After processing all indices in the hash table, close the file.
 * 5. Return SUCCESS to indicate the database was successfully saved to the file.
 *
 * Saves the entire database (hash table) to a specified file. The database is written in a structured format
 * where each line represents a mainNode and its corresponding subNodes, including the index, word, file count,
 * file names, and word counts.
 */
int Save_database(Hash *hash, int size, char *dest_file, int created) 
{
    /* Check database is created or not */
    if (created != 0)
    {
        printf("Database not created.\n");
        return FAILURE;
    }

    /* Open backup file in write mode and validate file opening */
    FILE *fptr = fopen(dest_file, "w");
    if (fptr == NULL)
    {
        printf("Destination file unable to open.\n");
        return FAILURE;
    }

    for (int i = 0; i < size; i++)
    {
	/* check each index node is not null */
        if (hash[i].Mlink != NULL)
        {
            mainNode *tempMnode = hash[i].Mlink;
	    /* traversing each node */
            while (tempMnode != NULL) 
            {
                subNode *tempSnode = tempMnode->Slink;
                /* Write the index, word, and file count into the file */
                fprintf(fptr, "#%d;%s;%d;", hash[i].idx, tempMnode->word, tempMnode->fileCount);
                /* treversing each subnode */
		while (tempSnode != NULL)
                {
                    /* Write the file name and word count into the file */
                    fprintf(fptr, "%s;%d;", tempSnode->fileName, tempSnode->wordCount);
                    tempSnode = tempSnode->Slink;
                }
                fprintf(fptr, "#\n");
                tempMnode = tempMnode->Mlink;
            }
        }
    }
    
    fclose(fptr);
    return SUCCESS;
}
