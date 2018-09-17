/*
Assignment Author: Nathaniel Tucker
Student ID: 0398463
Due Date: Sept 17
Assignment: WordCount with Trees
Description: Use the AvlTree to create a word counter
*/
#pragma once
#include "AvlTree.h"
#include <string>

using std::string;
/*
The main purpose of WordCount aside from being a word count
is moving strings from a file into the tree.
All other functions used to see the data and manipulate 
the data is found in the BinaryTree.h file.
The only important funciton in this file is
FormatString which removes all punctuations and lowercases the words
for proper compairson. Aside from that, anyone using the Binary/Avl Tree
should be able to use methods straight from the Tree to achieve the
same results.

This class is more FP than OOP.
*/
class WordCount : public AvlTree<string>
{
private:
	string FormatString(string);
public:
	void addWord(string);
	void getWordFile(string);


};
