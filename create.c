#include "main.h"

/*
 * Function: create_hash_table
 * 1. Loop through the array of hash nodes from 0 to size-1.
 * 2. Initialize each hash node's index with the loop counter (i).
 * 3. Set the Mlink pointer of each hash node to NULL, indicating no mainNode is yet attached.
 * 4. Return SUCCESS (assumed to be a macro defined as 0 or some success value).
 * Initializes a hash table with a specified size, where each entry points to
 * the start of a linked list of main nodes. Each main node represents a word
 * found in files.
 */
int create_hash_table(Hash *hash, int size) 
{
    /* run loop for size times */
    for (int i = 0; i < size; i++)
    {
        hash[i].idx = i;    
        hash[i].Mlink = NULL; 
    }
    return SUCCESS;
}

/*
 * Function: create_Snode
 * 1. Allocate memory for a new subNode.
 * 2. If allocation fails, print an error message.
 * 3. Initialize the word count to 1, assign the file name, and set the Slink to NULL.
 * 4. If the previous subNode pointer is NULL, this new subNode becomes the first subNode.
 * 5. If the previous subNode exists, link it to this new subNode.
 * Creates a new sub-node that holds information about a specific occurrence
 * of a word in a file. It updates the linked list of sub-nodes.
 */
int create_Snode(subNode **prevSnode, char *file_name)  
{
    /* Create new node and validate memory allocation */
    subNode *Snew = malloc(sizeof(subNode));
    if (Snew == NULL)
        printf("Sub node not created.\n");
    /* Assign all data */
    Snew->wordCount = 1;
    Snew->fileName = file_name;
    Snew->Slink = NULL;

    /* Link the node */
    if (*prevSnode == NULL)
    {
        *prevSnode = Snew;
    }
    else
    {
        (*prevSnode)->Slink = Snew;
    }
}

/*
 * Function: create_Mnode
 * 1. Allocate memory for a new mainNode.
 * 2. If allocation fails, print an error message.
 * 3. Allocate memory for the word and copy it to the mainNode.
 * 4. Initialize the file count to 1, set Mlink and Slink pointers to NULL.
 * 5. Create a sub-node linked to this main node to track the word's occurrence in the file.
 * 6. If the previous mainNode is NULL, this new mainNode becomes the first mainNode.
 * 7. If the previous mainNode exists, link it to this new mainNode.
 * Creates a new main-node that represents a word and its occurrences in different
 * files. It updates the linked list of main-nodes in the hash table.
 */
int create_Mnode(mainNode **prevMnode, char *file_name, char *word) 
{
    /* Create new node and validate the memory allocation */
    mainNode *Mnew = malloc(sizeof(mainNode));
    if (Mnew == NULL)
        printf("Main node not created.\n");

    /* Assign the data */
    Mnew->fileCount = 1;
    Mnew->word = malloc(strlen(word) + 1);
    if (Mnew->word == NULL)
        printf("Memory for word not allocated.\n");
    
    /* Copy word to node */
    strcpy(Mnew->word, word);
    Mnew->Mlink = NULL;
    Mnew->Slink = NULL;
    create_Snode(&Mnew->Slink, file_name);
    
    /* Link the node*/
    if (*prevMnode == NULL)
    {
        *prevMnode = Mnew;
    }
    else
    {
        (*prevMnode)->Mlink = Mnew;
    }
}

/*
 * Function: add_word
 * 1. Compute the index in the hash table based on the first letter of the word.
 * 2. If the Mlink in the hash table entry is NULL, create a new mainNode.
 * 3. Otherwise, traverse the linked list of mainNodes:
 *    a. If the word is found, traverse the subNode list to find the file name.
 *    b. If the file is found, increment the word count.
 *    c. If the file is not found, create a new subNode.
 * 4. If the word is not found, create a new mainNode.
 * Description:
 * Adds a word to the hash table. If the word already exists, it updates the 
 * corresponding mainNode and subNode. If the word doesn't exist, it creates 
 * a new mainNode and subNode.
 */
void add_word(Hash *hash, char *file_name, char *word)  
{
    /* Check the index */
    int idx = tolower(word[0]) - 97;    
    if (hash[idx].Mlink == NULL)    
    {
	/* create node */
        create_Mnode(&hash[idx].Mlink, file_name, word); 
    }
    else
    {
	/* take variables */
        int flagW = 0, flagF = 0;
        mainNode *tempMnode = hash[idx].Mlink;  
        mainNode *prevMnode = NULL;

	/* rum loop till last node */
        while (tempMnode != NULL) 
        { 
	    /* compare each node word with current word */
            if (strcmp(tempMnode->word, word) == 0) 
            {
		/* teke temparary variables */
                flagW = 1;
                subNode *tempSnode = tempMnode->Slink;
                subNode *prevSnode = NULL;
		
		/* run loop till last node */
                while (tempSnode != NULL)  
                {
		    /* compare each node file name with current file name */
                    if (strcmp(tempSnode->fileName, file_name) == 0) 
                    {
			/* if same file then increment the word count */
                        tempSnode->wordCount++;
                        flagF = 1;
                        break;
                    }
                    prevSnode = tempSnode;
                    tempSnode = tempSnode->Slink;
                }

                if (flagF == 0)
                {
		    /* if different file name then create the new sub node */
                    tempMnode->fileCount++;
                    create_Snode(&prevSnode, file_name);
                }

                break;
            }
            prevMnode = tempMnode;
            tempMnode = tempMnode->Mlink;
        }

        if (flagW == 0)
        {
	    /* if new word the create the new main node */
            create_Mnode(&prevMnode, file_name, word);
        }
    }
}

/*
 * Function: Create_database
 * 1. Create and initialize a hash table.
 * 2. Traverse through the list of files:
 *    a. Open each file.
 *    b. Read each word in the file.
 *    c. Add the word to the hash table using add_word.
 *    d. Close the file after reading.
 * 3. Print a confirmation message for each file processed.
 * Creates a database by reading words from a list of files and adding them to
 * a hash table. Each word's occurrences are tracked across multiple files.
 */
void Create_database(Hash *hash, FILE_LIST *flist, int size)  
{
    /* Create hash table */
    if (!create_hash_table(hash, size))        
        printf("Hash Table not created successfully.\n");

    /* take list for files */
    FILE_LIST *file = flist;

    /* run loop till file reaches the null means all files in a list */
    while (file != NULL)  
    {
	/* take file pointer for each files open in read mode and validate file opening */
        FILE *fptr = fopen(file->name, "r");  
        if (fptr == NULL)
            printf("File not opened.\n");

        char word[20];
	/* run loop and  take each word from the file */
        while (fscanf(fptr, "%s", word) != EOF)
        { 
            char *ptr = word;
	    /* add each word to hash table */
            add_word(hash, file->name, ptr);   
        }
        printf("\nDatabase for this file (%s) created.", file->name);
        fclose(fptr);     
        file = file->link;
    }
    printf("\n");
}  
