/*
Assignment Author: Nathaniel Tucker
Student ID: 0398463
Due Date: Sept 17
Assignment: WordCount with Trees
Description: Use the AvlTree to create a word counter
*/
#pragma once
#include <iostream>

using std::cout;
using std::endl;

template<class T>
struct Node
{
	T       element;
	Node   *left;
	Node   *right;
	int     height;
	int     dataFreq = 1;
};

template<class T>
class BinaryTree
{
public:
	/*
	Function: totalFreq
	Author: Nathaniel Tucker
	Description: Returns the total number
	of items in the tree; whether it is stored
	or has shown up.
	*/
	int totalFreq()
	{
		return totalFreq(this->root);
	}
	/*
	Function: BinaryTree Constructor
	Author: Glenn Stevenson, taken from lecture
	Description: Initiates tree with first node.
	*/
	BinaryTree()
	{
		this->root = NULL;
	}
	/*
	Function: BinaryTree  Working Constructor
	Author: Glenn Stevenson, taken from lecture
	Description: Initiates tree with first node storing data.
	*/
	BinaryTree(T data)
	{
		insert(data);
	}
	/*
	Function: getRoot
	Author: Nathaniel Tucker
	Description: returns element form root node
	*/
	T getRoot() const
	{
		return root->element;
	}
	/*
	Function: findMin
	Author: Glenn Stevenson, taken from lecture
	Description: finds element with lowest value
	*/
	const T & findMin() const
	{
		return elementAt(findMin(root));
	}
	/*
	Function: findMax
	Author: Glenn Stevenson, taken from lecture
	Description: returns element with greatest value
	*/
	const T & findMax() const
	{
		return elementAt(findMin(root));
	}
	/*
	Function: find
	Author: Glenn Stevenson, taken from lecture
	Description: returns element at given location
	*/
	const T & find(const T & x) const
	{
		return elementAt(find(x, root));
	}
	/*
	Function: findFreq
	Author: Nathaniel Tucker
	Description: returns element at given location
	*/
	const int & findFreq(const T & x) const
	{
		return freqAt(find(x, root));
	}
	/*
	Function: isEmpty
	Author: Glenn Stevenson, taken from lecture
	Description: if tree is empty, returns true, else returns false (meaning that it is not empty)
	*/
	bool isEmpty() const
	{
		return root == NULL;
	}
	/*
	Function: printTree
	Author: Glenn Stevenson, taken from lecture
	Description: prints elements of tree
	*/
	void printTree() const
	{
		if (isEmpty())
			cout << "Empty Tree" << endl;
		else
			printTree(root);
	}
	/*
	Function: printFrew
	Author: Nathaniel Tucker
	Description: prints elements and frequency of each element
	*/
	void printFreq() const
	{
		if (isEmpty())
			cout << "Empty Tree" << endl;
		else
			printFreq(root);
	}
	/*
	Function: makeEmpty
	Author: Glenn Stevenson, taken from lecture
	Description: deletes entire tree
	*/
	void makeEmpty()
	{
		makeEmpty(root);
	}
	/*
	Function: insert
	Author: Glenn Stevenson, taken from lecture
	Description: adds node and data to tree
	*/
	void insert(const int &x)
	{
		insert(x, root);
	}
	/*
	Function: remove
	Author: Glenn Stevenson, taken from lecture
	Description: removes node and data from tree
	*/
	void remove(const int &x)
	{
		remove(x, root);
	}
	/*
	Function: = operator
	Author: Glenn Stevenson, taken from lecture
	Description: makes one tree equal to another by cloning
	*/
	const BinaryTree & operator=(const BinaryTree & rhs)
	{
		if (this != &rhs)
		{
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}

protected:

	Node<T> *root;
	/*
	Function: totalFreq
	Author: Nathaniel Tucker
	Description: returns the total number of elements in the tree
	*/
	int totalFreq(Node<T> *n)
	{
		if (n == NULL)
			return 0;
		else
			return n->dataFreq + totalFreq(n->left) + totalFreq(n->right);
	}
	/*
	Function: elementAt
	Author: Glenn Stevenson, taken from lecture
	Description: returns element at node
	*/
	const T & elementAt(Node<T>  *rt) const
	{
		if (rt == NULL)
			return 0;
		else
			return rt->element;
	}
	/*
	Funciton: freqAt
	Author: Nathaniel Tucker
	Description: returns frequency at at node
	*/
	const int & freqAt(Node<T> *rt) const
	{
		if (rt == NULL)
			return 0;
		else
			return rt->dataFreq;
	}
	/*
	Function: insert
	Author: Glenn Stevenson, taken from lecture
	Description: inserts data. if data is not found, then a new node
	is added, if data is already present then the dataFreq is incremented by 1
	*/
	void insert(const T &data, Node<T> * &rt) const
	{
		if (rt == NULL)
		{
			rt = new Node<T>;
			rt->element = data;
			rt->right = NULL;
			rt->left = NULL;
		}
		else if (data < rt->element)
			insert(data, rt->left);
		else if (data > rt->element)
			insert(data, rt->right);
		else
			rt->dataFreq++; // added feature
		if (root != NULL)
			root->height = max(height(root->left), height(root->right)) + 1;
	}
	/*
	Function: remove
	Author: Glenn Stevenson, taken from lecture
	Description: removes node at given data
	*/
	void remove(int data, Node<T> *&n)
	{
		if (n == NULL)
			return; //empty tree do nothing
		if (data < n->Data)
			this->remove(data, n->left);
		else if (data > n->Data)
			this->remove(data, n->right);
		else if (n->left != NULL && n->Right != NULL)
		{
			n->Data = findMin(n->right);
			remove(n->Data, n->right);
		}
		else
		{
			Node<T> *oldNode = n;
			n = (n->left != NULL) ? n->left : n->right;
			delete oldNode;
		}
	}
	/*
	Function: findMin
	Author: Glenn Stevenson, taken from lecture
	Description: finds data with min value
	*/
	Node<T> * findMin(Node<T> *t) const
	{
		if (t == NULL)
			return t;
		while (t->left != NULL)
			t = t->left;
		return t;
	}
	/*
	Function: findMax
	Author: Glenn Stevenson, taken from lecture
	Description: finds data with max vaule
	*/
	Node<T> * findMax(Node<T> *t) const
	{
		if (t == NULL)
			return t;
		while (t->right != NULL)
			t = t->right;
		return t;
	}
	/*
	Function: find
	Author: Glenn Stevenson, taken from lecture
	Description: retruns node at given data
	*/
	Node<T> * find(const T & x, Node<T> *t) const
	{
		while (t != NULL)
			if (x < t->element)
				t = t->left;
			else if (t->element < x)
				t = t->right;
			else
				return t;    // Match

		return NULL;   // No match
	}
	/*
	Function: makeEmpty
	Author: Glenn Stevenson, taken from lecture
	Description: deletes entire tree
	*/
	void makeEmpty(Node<T> * & t) const
	{
		if (t != NULL)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}
	/*
	Function: printTree
	Author: Glenn Stevenson, taken from lecture
	Description: prints all elements form tree
	*/
	void printTree(Node<T> *t) const
	{
		if (t != NULL)
		{
			printTree(t->left);
			cout << t->element << endl;
			printTree(t->right);
		}
	}
	/*
	Function: printFreq
	Author: Nathaniel Tucker
	Description: Prints data and its frequency from tree
	*/
	void printFreq(Node<T> *t) const
	{
		if (t != NULL)
		{
			printFreq(t->left);
			cout << t->element << " : " << t->dataFreq << endl;
			printFreq(t->right);
		}
	}
	/*
	Function: clone
	Author: Glenn Stevenson, taken from lecture
	Description: makes clone of tree
	*/
	Node<T> *clone(Node<T> *t) const
	{
		if (t == NULL)
			return NULL;
		else
			return new Node<T>(t->element, clone(t->left),
				clone(t->right), t->height);
	}

	/*
	Function: height
	Author: Glenn Stevenson, taken from lecture
	Description: returns height at each node
	*/
	int height(Node<T> *t) const
	{
		return root == NULL ? -1 : root->height;
	}
	/*
	Function: max
	Author: Glenn Stevenson, taken from lecture
	Description: finds which height is greater
	*/
	int max(int lhs, int rhs) const
	{
		return lhs > rhs ? lhs : rhs;
	}


};

