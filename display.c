#include "main.h"

/*
 * Function: Display_database
 * 1. Check if the database has been created,If not, print an error message and return.
 * 2. Print the header for the database display table.
 * 3. Loop through each index of the hash table:
 * 4. If the Mlink (main node link) of the current hash index is not NULL:
 * 5. If no main node exists at the current index, continue to the next index.
 * This function displays the entire database, showing the words stored in each hash table index, 
 * along with the associated files and word counts. It traverses the linked lists of main nodes and sub-nodes 
 * and prints their data in a tabular format.
 */
void Display_database(Hash *hash, int size, int created)
{
    /* Validate the hash table created or not */
    if (created != 0)
    {
        printf("database not created ");
        return;
    }
    /* Date printing format */
    printf("[index]\t[word] \t-> File_Count\tFile/s:\t| Fname [WCount] |\n");
    printf("---------------------------------------------------------------------\n");
    
    /* run lopp for size times */
    for (int i = 0; i < size; i++) 
    {
	/* Check hash table is not empty */
        if (hash[i].Mlink != NULL)
        {
            mainNode *tempMnode = hash[i].Mlink; 
	    
	    /* run loop till last node of each index */
            while (tempMnode != NULL)  
            {

                subNode *tempSnode = tempMnode->Slink;   
                printf("[%d]\t%s\t->\t%d\tFile/s: ", hash[i].idx, tempMnode->word, tempMnode->fileCount);
                
		/* run loop till each last file of each node */
		while (tempSnode != NULL)  
                {
                    printf("| %s\t[%d] |", tempSnode->fileName, tempSnode->wordCount);
                    tempSnode = tempSnode->Slink;
                }
                tempMnode = tempMnode->Mlink;
                if (tempSnode == NULL)
                    printf("\n");
            }
        }
    }
}  
