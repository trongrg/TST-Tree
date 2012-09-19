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
#include "llnode.h"


WordNode *Insert(WordNode *node, char *s)
{
	char *strtemp;
	WordNode *newNode;

	/* Create New Node */
	strtemp = (char*) malloc((strlen(s)+1)*sizeof(char));
	if (strtemp==NULL)
		return FAILURE;

	newNode = (WordNode*) malloc(sizeof(WordNode));
	if (newNode==NULL)
		return FAILURE;

	newNode->word = strcpy(strtemp, s);
	newNode->previous = NULL;
	newNode->next = node;

	if(newNode->next){
		newNode->next->previous = newNode;
	}
	return newNode;
}

int Search(WordNode *root, char *keyword)
{
	int cmpResult=0;
	WordNode *currentNode = root;

	while(currentNode){
		cmpResult = strcmp(currentNode->word,keyword);/* && strcmp(keyword, currentNode->word);*/
		if(cmpResult == 0){
			return SUCCESS;
		}
		currentNode = currentNode->next;
	}
	return FAILURE;
}

void Traverse(WordNode *root, void (*poly)(char *word))
{
	WordNode *currentNode = root;
	while (currentNode)
	{
		poly(currentNode->word);
		currentNode = currentNode->next;
	}
}


void PMSearch(WordNode *node, char *s, char ** result, int *rsize)
{
	WordNode *current = node;
	while(current){
		char *temp = s;
		char *currentC = current->word;

		while (*temp !='\0' && *currentC !='\0'){
			if(*temp !='_' && *temp !=*currentC){
				break;
			}
			temp++;
			currentC++;
		}
		if(*temp =='\0' && *currentC =='\0'){
			result[*rsize] = current->word;
			(*rsize)++;
		}
		current = current->next;
	}
}

void Destroy(WordNode *node)
{
	WordNode *currentNode;
	while(node){
		free(node->word);
		currentNode = node;
		node=node->next;
		free(currentNode);
	}
}

WordNode *DeleteWord(WordNode *node, char *s)
{
	int cmpResult=0;
	WordNode *root = node;
	WordNode *currentNode = node;
	WordNode *previousNode = NULL;

	while(currentNode){
		cmpResult = strcmp(currentNode->word,s) && strcmp(s, currentNode->word);
		if(cmpResult == 0){
			previousNode = currentNode->previous;
			previousNode->next = currentNode->next;
			currentNode->next=NULL;
			Destroy(currentNode);
			return root;
		}
		currentNode = currentNode->next;
	}
	return root;
}




