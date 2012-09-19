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
#include "tstnode.h"



static WordNode *currParent;
static char *insertStr;
WordNode *NotBalanceInsert(WordNode *node, char *s){
	if (!insertStr)
		insertStr = s;
	if (node == 0)
	{
		node = (WordNode*) malloc(sizeof(WordNode));
		if (node==NULL)
			return NULL;
		node->split_char = *s;
		node->lchild = node->mchild = node->rchild = NULL;
		node->key = NULL;
		node->parent = currParent;
		node->h = 0;
	}
	if (*s < node->split_char)
	{
		currParent = node;
		node->h++;
		node->lchild = NotBalanceInsert(node->lchild, s);
	} else if (*s > node->split_char)
	{
		currParent = node;
		node->h++;
		node->rchild = NotBalanceInsert(node->rchild, s);
	} else {
		if (*(s+1) == '\0'){
			char *temp = (char*) malloc((strlen(insertStr)+1)*sizeof(char));
			if (temp==NULL)
				return node;
			node->key = strcpy(temp, insertStr);
		}
		else 
		{
			currParent = node;
			node->mchild = NotBalanceInsert(node->mchild, ++s);
		}
	}
	if (insertStr)
		insertStr = 0;
	return node;
}



int Search(WordNode *node, char *s)
{
	if (!node)
		return FAILURE;
	if (*s < node->split_char)
		return Search(node->lchild, s);
	else if (*s > node->split_char)
		return Search(node->rchild, s);
	else 
	{
		if (*(s+1) == '\0')
			return SUCCESS;
		return Search(node->mchild, ++s);
	}
}

void PMSearch(WordNode *node, char *s, char ** result, int *rsize)
{
	if (!node) return;
	if (*(s+1) == '\0' && node->key && (node->split_char == *s || *s == '_')){
		result[*rsize] = node->key;
		*rsize += 1;
	}
	if (*s == '_' ||*s == node->split_char)
		if (*s && node->split_char)
			PMSearch(node->mchild, s+1, result, rsize);
	if (*s == '_' || *s < node->split_char)
		PMSearch(node->lchild, s, result, rsize);
	if (*s == '_' || *s > node->split_char)
		PMSearch(node->rchild, s, result, rsize);
}



void InOrderTraverse(WordNode *node, void (*poly)(char *key))
{   
	if (!node) return;
	if (node->lchild)
		InOrderTraverse(node->lchild, poly);
	if (node->key)
		poly(node->key);
    if (node->split_char)
        InOrderTraverse(node->mchild, poly);
	if (node->rchild)
		InOrderTraverse(node->rchild, poly);
}

void PostOrderTraverse(WordNode *node, void (*poly)(char *key))
{   
	if (!node) return;
	if (node->rchild)
		PostOrderTraverse(node->rchild, poly);
    if (node->split_char)
        PostOrderTraverse(node->mchild, poly);
	if (node->key)
        poly(node->key);
	if (node->lchild)
		PostOrderTraverse(node->lchild, poly);
}

void PreOrderTraverse(WordNode *node, void (*poly)(char *key))
{
	if (!node) return;
	if (node->mchild)
		PreOrderTraverse(node->mchild, poly);
	if (node->lchild)
		PreOrderTraverse(node->lchild, poly);
	if (node->rchild)
		PreOrderTraverse(node->rchild, poly);
	if (node->key)
		poly(node->key);
}

void Destroy(WordNode *node)
{
	WordNode *parent;
	if (node)
	{
		Destroy(node->mchild);
		Destroy(node->lchild);
		Destroy(node->rchild);
		parent = node->parent;
		if (parent)
		{
			if (parent->lchild == node)
				parent->lchild = 0;
			else if (parent->rchild == node)
				parent->rchild = 0;
			else if (parent->mchild == node)
				parent->mchild = 0;
		}
		node->lchild= node->rchild = node->mchild = node->parent = 0;
		if (node->key)
			free(node->key);
		free(node);
	}
}

int Height(WordNode *node)
{
	if (node)
		return node->h;
	return -1;
}

int GetMax(int l, int r)
{
	if (l>r)
		return l;
	return r;
}

