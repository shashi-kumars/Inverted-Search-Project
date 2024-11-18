#ifndef MAIN_H
#define MAIN_H

/* Include necessary files */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* Enum for program status */
typedef enum
{
    FAILURE,
    SUCCESS
}status;

/* Structure for storing each word in list */
typedef struct FT_
{
    char *name;
    struct FT_ *link;

}FILE_LIST;

/* Sub node to store file name and word count */
typedef struct sub_node
{
    int wordCount;
    char *fileName;
    struct sub_node *Slink;
}subNode;

/* Main node to store file count and words */
typedef struct main_node
{
    int fileCount;
    char *word;
    struct main_node *Mlink;
    subNode *Slink;

}mainNode;

/* Structure for hash table */
typedef struct hash_table
{
    int idx;
    mainNode *Mlink;
}Hash;

/* Function declarations */

/* To read and validate files and words */
int read_validate(int argc ,char *argv[], FILE_LIST **flist);

/* To create the database with list */
void Create_database(Hash *hash,FILE_LIST *flist,int size);

/* To display creted database */
void Display_database(Hash *hash,int size,int created);

/* To search word in an database */
int Search_database(Hash *hash,int created);

/* Save a database in an file as backup */
int Save_database(Hash *hash,int size,char *dest_file,int created);

/* Update database from backup file */
int Update_database(Hash *hash,char *fname,int size);

#endif
