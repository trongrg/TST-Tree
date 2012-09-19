/*	Crossword Assistant
*	Assignment 2, COSC2085 Programming Techniques
*	Copyright 2010 s3245848 Tran Van Trong, s3255132 Huynh Quang Dung
*	RMIT International University Vietnam
*	This assignment includes software developed by the above mentioned
*	student(s.)
*	Refer to the NOTICE file in the root of the source tree for
*	acknowledgements of third party works used in this software.
*
*	Date created: 18 Dec 2010
*	Date last modified: 3 Jan 2011
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "wordset.h"

#define FILENAME "words"



/**************************************
 * Function readRestOfLine() is used for buffer clearing.
 *************************************/
void readRestOfLine(){
   int c;
   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;
   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}

char *MyGetString(char *str, int strlen)
{
	if (fgets(str, strlen, stdin)!=NULL){
		char *eot;
		char *newline = strchr(str,'\n');		
		if (newline!=NULL)
			*newline = '\0';
		else
			readRestOfLine();
		eot = strchr(str, 4);
		if (eot!=NULL)
			return NULL;
		return Trim(str);	
	}
	return NULL;
}


WordSet *LoadDatabase(WordSet *set, char *fileName)
{
	set = NULL;
	set = Initialize(set, fileName, 'a');
	if (!set){
		printf("Database '%s' does not exist\n", fileName);
		printf("User default database instead\n");
		set = Initialize(set, FILENAME, 'a');
		if (!set)
			printf("Default database is missing\n");
	}
	printf("%d words loaded\n", Size(set));
	return set;
}

void InteractiveMode(WordSet *set, char **result)
{
	int rsize;
	int i;
	char keyword[25];
	char *query;
	while (1){
		printf(">");
			query = MyGetString(keyword, 25);
			if (query == NULL)
				break;
			/*search for the query*/
			rsize = 0;
			PMSearchWord(set, query, result, &rsize);
			/*print the result*/
			printf("Search for keyword: %s, found %d results: \n", query, rsize);
			for (i = 0; i < rsize; i++){
				printf("%s\n", *(result+i));
			}
		}
}

char **AllocResult(char *fileName, char **result)
{
	struct stat st;
	int fileSize;
	/*get the size of the file*/
	if(stat(fileName, &st) != 0){
		fileSize = 1000000;
	} else {
		fileSize = st.st_size;
	}
	
	/* allocate memory for the result, prepare for the case that
	all the words are found*/
	result = (char**) malloc(fileSize*sizeof(char));
	if (result == NULL){
		printf("Do not have enough memory to operate\n");
		return NULL;
	}
	return result;
}

void QueryMode(WordSet *set, char **result, char *query)
{
	int rsize = 0;
	int i;
	PMSearchWord(set, query, result, &rsize);
		printf("Search for keyword: %s, found %d results: \n", query, rsize);
		for (i = 0; i < rsize; i++){
			printf("%s\n", *(result+i));
		}
}

void DoQuery(char* fileName, char *query)
{
	char **result;
	WordSet *set;
	/*load database into the set*/
	set = LoadDatabase(set, fileName);
	if (!set)
		return;
	/*allocate memory for the result*/
	result = AllocResult(fileName, result);

	if (result == NULL)
		return;

	/*if null parameter is passed, go to Interactive mode*/
	if (query == NULL){
		printf("Interactive Mode:\n");
		InteractiveMode(set, result);
	} else {
		printf("Query Mode:\n");
		QueryMode(set, result, query);
	}
	/*free memory*/
	free(result);
	FreeSet(set);

}
#ifdef TST_NODE
void DisplayMode(char *mode, char *fileName)
{
	WordSet *set;
	printf("Display Mode\n");
	set = LoadDatabase(set, fileName);
	if (set == NULL)
		return;
	if (strcmp(mode, "preorder")==0)
		DisplayPreOrder(set);
	else if (strcmp(mode, "postorder")==0)
		DisplayPostOrder(set);
	else
		DisplayInOrder(set);
}
#endif

void HelpMode()
{
	printf("usage: wordfind ");
#ifdef TST_NODE 
	printf("[--display <mode> <filename>]");
#endif
	printf(" [--db <filename>] [--q <word>]\n\n");
	printf("options: \n");
#ifdef TST_NODE
	printf("--display <mode> <filename>	optional, display all the words in the database\n");
	printf("						specified and then terminate the application\n");
	printf("						possible mode is inorder, preorder and postorder\n");
	printf("						default mode is inorder\n\n");
#endif
	printf("--db <filename>			optional, specify the database file\n\n");
	printf("--q <word>			optional, specify the query word\n\n");
	printf("						query word can contain '_' as represented\n");
	printf("						character\n\n");
	printf("if --db option is not specified the default database file (words) will be used\n");
	printf("if --q option is not specified, the program will enter interactive mode\n");
}

int main(int argc, char *args[])
{
	if (argc <= 1)
		DoQuery(FILENAME, NULL);
	else if (argc <= 4)
	{
#ifdef TST_NODE
		if (strcmp(args[1], "--display")==0){
			DisplayMode(args[2], args[3]);
		} else 
#endif
			if (strcmp(args[1], "--db")==0)
			DoQuery(args[2], NULL);
		else if (strcmp(args[1], "--q")==0)
			DoQuery(FILENAME, args[2]);
		else 
			HelpMode();
	}
	else
	{
#ifdef TST_NODE
		if (strcmp(args[1], "--display")==0){
			DisplayMode(args[2], args[3]);
		} else 
#endif
		if (strcmp(args[1], "--db")==0&&strcmp(args[3], "--q")==0)
			DoQuery(args[2], args[4]);
		else
			HelpMode();
	}
	return EXIT_SUCCESS;
}
