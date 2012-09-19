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
#include "wordset.h"




char *Trim(char *str)
{
  char *end;
  while (*str == '\n'||*str=='\r'||*str==' ') 
	  str++;
  if (*str == 0)
    return str;
  end = str + strlen(str) - 1;
  while (end > str && (*end=='\r'||*end=='\n'||*end==' ')) 
	  end--;
  *(end+1) = 0;
  return str;
}


WordSet *MakeSet(WordSet *set, char sortType)
{
	if (set == NULL)
		set = (WordSet*)malloc(sizeof(WordSet));
	if (set == NULL)
		return NULL;
	set->size = 0;
	if (sortType=='d'||sortType=='D')
		set->sortType = 'd';
	else if (sortType=='a'||sortType=='A')
		set->sortType = 'a';
	else set->sortType = 'a';
	set->root = NULL;
	return set;
}

WordSet *Initialize(WordSet *set, char *fileName, char sortType)
{
	char input[25];
	FILE *f;
	set = MakeSet(set, sortType);
	f = fopen(fileName, "r");
	if (f == NULL){
		return NULL;
	}
	while(fgets(input,25,f))
	{
		char *temp = Trim(input);
		set->root = Insert(set->root, temp);
		set->size++;
	}
	fclose(f);
	return set;
}

int InsertWord(WordSet *set, char *word)
{
	if (Search(set->root, word) == SUCCESS)
		return FAILURE;
	set->root = Insert(set->root, word);
	set->size++;
	return SUCCESS;
}

int RemoveWord(WordSet *set, char *word)
{
	if (Search(set->root, word) == FAILURE)
		return FAILURE;
	set->root = DeleteWord(set->root, word);
	set->size--;
	return SUCCESS;
}

int SearchWord(WordSet *set, char *word)
{
	return Search(set->root, word);
}

void PMSearchWord(WordSet *set, char *word, char **result, int *rsize)
{
	PMSearch(set->root, word, result, rsize);
}

int Size(WordSet *set)
{
	return set->size;
}

char SortType(WordSet *set)
{
	return set->sortType;
}

void DisplayWord(char *word)
{
	printf("%s\n", word);
}

void Display(WordSet *set)
{
#ifdef TST_NODE
	if (set->sortType == 'a')
		InOrderTraverse(set->root, DisplayWord);
	else 
		PostOrderTraverse(set->root, DisplayWord);
#endif
#ifdef LL_NODE
	Traverse(set->root, DisplayWord);
#endif
}

#ifdef TST_NODE
void DisplayPreOrder(WordSet *set)
{
	PreOrderTraverse(set->root, DisplayWord);
}
void DisplayPostOrder(WordSet *set)
{
	PostOrderTraverse(set->root, DisplayWord);
}
void DisplayInOrder(WordSet *set)
{
	InOrderTraverse(set->root, DisplayWord);
}
#endif

void FreeSet(WordSet *set)
{
	if (!set)
		return;
	Destroy(set->root);
	set->root = NULL;
	set->size = 0;
	set->sortType = 0;
	free(set);
}
/*
int main()
{
	WordSet *set = NULL;
	char *fileName = "words";
	set = Initialize(set, fileName, 'a');
	InsertWord(set, "TRUE");
	Display(set);
	printf("set size: %d\n", Size(set));
	FreeSet(set);
	return 0;
}*/