/* 
single rotate with the left child (in left left case)

simple case:		 / -> \
normal case:     /\    ->   /\
				/\     ->    /\
balance case:
				/\   ->     /\
			   /\	 ->    /\/\
			  /\	 ->
	can only be called if node has a left child
	rotate node with its left child
	update new heights and return the new root
*/


WordNode *SingleRotateLeft(WordNode *node)
{
	WordNode *newRoot;
	WordNode *parent;
	/*rotate*/
	newRoot = node->lchild;
	if (!newRoot)
		return node;
	node->lchild = newRoot->rchild;
	if (newRoot->rchild)
		newRoot->rchild->parent = node;
	newRoot->rchild = node;
	/*update parent relationship*/
	newRoot->parent = node->parent;
	parent = newRoot->parent;
	if (parent && parent->lchild == node)
		parent->lchild = newRoot;
	else if (parent && parent->rchild == node)
		parent->rchild = newRoot;
	node->parent = newRoot;
	/*update new heights*/
	node->h = GetMax(Height(node->lchild), Height(node->rchild))+1;
	newRoot->h = GetMax(Height(newRoot->lchild), Height(newRoot->rchild))+1;
	
	return newRoot;
}

/* 
single rotate with the right child (in right right case)
simple case:		 \ -> /
normal case:     /\    ->     /\ 
				  /\   ->    /\
balance case:
				/\     ->     /\
			   / /\	   ->    /\/\
				  /\   ->
	can only be called if node has a right child
	rotate the node with its right child
	update new heights and return new root
*/

WordNode *SingleRotateRight(WordNode *node)
{
	WordNode *newRoot;WordNode *parent;
	/*rotate*/
	newRoot = node->rchild;
	if (!newRoot)
		return node;
	node->rchild = newRoot->lchild;
	if (newRoot->lchild)
		newRoot->lchild->parent = node;
	newRoot->lchild = node;
	/*update parent relationship*/
	newRoot->parent = node->parent;
	parent = newRoot->parent;
	if (parent && parent->lchild == node)
		parent->lchild = newRoot;
	else if (parent && parent->rchild == node)
		parent->rchild = newRoot;
	node->parent = newRoot;
	/*update new heights*/
	node->h = GetMax(Height(node->lchild), Height(node->rchild))+1;
	newRoot->h = GetMax(Height(newRoot->lchild), Height(newRoot->rchild))+1;
	return newRoot;
}

/*
double rotate (in left right case)

simple case:     /   ->   /\
			     \	
balance case: 
				/\   ->     /\    ->      /\
			   /\    ->    /\     ->     /\/\
			    /\   ->   /\      ->
	can only be called if the node has a left child 
	which has a right child

	rotate right the node's left child and then 
	rotate left the node
*/
WordNode *DoubleRotateRightLeft(WordNode *node)
{
	node->lchild = SingleRotateRight(node->lchild);
	return SingleRotateLeft(node);
}

/*
double rotate (in right left case)

simple case:     \   ->   /\
			     /	
balance case: 
				/\   ->    /\     ->      /\
			     /\  ->     /\    ->     /\/\
			    /\   ->      /\   ->
	can only be called if the node has a right child 
	which has a left child

	rotate left the node's right child and then 
	rotate right the node
*/


WordNode *DoubleRotateLeftRight(WordNode *node)
{
	node->rchild = SingleRotateLeft(node->rchild);
	return SingleRotateRight(node);
}

/* seft balanced Insert
after Inserting, balance the tree*/

WordNode *Insert(WordNode *node, char *s)
{
	if (!insertStr)
		insertStr = s;
	if (node == 0)
	{
		/* allocate memory for the node*/
		node = (WordNode*) malloc(sizeof(WordNode));
		/* error checking*/
		if (node==NULL)
			return node;
		node->split_char = *s;
		node->lchild = node->mchild = node->rchild = 0;
		node->key = 0;
		node->parent = currParent;
		node->h = 0;
	}
	if (*s < node->split_char)
	{
		node->h++;
		currParent = node;
		node->lchild = Insert(node->lchild, s);
		if (Height(node->lchild) - Height(node->rchild) >= 2)
		{
			if (*s < node->lchild->split_char)
			{
				node = SingleRotateLeft(node);
			}
			else
			{
				node = DoubleRotateRightLeft(node);
			}
		}
	}
	else if (*s > node->split_char)
	{
		node->h++;
		currParent = node;
		node->rchild = Insert(node->rchild, s);
		if (Height(node->rchild) - Height(node->lchild) == 2)
		{
			if (*s < node->rchild->split_char)
			{
				node = SingleRotateRight(node);
			}
			else 
			{
				node = DoubleRotateLeftRight(node);
			}
		}
	}
	else{
		if (*(s+1) == '\0')
		{
			char *temp = (char*) malloc((strlen(insertStr)+1)*sizeof(char));
			if (temp == NULL)
				return node;
			node->key = strcpy(temp, insertStr);
		}
		else
		{
			currParent = node;
			node->mchild = Insert(node->mchild, ++s);
		}
	}
	node->h = GetMax(Height(node->lchild), Height(node->rchild))+1;
	if (insertStr)
		insertStr = 0;
	return node;
}

