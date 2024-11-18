#include "main.h"

/*
 * Function: file_exist
 * 1. Attempt to open the file in read mode.
 * 2. If the file pointer is not NULL, return SUCCESS (indicating the file exists).
 * 3. If the file pointer is NULL, return FAILURE (indicating the file does not exist).
 * Checks if a file with the given name exists by trying to open it in read mode.
 */
int file_exist(char *file_name) 
{
    /* open the file in read mode and validate the file opening */
    FILE *fptr = fopen(file_name, "r");
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
 * Function: file_content
 * 1. Open the file in read mode.
 * 2. Move the file pointer to the end of the file using fseek.
 * 3. Get the current position of the file pointer using ftell, which gives the file size.
 * 4. If the size is greater than 1 (indicating the file has content), return SUCCESS.
 * 5. Otherwise, return FAILURE (indicating the file is empty).
 * Checks if a file has any content by calculating its size.
 */
int file_content(char *file_name) 
{
    /* open file in read mode and go till end of file */
    FILE *fptr = fopen(file_name, "r");
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    /* check if the file size is greater then 1 */
    if (size > 1)
        return SUCCESS;
    else
        return FAILURE;
}

/*
 * Function: duplicate_file_check
 * 1. If the file list (flist) is NULL, return FAILURE (no duplicates).
 * 2. Otherwise, traverse the linked list of files:
 *    a. Compare each file name in the list with the given file name.
 *    b. If a match is found, return SUCCESS (indicating a duplicate file).
 *    c. If no match is found after traversing the list, return FAILURE.
 * Checks if a file with the given name is already present in the list of files.
 */
int duplicate_file_check(FILE_LIST *flist, char *file_name)
{
    /* Check if the list is empty */
    if (flist == NULL)
    {
        return FAILURE;
    }
    else
    {
        FILE_LIST *temp = flist;
	/* run loop and get each file */
        while (temp != NULL)
        {
	    /* check each file with current file for duplicacy */
            if (strcmp(temp->name, file_name) == 0)
            {
                return SUCCESS;
            }
            temp = temp->link;
        }
        return FAILURE;
    }
}

/*
 * Function: insert_list
 * 1. Allocate memory for a new FILE_LIST node.
 * 2. Assign the given file name to the new node and set its link to NULL.
 * 3. If the file list (flist) is NULL, make the new node the head of the list.
 * 4. Otherwise, traverse the list to find the last node and link the new node to it.
 * 5. Return SUCCESS after inserting the new node.
 * Inserts a file into the list of files. The file is added to the end of the linked list.
 */
int insert_list(FILE_LIST **flist, char *file_name)
{
    /* Create new node allocate memory and validate memory allocation */
    FILE_LIST *new = malloc(sizeof(FILE_LIST));
    new->name = file_name;
    new->link = NULL;

    if (*flist == NULL)
    {
        *flist = new;
        return SUCCESS;
    }
    else
    {
        FILE_LIST *temp = *flist;
	/* run loop till last file and connect at end */
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new;
        return SUCCESS;
    }
}

/*
 * Function: read_validate
 * 1. Initialize a file count to 0.
 * 2. Loop through the command-line arguments (excluding the program name):
 *    a. Check if the file name ends with ".txt".
 *    b. If valid, check if the file exists.
 *    c. If the file exists, check if it has content.
 *    d. If the file has content, check if it's a duplicate.
 *    e. If not a duplicate, insert the file into the list and increment the file count.
 *    f. If any checks fail, print an appropriate error message.
 * 3. Return the total count of valid, non-duplicate files.
 * Validates the list of files passed as command-line arguments, checking if they exist, 
 * have content, and are not duplicates. Valid files are added to the file list.
 */
int read_validate(int argc, char *argv[], FILE_LIST **flist)  
{
    int file_count = 0;
    /* run loop for each file passed from CLA */
    for (int i = 1; i < argc; i++)
    {
	/* check for text file */
        if (strstr(argv[i], ".txt"))
        {
	    /* check file exesistece */
            if (file_exist(argv[i]) == SUCCESS)
            {
		/* check for file has content */
                if (file_content(argv[i]) == SUCCESS)
                {
		    /* check for file duplicate */
                    if (duplicate_file_check(*flist, argv[i]) == FAILURE)
                    {
			/* insert new file to list */
                        if (insert_list(flist, argv[i]) == SUCCESS)
                        {
			    /* increment file count */
                            file_count++;
                        }
                    }
                    else
                    {
                        printf("This file (%s) is duplicate.\n", argv[i]);
                    }
                }
                else
                {
                    printf("This file (%s) is empty.\n", argv[i]);
                }
            }
            else
            {
                printf("This file (%s) does not exist.\n", argv[i]);
            }	    
        }
        else
        {
            printf("The file (%s) is not valid.\n", argv[i]);
        }	
    }
    return file_count;
}
