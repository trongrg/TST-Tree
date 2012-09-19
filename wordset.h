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

#ifndef WORD_SET
#define WORD_SET
#ifdef TYPE
#include TYPE
#else
#error TYPE must be defined with the quoted string header file name
#endif

/* 
 * WordSet
 *
 * WordSet is a data structure to store dictionary words
 *
 * type:
 * WordSet
 *
 * constants:
 *		SUCCESS
 *		FAILURE
 *
 * interface routines:
 *	WordSet *MakeSet(WordSet *set, char sortType)
 *		attempts to initialise a WordSet variable (passed by address)
 *		if insufficient memory is available for the size list requested
 *		then MakeSet() retuns FAILURE, otherwise it returns SUCCESS
 *		MakeSet() must be applied to an WordSet before any other
 *		function.
 *
 *	WordSet *Initialize(WordSet *set, char *fileName, char sortType)
 *		initialize a WordSet by inserting all the words in the specified
 *		file into a WordSet varialbe (passed by address). If the WordSet
 *		variable is not yet created, create it by calling MakeSet()
 *
 *	int InsertWord(WordSet *set, char *word)
 *		insert a word into the a WordSet varialbe (passed by address), 
 *		increase the size of the set by 1.
 *		Return SUCCESS if the word does not exist in the set, otherwise
 *		return FAILURE
 *
 *	int RemoveWord(WordSet *set, char *word)
 *		remove a word from a WordSet varialbe (passed by address), 
 *		decrease the size of the set by 1.
 *		Return SUCCESS if the word exists in the set, otherwise
 *		return FAILURE
 *	
 *	int SearchWord(WordSet *set, char *word)
 *		search for a specified key word in a WordSet varialbe (passed by address). 
 *		Return SUCCESS if the word is found, otherwise FAILURE.
 *
 *	void PMSearchWord(WordSet *set, char *keyword, char **result, int *rsize)
 *		partial match search, accept keyword with represent character '_'
 *		the results are stored in the array of string result, and the size
 *		of the result is stored in rsize
 *
 *	int Size(WordSet *set)
 *		return the size of the set
 *
 *	char SortType(WordSet *set)
 *		return the sort type of a WordSet varialbe (passed by address)
 *
 *	void Display(WordSet *set)
 *		display all the words in a WordSet varialbe (passed by address)
*		as the sort type specified
 *
 *	void InOrderTraverse(WordSet *set, void (*poly)(char *key))
 *		traverse through a WordSet varialbe (passed by address) and
 *		process all the words ascendingly using poly method
 *	
 *	void PostOrderTraverse(WordSet *set, void (*poly)(char *key))
 *		traverse through a WordSet varialbe (passed by address) and
 *		process all the words descendingly using poly method
 *
 *	void PreOrderTraverse(WordSet *set, void (*poly)(char *key));
 *		traverse through a WordSet varialbe (passed by address) and 
 *		process all the words from root to left child then 
 *		right child using poly method
 *
 *	void FreeSet(WordSet *set)
 *		reset a WordSet variable (passed by address) to the "empty"
 *		state.
 *
 *
 */



typedef struct 
{
	WordNode *root;
	char sortType;
	int size;
} WordSet;



WordSet *MakeSet(WordSet *set, char sortType);

WordSet *Initialize(WordSet *set, char *fileName, char sortType);

int InsertWord(WordSet *set, char *word);

int RemoveWord(WordSet *set, char *word);

int SearchWord(WordSet *set, char *keyword);

void PMSearchWord(WordSet *set, char *keyword, char **result, int *rsize);

int Size(WordSet *set);

char SortType(WordSet *set);

void Display(WordSet *set);

#ifdef TST_NODE
	void DisplayPreOrder(WordSet *set);
	void DisplayPostOrder(WordSet *set);
	void DisplayInOrder(WordSet *set);
#endif

void FreeSet(WordSet *set);

char *Trim(char *str);

#endif
