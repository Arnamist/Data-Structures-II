//****************************************************************************************************************************************
//
//     File:			    BTree.h
//     Student:				Cyrus Bajracharya
//     Assignment:		    Assignment 6
//     Course:				COSC 3100 01 Data Structures II
//     Due:				    
//
//****************************************************************************************************************************************
#ifndef BTREE_H
#define BTREE_H
#include<fstream>
#include<iostream>

//*****************************************************************************************************
template<typename T>
struct Node {
	T value;
	Node<T>* left;
	Node<T>* right;
};
//*****************************************************************************************************
template<typename T>
class BinarySearchTree {
private:
	Node<T>* root;
	void destroy(Node<T>*& r);
	void insert(Node<T>*& r, const T& item);
	void order(Node<T>* r, std::ostream& os, int x) const;
	void deleteNode(Node<T>*& r, const T& item);
	T* search(Node<T>* r, const T& item) const;
	int max(int a, int b) const;
	int height(Node<T>* r) const;
	int numNodes(Node<T>* r) const; 
	int numLeafs(Node<T>* r) const;
public:
	BinarySearchTree();
	~BinarySearchTree();
	void destroy();
	void insert(const T& item);
	void inorder(std::ostream& os = std::cout) const;
	void preorder(std::ostream& os = std::cout) const;
	void postorder(std::ostream& os = std::cout) const;
	void deleteNode(const T& item);
	void searchD(const T& item, bool& found, Node<T>*& locPtr, Node<T>*& parent) const;
	T* search(const T& item) const;
	int height() const;
	int numNodes() const;
	int numLeafs() const;
};
//*****************************************************************************************************
template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = nullptr;
}
template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	destroy(root);
}
//*****************************************************************************************************
template<typename T>
void BinarySearchTree<T>::destroy(Node<T>*& r)
{
	if (r != nullptr)
	{
		destroy(r->left);
		destroy(r->right);
		delete r;
		r = nullptr;
	}
}
template<typename T>
void BinarySearchTree<T>::destroy()
{
	destroy(root);
}
//*****************************************************************************************************
template<typename T>
void BinarySearchTree<T>::insert(Node<T>*& r, const T& item)
{
	if (r == nullptr)
	{
		r = new Node<T>;
		r->value = item;
		r->left = nullptr;
		r->right = nullptr;
	}
	else if (item < r->value)
	{
		insert(r->left, item);
	}
	else if (item > r->value)
	{
		insert(r->right, item);
	}
	else
	{
		std::cout << "Dublicate\n";
	}
}
template<typename T>
inline void BinarySearchTree<T>::insert(const T& item)
{
	insert(root, item);
}
//*****************************************************************************************************
template<typename T>
void BinarySearchTree<T> ::order(Node<T>* r, std::ostream& os, int x) const
{
	if (r != nullptr)
	{
		if (!os)
		{
			if (x == 0)
				std::cout << r->value << std::endl;
			order(r->left, os, x);
			if (x == 1)
				std::cout << r->value << std::endl;
			order(r->right, os, x);
			if (x == 2)
				std::cout << r->value << std::endl;
		}
		else
		{
			if (x == 0)
				os << r->value << std::endl;
			order(r->left, os, x);
			if (x == 1)
				os << r->value << std::endl;
			order(r->right, os, x);
			if (x == 2)
				os << r->value << std::endl;
		}
	}
}
template<typename T>
inline void BinarySearchTree<T>::preorder(std::ostream& os) const
{
	order(root, os, 0);
}
template<typename T>
inline void BinarySearchTree<T>::inorder(std::ostream& os) const
{
	order(root, os, 1);
}
template<typename T>
inline void BinarySearchTree<T>::postorder(std::ostream& os) const
{
	order(root, os, 2);
}
//*****************************************************************************************************
template <typename T>
void BinarySearchTree<T>::searchD(const T& item, bool& found, Node<T>*& locPtr, Node<T>*& parent) const
{
	locPtr = root;
	parent = nullptr;
	found = false;
	while (!found && locPtr != nullptr)
	{
		if (item < locPtr->value)
		{
			parent = locPtr;
			locPtr = locPtr->left;
		}
		else if (locPtr->value < item)
		{
			parent = locPtr;
			locPtr = locPtr->right;
		}
		else
			found = true;
	}
}
template <typename T>
void BinarySearchTree<T>::deleteNode(Node<T>*& r, const T& item)
{
	bool found;
	Node<T>* current;
	Node<T>* parent;
	searchD(item, found, current, parent);
	if (!found)
	{
		std::cout << "Item not in tree" << std::endl;
	}
	else
	{
		if ((current->left != nullptr) && (current->right != nullptr))
		{
			Node<T>* currentSucc = current->right;
			parent = current;
			while (currentSucc->left != nullptr)
			{
				parent = currentSucc;
				currentSucc = currentSucc->left;
			}
			current->value = currentSucc->value;
			current = currentSucc;
		}
		Node<T>* subtree = current->left;
		if (subtree == nullptr)
		{
			subtree = current->right;
		}
		if (parent == nullptr)
		{
			r = subtree;
		}
		else if (parent->left == current)
			parent->left = subtree;
		else
			parent->right = subtree;
		delete current;
	}
}
template <typename T>
inline void BinarySearchTree<T>::deleteNode(const T& item)
{
	deleteNode(root, item);
}
//*****************************************************************************************************
template<typename T>
T* BinarySearchTree<T>::search(Node<T>* r, const T& item) const
{
	T* result;
	if (r == nullptr)
		result = nullptr;
	else if (item < r->value)
		result = search(r->left, item);
	else if (item > r->value)
		result = search(r->right, item);
	else
		result = new T(r->value);
	return result;
}
template<typename T>
T* BinarySearchTree<T>::search(const T& item) const
{
	return search(root, item);
}
//*****************************************************************************************************
template<typename T>
inline int BinarySearchTree<T>::max(int a, int b) const
{
	return (a > b) ? a : b;
}
//*****************************************************************************************************
template<typename T>
int BinarySearchTree<T>::height(Node<T>* r) const
{
	return ((r == nullptr) ? 0 : (1 + max(height(r->left), height(r->right))));
}
template<typename T>
inline int BinarySearchTree<T>::height() const
{
	return height(root);
}
//*****************************************************************************************************
template<typename T>
inline int BinarySearchTree<T>::numNodes() const
{
	return numNodes(root);
}
template<typename T>
int BinarySearchTree<T>::numNodes(Node<T>* r) const
{
	int num = 0;
	if (r != nullptr)
	{
		num = 1 + numNodes(r->left) + numNodes(r->right);
	}
}
//*****************************************************************************************************

template <typename T>
inline int BinarySearchTree<T>::numLeafs() const
{
	return numLeafs(root);
}
template <typename T>
int BinarySearchTree<T>::numLeafs(Node<T>* r) const
{
	int num = 0;
	if (r != nullptr)
	{
		if ((r->left == nullptr) && (r->right == nullptr))
			++num;
		else
			num = numLeafs(r->left) + numLeafs(r->right);
	}
	return num;
}
//*****************************************************************************************************

#endif