/*
Assignment Author: Nathaniel Tucker
Student ID: 0398463
Due Date: Sept 17
Assignment: WordCount with Trees
Description: Use the AvlTree to create a word counter
*/
#pragma once
#include "BinaryTree.h"

template<class T>
class AvlTree : public BinaryTree<T>
{
	/*
	Function: rotateWithLeftChild
	Author: Glenn Stevenson, taken from lecture
	Description: Rotates tree to balance if right heavy
	*/
	void rotateWithLeftChild(Node<T> * &k2) const
	{
		Node<T> *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = this->max(this->height(k2->left), this->height(k2->right)) + 1;
		k1->height = this->max(this->height(k1->left), k2->height) + 1;
		k2 = k1;
	}
	/*
	Function: rotateWithRightChild
	Author: Glenn Stevenson, taken from lecture
	Description: Rotates and balances tree if left heavy
	*/
	void rotateWithRightChild(Node<T> * &k1) const
	{
		Node<T> *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = this->max(this->height(k1->left), this->height(k1->right)) + 1;
		k2->height = this->max(this->height(k2->right), k1->height) + 1;
		k1 = k2;
	}
	/*
	Function: doubleWithLeftChild
	Author: Glenn Stevenson, taken from lecture
	Description: double rotation if right heavy
	*/
	void doubleWithLeftChild(Node<T> * &k3) const
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	/*
	Function: doubleWithRightChild
	Author: Glenn Stevenson, taken from lecture
	Description: double rotation if left heavy
	*/
	void doubleWithRightChild(Node<T> * &k1) const
	{
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}
	/*
	Function: InsertAVL
	Author: Glenn Stevenson, taken from lecture
	Description: Function that is called from overloaded Avl insert
	While inserting each element, the tree is rotated. I did add a little extra 
	parameter, if the elements are equal to eachother then a count for that
	spacific node is incremented by 1.
	*/
	void insertAVL(const T & x, Node<T> * & root) const
	{
		if (root == NULL)
		{
			root = new Node<T>;
			root->element = x;
			root->right = NULL;
			root->left = NULL;
		}
		else if (x < root->element)
		{
			insertAVL(x, root->left);
			if (this->height(root->left) - this->height(root->right) == 2)
			{
				if (x < root->left->element)
					rotateWithLeftChild(root);
				else
					doubleWithLeftChild(root);
			}
		}
		else if (root->element < x)
		{
			insertAVL(x, root->right);
			if (this->height(root->right) - this->height(root->left) == 2)
			{
				if (root->right->element < x)
					rotateWithRightChild(root);
				else
					doubleWithRightChild(root);
			}
		}
		else
			root->dataFreq++; // added feature
		if (root != NULL)
			root->height = this->max(this->height(root->left), this->height(root->right)) + 1;
	}
	/*
	Function: removeAVL
	Author: Glenn Stevenson, taken from lecture
	Description: called by overloaded Avl remove.
	Removes node from tree while balancing tree
	*/
	void removeAVL(T x, Node<T> *&root)
	{
		if (root == NULL)
			return;
		else if (x < root->element)
		{
			removeAVL(x, root->left);
			if (this->height(root->right) - this->height(root->left) > 1)
			{
				if (this->height(root->right->right) >= this->height(root->right->left))
					rotateWithRightChild(root);
				else
					doubleWithRightChild(root);
			}
		}
		else if (x > root->element)
		{
			removeAVL(x, root->right);
			if (this->height(root->left) - this->height(root->right) > 1)
			{
				if (this->height(root->left->left) >= this->height(root->left->right))
					rotateWithLeftChild(root);
				else
					doubleWithLeftChild(root);
			}
		}

		else  
		{
			if (root->left == NULL || root->right == NULL)
			{
				Node<T> *temp = root->left ? root->left : root->right;
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else
				{
					*root = *temp;
				}
				delete temp;
			}
			else
			{
				Node<T> *temp = this->findMin(root->right);
				root->element = temp->element;
				removeAVL(temp->element, root->right);
			}
			if (root != NULL)
				root->height = max(this->height(root->left), this->height(root->right)) + 1;
		}
	}

public:
	/*
	Function: AvlTree Constructor
	Description: Initiates tree with first node.
	*/
	AvlTree()
	{
		this->root = NULL;
	}
	/*
	Function: AvlTree Working Constructor
	Description: Initiates tree with first node and data;
	*/
	AvlTree(T data)
	{
		insertAvl(data, this->root);
	}
	/*
	Function: AvlTree Destructor
	Author: Glenn Stevenson, taken from lecture
	Description: Destructs tree
	*/
	~AvlTree()
	{
		this->makeEmpty(this->root);
	}
	/*
	Function: insert
	Author: Nathaniel Tucker
	Description: inserts node, calls AVL specific insert for balancing
	*/
	void insert(T data)
	{
		insertAVL(data, this->root);
	}
	/*
	Function: remove
	Author: Nathaniel Tucker
	Description: Removes node, calls AVL specific remove for balancing
	*/
	void remove(T data)
	{
		removeAVL(data, this->root);
	}
};
