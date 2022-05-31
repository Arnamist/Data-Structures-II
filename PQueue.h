//****************************************************************************************************************************************
//
//     File:			    PQueue.h
//     Student:				Cyrus Bajracharya
//     Assignment:		    Assignment 7
//     Course:				COSC 3100 01 Data Structures II
//     Due:				    
//
//****************************************************************************************************************************************
#ifndef PQUEUE_H
#define PQUEUE_H
#include<iostream>

//*****************************************************************************************************
template<typename T>
class PriorityQueue {
private:
	T* elements;
	int size;
	int items;
	bool resize();
	void heapify(int i);
public:
	PriorityQueue();
	~PriorityQueue();
	void enqueue(const T& value);
	void dequeue(T& value);
	void display() const;
};
//*****************************************************************************************************
template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	size = 12;
	items = 0;
	elements = new T[size];
}
template<typename T>
PriorityQueue<T>::~PriorityQueue()
{
	size = 0;
	items = 0;
	delete[] elements;
}
//*****************************************************************************************************
template<typename T>
void PriorityQueue<T>::display() const
{
	std::cout << "\nItems:\n";
	for (int i = 0; i < items; i++) {
		std::cout << i+1 << ". ";
		elements[i].display();
		std::cout << std::endl;
	}
}
//*****************************************************************************************************
template <typename T>
bool PriorityQueue<T>::resize()
{
	T* newArray;
	bool success = false;
	int newCapacity = 0;
	if (items >= size)
		newCapacity = size + 10;
	else if (size - items >= 10 && size > 12)
		newCapacity = size - 10;
	newArray = new T[newCapacity];
	

	if (newArray)
	{
		for (int i = 0; i < items; i++)
		{
			newArray[i] = elements[i];
		}

		delete[] elements;
		size = newCapacity;
		elements = newArray;
		success = true;
	}

	return success;
}
//*****************************************************************************************************
template<typename T>
void PriorityQueue<T>::enqueue(const T& value)
{
	int child = items;
	int parent = (child - 1) / 2;
	bool success = true;
	if (items >= size)
	{
		success = resize();
	}
	if (success)
	{
		while ((child > 0) && (value > elements[parent]))
		{
			elements[child] = elements[parent];
			child = parent;
			parent = (parent - 1) / 2;
		}
		elements[child] = value;
		items++;
	}
}
//*****************************************************************************************************
template<typename T>
void PriorityQueue<T>::dequeue(T& value)
{
	if (items > 0)
	{
		value = elements[0];
		elements[0] = elements[items - 1];
		items--;
		heapify(0);
	}
	if (size - items >= 10 && size > 12)
	{
		resize();
	}

}
//*****************************************************************************************************
template<typename T>
void PriorityQueue<T>::heapify(int i)
{
	int leftChild;
	int rightChild;
	int largest;
	bool stop = false;
	T temp = elements[i];
	leftChild = (i * 2) + 1;

	while ((leftChild < items) && (!stop))
	{
		rightChild = leftChild + 1;
		if (rightChild >= items)
		{
			largest = leftChild;
		}
		else if (elements[leftChild] > elements[rightChild])
		{
			largest = leftChild;
		}
		else
		{
			largest = rightChild;
		}
		if (elements[largest] > temp)
		{
			elements[i] = elements[largest];
			i = largest;
			leftChild = (i * 2) + 1;
		}
		else
		{
			stop = true;
		}
	}
	elements[i] = temp;
}
//*****************************************************************************************************
#endif