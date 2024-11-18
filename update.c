#include "main.h"

/* Take file pointer */
FILE *fptr = NULL;

/*
 * Function: file_Exist
 * 1. Attempt to open the specified file in read mode.
 * 2. If the file is opened successfully, return SUCCESS.
 * 3. If the file cannot be opened, return FAILURE.
 * This function checks whether the specified file exists by attempting to open it in read mode.
 */
int file_Exist(char *file_name) 
{
    /* open file in read mode and check file existence */
    fptr = fopen(file_name, "r");
    if (fptr != NULL)
    {
	return SUCCESS;
    }
    else
    {
	return FAILURE;
    }
}

/*
 * Function: file_Content
 * 1. Move the file pointer to the end of the file using fseek().
 * 2. Measure the file size using ftell().
 * 3. Close the file.
 * 4. If the file size is greater than 1 byte, return SUCCESS.
 * 5. Otherwise, return FAILURE.
 * This function checks whether the specified file has content by measuring its size.
 */
int file_Content(char *file_name)  
{
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    fclose(fptr);
    /* check file has content */
    if (size > 1)
	return SUCCESS;
    else
	return FAILURE;
}

/*
 * Function: valid_data
 * 1. Open the file in read mode and determine its size.
 * 2. Rewind the file pointer to the beginning.
 * 3. Check the first character of the file:
 *    a. If it is '#', continue to read the line.
 *    b. If a second '#' is encountered on the same line, mark the file as valid.
 * 4. If the file is not marked as valid, print an error message and return FAILURE.
 * 5. Return SUCCESS if the file contains valid data.
 * This function checks if the file has valid backup data by ensuring the correct format is present.
 */
int valid_data(char *file_name)  
{

    fptr = fopen(file_name, "r");
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    rewind(fptr);

    char ch, flag = 0;
    /* Check the file has data in proper format */
    if ((ch = fgetc(fptr)) == '#')
    {
	while ((ch = fgetc(fptr)) != '\n')
	{
	    if (ch == '#')
	    {
		flag = 1;
		break;
	    }
	}
    }

    if (flag == 0)
    {
	printf("\nProvided file \"%s\" is not a backup file\n", file_name);
	return FAILURE;
    }

    return SUCCESS;
}

/*
 * Function: validate_file
 * 1. Check if the provided file has a ".txt" extension.
 * 2. If it does, check if the file exists using file_Exist().
 * 3. If the file exists, check if it has content using file_Content().
 * 4. If the file has content, check if the content is valid using valid_data().
 * 5. Return SUCCESS if all checks pass; otherwise, print appropriate error messages and return FAILURE.
 * This function validates the destination file by checking its existence, content, and validity.
 */
int validate_file(char *dest_file)  
{
    /* Check file is text file */
    if (strstr(dest_file, ".txt"))
    {
	/* Check file is existing */
	if (file_Exist(dest_file) == SUCCESS)
	{
	    /* check file is not empty */
	    if (file_Content(dest_file) == SUCCESS)
	    {
		/* check file has valid content */
		if (valid_data(dest_file) == SUCCESS)
		{
		    return SUCCESS;
		}
		else
		{
		    printf("This file (%s) has no valid data.\n", dest_file);
		    return FAILURE;
		}
	    }
	    else
	    {
		printf("This file (%s) is empty.\n", dest_file);
		return FAILURE;
	    }
	}
	else
	{
	    printf("This file (%s) not exist.\n", dest_file);
	    return FAILURE;
	}
    }
    else
    {
	printf("The file (%s) not valid.\n", dest_file);
	return FAILURE;
    }
    return FAILURE;
}

/*
 * Function: create_hashTable
 * 1. Loop through each element in the hash table array.
 * 2. Assign the index value to the idx field of each hash element.
 * 3. Initialize the Mlink pointer of each hash element to NULL.
 * 4. Return SUCCESS.
 * This function initializes the hash table by setting the index and link fields for each element.
 */
int create_hashTable(Hash *hash, int size)  
{
    /* run loop and initialize hash table */
    for (int i = 0; i < size; i++)
    {
	hash[i].idx = i;
	hash[i].Mlink = NULL;
    }
    return SUCCESS;
}

/*
 * Function: create_subNode
 * 1. Allocate memory for a new subNode.
 * 2. If allocation fails, return FAILURE.
 * 3. Assign the word count and file name to the new subNode.
 * 4. Set the Slink pointer of the new subNode to NULL.
 * 5. If the previous subNode pointer is NULL, assign the new subNode to it.
 * 6. Otherwise, link the new subNode to the previous subNode's Slink.
 * 7. Return SUCCESS.
 * This function creates a subNode and links it to the existing chain of subNodes.
 */
