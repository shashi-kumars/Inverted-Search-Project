#include "main.h"

/* Main fucntion controller */
int main(int argc,char *argv[])
{
    /* Hash table declaration and take hash table size as 28 */
    int size=28;
    Hash hash[size];

    /* List declaration */
    int count=0,opt,created=100;
    FILE_LIST *flist=NULL;  
    
    /* Validate the CLA */
    if(argc==1)
    {
	printf("Pass the files.\n");
	return 0;
    }
    
    /* Call fucntion to read ,validate the files and create list */
    if(count=read_validate(argc,argv, &flist))
	printf("Reading and validation Successful.\nTotal file added to list is: %d\n",count);
    else
	printf("Reading and validation unsuccessful.\n");

    char ch='y';
    do
    {
	/* Promt for available options */
	printf("\n1.Create database\n2.Display database\n3.Search database\n4.Save database\n5.Updata database\nEnter your choice: ");
	scanf("%d",&opt); 
	switch(opt)
	{
	    /* To create database with list */
	    case 1:Create_database(hash,flist,size);
		   created=0;
		   break;
	    /* To display the created database */
	    case 2:Display_database(hash,size,created);
		   break;
            /* To search a word from database */
	    case 3:Search_database(hash,created);
		   break;
	    /* To save a created database into a text file */
	    case 4:{
		       char dest_fname[20];
		       printf("Enter the file name for saving database : ");
		       /* Read a destination file */
		       scanf("%s",dest_fname);     
		       Save_database(hash,size,dest_fname,created);
		       break;
		   }
	    /* To update the data base from file */
	    case 5: {
			int created=0;
			char *dest_fname;
			Hash hashTable[size];
			printf("Enter the file name which has data: ");
			/* read a file in with data based is backed up */
			scanf("%s",dest_fname);
			if(Update_database(hashTable,dest_fname,size) == SUCCESS)
			    Display_database(hashTable,size,created);
			break;
		    }

	    default: printf("Enter valid Option.\n");
		     break;
	}
	printf("\nDo you still want to continue[y/n]: ");
	scanf(" %c",&ch);

    }while(ch=='y');
}
