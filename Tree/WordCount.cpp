/*
Assignment Author: Nathaniel Tucker
Student ID: 0398463
Due Date: Sept 17
Assignment: WordCount with Trees
Description: Use the AvlTree to create a word counter
*/
#include "WordCount.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
/*
Function: FormatString
Author: Nathaniel Tucker
Description: Formats strings coming form file by
removing punctuation and making the string all lowercase
for more accurate compairisons.
*/
string WordCount::FormatString(string str)
{
	string tmp;
	for (char c : str)
	{
		if (!isalpha(c))
			str.erase(std::remove(str.begin(), str.end(), c), str.end());
	}
	for (char c : str)
	{
		tmp += tolower(c);
	}
	return tmp;
}
/*
Function: addWord
Author: Nathaniel Tucker
Description: takes in a string, formats them then adds the string 
into the tree
*/
void WordCount::addWord(string word)
{
	insert(FormatString(word));
}
/*
Function: getWordFile
Author: Nathaniel Tucker
Description: Pulls individual words from file, sends
each word to addWord to be added to tree.
*/
void WordCount::getWordFile(string fileName)
{
	ifstream infile(fileName);
	string str;
	if (!infile)
	{
		cout << "Unable to read file" << endl;
	}
	while (infile >> str)
		addWord(str);
	infile.close();
}