int create_subNode(subNode **prevSnode, char *filename, int wordCount)  
{
    /* Create new subnode allocate memory and validate memory allocation */
    subNode *Snew = malloc(sizeof(subNode));
    if (Snew == NULL)
	return FAILURE;

    /* Assign data */
    Snew->wordCount = wordCount;
    Snew->fileName = filename;
    Snew->Slink = NULL;

    /* connect the node */
    if (*prevSnode == NULL)
	*prevSnode = Snew;
    else
	(*prevSnode)->Slink = Snew;

    return SUCCESS;
}

/*
 * Function: create_mainNode
 * 1. Allocate memory for a new mainNode.
 * 2. If allocation fails, return FAILURE.
 * 3. Allocate memory for the word string and copy the word into it.
 * 4. If allocation for the word fails, free the mainNode and return FAILURE.
 * 5. Assign the word count and initialize the Mlink and Slink pointers to NULL.
 * 6. If the previous mainNode pointer is NULL, assign the new mainNode to it.
 * 7. Otherwise, link the new mainNode to the previous mainNode's Mlink.
 * 8. Return SUCCESS.
 *
 * Description:
 * This function creates a mainNode and links it to the existing chain of mainNodes.
 */
int create_mainNode(mainNode **prevMnode, char *word, int fileCount)  
{
    /* Create new node allocate memory and validate */
    mainNode *Mnew = malloc(sizeof(mainNode));
    if (Mnew == NULL)
	return FAILURE;

    Mnew->word = malloc(strlen(word) + 1); 
    if (Mnew->word == NULL)
    {
	free(Mnew);
	return FAILURE;
    }
    /* copy word to node */
    strcpy(Mnew->word, word); 
    Mnew->fileCount = fileCount;
    Mnew->Mlink = NULL;
    Mnew->Slink = NULL;

    /* Connect the new node */
    if (*prevMnode == NULL)
	*prevMnode = Mnew;
    else
	(*prevMnode)->Mlink = Mnew;

    return SUCCESS;
}

/*
 * Function: Update_database
 * 1. Validate the destination file using validate_file().
 * 2. If the file is valid, create a hash table using create_hashTable().
 * 3. Rewind the file pointer to the beginning of the file.
 * 4. For each line in the file:
 *    a. Extract the index, word, and file count from the line.
 *    b. If no mainNode exists at the index, create a new mainNode and link it to the hash table.
 *    c. For each file associated with the word, create a subNode and link it to the mainNode.
 * 5. Close the file after processing.
 * This function updates the hash table database with the information from the destination file.
 */
int Update_database(Hash *hash, char *dest_file, int size)  
{
    char line[500];
    char *token;
    /* Validate file */
    if (validate_file(dest_file) == FAILURE)
    {
	printf("This file is not valid.\n");
	return FAILURE;
    }
    /* Create new hash table of desired size */
    if (create_hashTable(hash, size) == FAILURE)
    {
	printf("Hash table not created successfully.\n");
	return FAILURE;
    }
    rewind(fptr);
    /* run loop scan each line */
    while ((fscanf(fptr, "%s", line)) != EOF)
    {   
	/* tokenize each words */	
	token = strtok(line, ";#");
	int idx = atoi(token);

	token = strtok(NULL, ";#");
	char *word = strdup(token);

	token = strtok(NULL, ";#");
	int fcount = atoi(token);

	mainNode *tempMnode = hash[idx].Mlink;
	mainNode *PrevMnode = NULL;

	if (tempMnode == NULL)
	{
	    /* create new node if link is null  */
	    create_mainNode(&tempMnode, word, fcount);
	    hash[idx].Mlink = tempMnode;
	}
	else
	{
	    /* traversing each node */
	    while (tempMnode->Mlink != NULL)
	    {
		tempMnode = tempMnode->Mlink;
	    }
	    /* Create node call */
	    create_mainNode(&tempMnode, word, fcount);
	    tempMnode = tempMnode->Mlink;
	}

	subNode *tempSnode = tempMnode->Slink;
	subNode *prevSnode = NULL;

	for (int i = 1; i <= fcount; i++)
	{
	    /* token size each word */
	    token = strtok(NULL, "#;");
	    char *file = strdup(token);

	    token = strtok(NULL, "#;");
	    int wordCount = atoi(token);

	    if (tempSnode == NULL)
	    {
		/* create sub node */
		create_subNode(&tempSnode, file, wordCount);
		tempMnode->Slink = tempSnode;
	    }
	    else
	    {
		/* traverisng each node */
		while (tempSnode->Slink != NULL)
		{
		    tempSnode = tempSnode->Slink;
		}
		/* create sub node */
		create_subNode(&tempSnode, file, wordCount);
	    }
	}
    }
    fclose(fptr);
    return SUCCESS;
}
