/*
Assignment Author: Nathaniel Tucker
Student ID: 0398463
Due Date: Sept 17
Assignment: WordCount with Trees
Description: Use the AvlTree to create a word counter
*/
#include <iostream>
#include "WordCount.h"
#include <string>
#include <random>

using namespace std;
/*
Since WordCount is more of a location to store the functions and less of a
class or object the tree would be able to be used as is for the most part.
The addWord funciton found in WordCount is used to format a string before entering
the string into the tree. getWordFile simply pulls the strings from a file and calls addWord
*/
/*
	BinaryTree
	/
   /
AvlTree ---- main
\           /
 \         /
  WordCount

*/

int main() {
	WordCount word; // calls WordCount to use getWordFile and addWord for 
	               // file call and string formatting
	word.getWordFile("WordCountTest.txt");//file being called
	word.printFreq(); //prints out each data(string) and the data's frequency
	cout << "Total word count: " << word.totalFreq() << endl; //prints out the total amount of data
	
	cout << "\ndata frequency for string (in)" << endl;
	cout << "in - " << word.findFreq("in") << endl;
	//I will remove the string "in" form the tree
	cout << "Removing (in)\n";
	word.remove("in");
	cout << "in - " << word.findFreq("in") << endl;

	//addind a new word three times
	for (int i = 0; i < 3; i++)
	{
		word.addWord("++++ZEbRA!??");
	}
	//notice how the new word has been formatted
	cout << word.find("zebra") << " - " << word.findFreq("zebra") << endl;

	//Since numbers can be apart of a word I did not add anything to remove numbers
	//So if I were do add a word like F1gur471v3ly (Figuratively) or 1st, 2nd, 3rd...,
	//They can still be added to the tree

	word.insert("f1gur471v3ly"); //inserting without formatting
	cout << word.find("f1gur471v3ly") << " - " << word.findFreq("f1gur471v3ly") << endl;

	//Now we can reprint the entire tree with the edits that were made
	cout << "\n";
	word.printFreq();

	//A downside to the formatting is if the user is unaware of what it is doing
	//or how the user would need to remember to type in the word in its formatted
	//for to search for the word in the tree

	cout << "\n";
	word.makeEmpty(); // now we can delete the tree
	word.printFreq(); // the print function with print out "Empty Tree"
	return 0;
}
