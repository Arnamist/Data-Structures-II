//****************************************************************************************************************************************
//
//     File:			    AVLTree.h
//     Student:				Cyrus Bajracharya
//     Assignment:		    Assignment 8
//     Course:				COSC 3100 01 Data Structures II
//     Due:				    
//
//****************************************************************************************************************************************
#ifndef AVLTREE_H
#define AVLTREE_H
#include<fstream>
#include<iostream>

//*****************************************************************************************************

template<typename T>
struct Node
{
	T value;
	Node<T>* left;
	Node<T>* right;
	int bFactor;
};

//*****************************************************************************************************

template<typename T>
class AVLTree {
private:
	Node<T>* root;
	void rotateLeft(Node<T>*& k1);
	void rotateRight(Node<T>*& k2);
	int getBalance(Node<T>* r) const;
	void updatebFactors(Node<T>* r);
	void destroy(Node<T>*& r);
	void insert(Node<T>*& r, const T& item);
	void order(Node<T>* r, std::ostream& os, int x) const;
	T* search(Node<T>* r, const T& item) const;
	int max(int a, int b) const;
	int height(Node<T>* r) const;

public:
	AVLTree();
	~AVLTree();

	void destroy();
	void insert(const T& item);
	void inorder(std::ostream& os = std::cout) const;
	void preorder(std::ostream& os = std::cout) const;
	void postorder(std::ostream& os = std::cout) const;
	T* search(const T& item) const;
	int height() const;
};

//*****************************************************************************************************

template<typename T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
}
template<typename T>
AVLTree<T>::~AVLTree()
{
	destroy(root);
}

//*****************************************************************************************************

template <typename T>
void AVLTree<T>::rotateLeft(Node<T>*& k1)
{
	Node<T>* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1 = k2;
}
template <typename T>
void AVLTree<T>::rotateRight(Node<T>*& k1)
{
	Node<T>* k2 = k1->left;
	k1->left = k2->right;
	k2->right = k1;
	k1 = k2;
}
template <typename T>
int AVLTree<T>::getBalance(Node<T>* r) const
{
	int balance;
	if (r == nullptr) {
		balance = 0;
	}
	else {
		balance = height(r->left) - height(r->right);
	}
	return balance;
}
template <typename T>
void AVLTree<T>::updatebFactors(Node<T>* r)
{
	if (r != nullptr) {
		r->bFactor = getBalance(r);
		updatebFactors(r->left);
		updatebFactors(r->right);
	}
}
template<typename T>
void AVLTree<T>::destroy(Node<T>*& r)
{
	if (r != nullptr)
	{
		destroy(r->left);
		destroy(r->right);
		delete r;
		r = nullptr;
	}
}
template <typename T>
void AVLTree<T>::insert(Node<T>*& r, const T& item)
{
	if (r == nullptr)
	{
		r = new Node<T>;
		r->value = item;
		r->left = nullptr;
		r->right = nullptr;
	}
	else
	{
		if (item < r->value)
			insert(r->left, item);
		else
			insert(r->right, item);
	}
	r->bFactor = getBalance(r);

	if (r->bFactor > 1)
	{
		if (r->left->bFactor > 0)
		{
			rotateRight(r);
		}
		else
		{
			rotateLeft(r->left);
			rotateRight(r);
		}
		updatebFactors(r);
	}
}
template<typename T>
void AVLTree<T> ::order(Node<T>* r, std::ostream& os, int x) const
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
T* AVLTree<T>::search(Node<T>* r, const T& item) const
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
inline int AVLTree<T>::max(int a, int b) const
{
	return (a > b) ? a : b;
}
template<typename T>
int AVLTree<T>::height(Node<T>* r) const
{
	return ((r == nullptr) ? 0 : (1 + max(height(r->left), height(r->right))));
}

//*****************************************************************************************************

template<typename T>
inline void AVLTree<T>::insert(const T& item)
{
	insert(root, item);
}
template<typename T>
void AVLTree<T>::destroy()
{
	destroy(root);
}

template<typename T>
inline void AVLTree<T>::preorder(std::ostream& os) const
{
	order(root, os, 0);
}
template<typename T>
inline void AVLTree<T>::inorder(std::ostream& os) const
{
	order(root, os, 1);
}
template<typename T>
inline void AVLTree<T>::postorder(std::ostream& os) const
{
	order(root, os, 2);
}
template<typename T>
inline int AVLTree<T>::height() const
{
	return height(root);
}
//*****************************************************************************************************

#endif