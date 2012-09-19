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


#ifndef LL_NODE
#define LL_NODE

/* 
 * WordNode
 *
 * WordNode is a linked list implementation to store words
 *
 * type:
 * WordNode
 *
 * constants:
 *		SUCCESS
 *		FAILURE
 *
 * interface routines:
 *	WordNode *Insert(WordNode *root, char *insertString)
 *		insert a string into the linked list, and then return the root node.
 *	
 *	int Search(WordNode *root, char *keyword)
 *		search for a specified key word in the linked list. Return SUCCESS if the
 *		word is found, otherwise FAILURE.
 *
 *	void PMSearch(WordNode *root, char *keyword, char **result, int *rsize)
 *		partial match search, accept keyword with represent character '_'
 *		the results are stored in the array of string result, and the size
 *		of the result is stored in rsize
 *
 *	void Traverse(WordNode *root, void (*poly)(char *key));
 *		traverse through the linked list from the root and process all the words 
 *		using poly method
 *
 *	void Destroy(WordNode *root)
 *		destroy the root node and all its child nodes
 *
 *	WordNode *DeleteWord(WordNode *root, char *word)
 *		delete a word from the linked list, return the root. If the
 *		word does not exist in the linked list, do nothing
 *
 * 
 */

#define SUCCESS 1
#define FAILURE 0
typedef struct node
{
	char *word;
	struct node *previous;
	struct node *next;
} WordNode;


WordNode *Insert(WordNode *node, char *s);

int Search(WordNode *root, char *keyword);

void PMSearch(WordNode *root, char *keyword, char ** results, int *rSize);

void Traverse(WordNode *root, void (*poly)(char* word));

void Destroy(WordNode *root);

WordNode *DeleteWord(WordNode *node, char *s);


#endif