WordNode *RemoveNode(WordNode *node)
{
	if (!node)
		return NULL;
	while (!node->lchild && !node->rchild && !node->mchild&&!node->key)
	{
		WordNode *temp = node;
		if (node->parent){
			node = node->parent;
			Destroy(temp);
		}
		else{
			Destroy(temp);
			return NULL;
		}
	}
	if (!node->mchild && !node->key)
	{
		if (!node->lchild)
		{
			WordNode *temp = node->rchild;
			node->split_char = temp->split_char;
			node->key = temp->key;
			node->lchild = temp->lchild;
			node->rchild = temp->rchild;
			node->mchild = temp->mchild;
			if (node->mchild)
				node->mchild->parent = node;
			if (node->lchild)
				node->lchild->parent = node;
			if (node->rchild)
				node->rchild->parent = node;
			temp->mchild = temp->lchild = temp->rchild = temp->parent = 0;
			temp->key = 0;
			Destroy(temp);
		} else if (!node->rchild)
		{
			WordNode *temp = node->lchild;
			node->split_char = temp->split_char;
			node->key = temp->key;
			node->lchild = temp->lchild;
			node->rchild = temp->rchild;
			node->mchild = temp->mchild;
			if (node->mchild)
				node->mchild->parent = node;
			if (node->lchild)
				node->lchild->parent = node;
			if (node->rchild)
				node->rchild->parent = node;
			temp->mchild = temp->lchild = temp->rchild = temp->parent = 0;
			temp->key = 0;
			Destroy(temp);
		}
	}
	while (node->parent)
		node = node->parent;
	return node;

}

WordNode *DeleteWord(WordNode *node, char *s)
{
	if (!node)
		return 0;
	if (*s < node->split_char)
		return DeleteWord(node->lchild, s);
	else if (*s > node->split_char)
		return DeleteWord(node->rchild, s);
	else 
	{
		if (*(s+1) == '\0'){
			if (node->key){
				free(node->key);
				node->key = 0;
				return RemoveNode(node);
			}
			while(node->parent)
				node=node->parent;
			return node;
		}
		return DeleteWord(node->mchild, ++s);
	}
}

/*char *Trim(char *str)
{
  char *end;
  while(*str == 10||*str==' ') str++;
  if(*str == 0)
    return str;
  end = str + strlen(str) - 1;
  while(end > str && (*end==10||*end==' ')) end--;
  *(end+1) = 0;
  return str;
}


int main()
{
	WordNode *node = 0;
	node = SBInsert(node, "Trong");
	Destroy(node);
	return 0;
}*/
/*
int main()
{
	char ** result;
	char * key;
	int rsize;
	WordNode *node;
	int i;
	char str[25];
	FILE *f;
	node = NULL;
	f = fopen("words", "r");
	while(fgets(str,25,f)){
		char *temp = Trim(str);
		node = SBInsert(node, temp);
	}
	DescTraverse(node);
	rsize = 0;
	key = "____ting";
	result = (char**) malloc(1000*sizeof(char));
	PMSearch(node, key, result, &rsize);
	printf("Search %s found: %d\n", key, rsize);
	for (i = 0; i < rsize; i++){
		printf("%s \n", *(result+i));
	}

	Destroy(node);
	fclose(f);
	f = fopen("words", "r");
	while(fgets(str,25,f)){
		char *temp = trim(str);
		node = deleteWord(node, temp);
	}
	free(str);
	free(result);
	fclose(f);
	return 0;
}
*/

