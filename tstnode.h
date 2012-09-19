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



#ifndef TST_NODE
#define TST_NODE

/* 
 * WordNode
 *
 * WordNode is a ternary search tree implementation, which combine the time efficiency
 * of digital tries with the space efficiency of binary search trees, to store words
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
 *		insert a string into the trie, and then return the root node. Using 
 *		two temporary/global variables (currParent and insertStr) to store
 *		the current parent of the travelling node and the inserted String
 *		after inserting, balance the trie
 *	
 *	int Search(WordNode *root, char *keyword)
 *		search for a specified key word in the trie. Return SUCCESS if the
 *		word is found, otherwise FAILURE.
 *
 *	void PMSearch(WordNode *root, char *keyword, char **result, int *rsize)
 *		partial match search, accept keyword with represent character '_'
 *		the results are stored in the array of string result, and the size
 *		of the result is stored in rsize
 *
 *	void InOrderTraverse(WordNode *root, void (*poly)(char *key))
 *		traverse through the trie from the root and process all the words 
 *		ascendingly using poly method
 *	
 *	void PostOrderTraverse(WordNode *root, void (*poly)(char *key))
 *		traverse through the trie from the root and process all the words 
 *		descendingly using poly method
 *
 *	void PreOrderTraverse(WordNode *root, void (*poly)(char *key));
 *		traverse through the trie from the root and process all the words 
 *		from root to left child then right child using poly method
 *
 *	void Destroy(WordNode *root)
 *		destroy the root node and all its child nodes
 *
 *	WordNode *RemoveNode(WordNode *leaf)
 *		remove the leaf and all of its direct ancestors which do not form
 *		any other words
 *
 *	WordNode *DeleteWord(WordNode *root, char *word)
 *		delete a word from the trie, return the root of the trie. If the
 *		word does not exist in the trie, do nothing
 *
 * WordNode use the algorithm of AVL tree to balance itself because it can 
 * be considered as a AVL tree (the middle child does not affect the search
 * and rotate algorithm)
 *
 */

#define SUCCESS 1
#define FAILURE 0
typedef struct node
{
	char split_char; /* the split char of the node*/
	char *key; /* the key that store in the leaf*/
	struct node *parent, *lchild, *mchild, *rchild; 
	/*parent, left child, mid child, right child node*/
	int h; /* height of the node, only the node whose character
	starts a word has height*/
} WordNode;




WordNode *Insert(WordNode *root, char *word);

int Search(WordNode *root, char *keyword);

void PMSearch(WordNode *root, char *keyword, char ** results, int *rSize);

void InOrderTraverse(WordNode *root, void (*poly)(char *key));

void PostOrderTraverse(WordNode *root, void (*poly)(char *key));

void PreOrderTraverse(WordNode *root, void (*poly)(char *key));

void Destroy(WordNode *root);

WordNode *DeleteWord(WordNode *node, char *s);

#endif



