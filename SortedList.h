//****************************************************************************************************************************************
//
//     File:			    SortedList.h
//     Student:				Cyrus Bajracharya
//     Assignment:		    Assignment 10
//     Course:				COSC 3100 01 Data Structures II
//     Due:				    11/19/2021
//     Description:         The following program has various sort algorithm for array list
//
//****************************************************************************************************************************************
#ifndef SORTEDLIST_H
#define SORTEDLIST_H
#include<iostream>
#include<time.h>
//****************************************************************************************************************************************
template<typename T>
class SortedList {
private:
    T* list;
    int arrSize;
    int items;

    void resize();
    void selectionSort(T arr[], bool asc = true);
    int partition(T arr[], int low, int high, bool asc);
    void quickSort(T arr[], int low, int high, bool asc);
    void heapify(T arr[], int n, int root, bool asc);
    void heapSort(T arr[], int n, bool asc);
public:
    SortedList(int s = 10);
    ~SortedList();
    void insert(const T & item);
    void randomise();
    void display() const;
    void displayProperty() const;
    void selectionSortA();
    void selectionSortD();
    void quickSortA();
    void quickSortD();
    void heapSortA();
    void heapSortD();
};
//****************************************************************************************************************************************
template<typename T>
SortedList<T>::SortedList(int s)
{
    arrSize = s;
    items = 0;
    list = new T[arrSize];
}
template<typename T>
SortedList<T>::~SortedList()
{
    delete[] list;
}
//****************************************************************************************************************************************
template<typename T>
void SortedList<T>::resize()
{
	T* newArray;
	int newCapacity = arrSize;
	if (items >= arrSize)
		newCapacity = arrSize + 10;
	newArray = new T[newCapacity];

	if (newArray)
	{
		for (int i = 0; i < items; i++)
		{
			newArray[i] = list[i];
		}

		delete[] list;
		arrSize = newCapacity;
		list = newArray;
	}
}
template<typename T>
void SortedList<T>::insert(const T& item)
{
    
    if (items >= arrSize)
    {
        resize();
    }
    items++;
    bool found = false;
    T temp = item;
    for (int i = 0; i < items; i++)
    {
        if (list[i] < item)
            found = true;
        if (found)
            std::swap(temp, list[i]);
    }
}
//****************************************************************************************************************************************
template<typename T>
void SortedList<T>::randomise()
{
    srand(time(NULL));
    int a, b;
    for (int i = 0; i < items; i++)
    {
        a = rand() % items;
        b = rand() % items;
        if (a != b)
            std::swap(list[a], list[b]);
    }
}
template<typename T>
void SortedList<T>::display() const
{
    std::cout << "\nItems:\n";
    for (int i = 0; i < items; i++)
        std::cout << list[i] << std::endl;
}
template<typename T>
inline void SortedList<T>::displayProperty() const
{
    std::cout << "\nSize of Array: " << arrSize << "\nItems in Array: " << items << "\n";
}
//****************************************************************************************************************************************
template<typename T>
void SortedList<T>::selectionSort(T arr[], bool asc)
{
    int index;

    for (int i = 0; i <items; i++)
    {
        index = i;

        for (int j = i + 1; j < items; j++)
        {
            if (asc)
            {
                if (arr[j] < arr[index])
                    index = j;
            }
            else
            {
                if (arr[j] > arr[index])
                    index = j;
            }
        }

        std::swap(arr[index], arr[i]);
    }
}
template<typename T>
inline void SortedList<T>::selectionSortA()
{
    selectionSort(list, true);
}
template<typename T>
inline void SortedList<T>::selectionSortD()
{
    selectionSort(list, false);
}
//****************************************************************************************************************************************
template<typename T>
int SortedList<T>::partition(T arr[], int low, int high, bool asc)
{
    T pivot = arr[(low + high) / 2];
    std::swap(arr[low], arr[(low + high) / 2]);
    int smallIndex = low;
    int index;

    for (int i = low + 1; i <= high; i++) {
        index = i;
        if (asc)
        {
            if (pivot > arr[index]) 
            {
                smallIndex++;
                std::swap(arr[smallIndex], arr[index]);
            }
        }
        else 
        {
            if (pivot < arr[index])
            {
                smallIndex++;
                std::swap(arr[smallIndex], arr[index]);
            }
        }
    }
    std::swap(arr[low], arr[smallIndex]);
    return smallIndex;
}
template<typename T>
void SortedList<T>::quickSort(T arr[], int low, int high, bool asc)
{
    if (low < high)
    {
        int pivotLoc = partition(arr, low, high, asc);
        quickSort(arr, low, pivotLoc - 1, asc);
        quickSort(arr, pivotLoc + 1, high, asc);
    }
}
template<typename T>
inline void SortedList<T>::quickSortA()
{
    quickSort(list, 0, items-1, true);
}
template<typename T>
inline void SortedList<T>::quickSortD()
{
    quickSort(list, 0, items+1, false);
}
//****************************************************************************************************************************************
template<typename T>
void SortedList<T>::heapify(T arr[], int n, int root, bool asc)
{
    int largest = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (asc) 
    {
        if ((l < n) && (arr[l] > arr[largest]))
        {
            largest = l;
        }
        if ((r < n) && (arr[r] > arr[largest]))
        {
            largest = r;
        }
    }
    else
    {
        if ((l < n) && (arr[l] < arr[largest]))
        {
            largest = l;
        }
        if ((r < n) && (arr[r] < arr[largest]))
        {
            largest = r;
        }
    }
    if (largest != root)
    {
        std::swap(arr[root], arr[largest]);
        heapify(arr, n, largest, asc);
    }
}
template<typename T>
void SortedList<T>::heapSort(T arr[], int n, bool asc)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, asc);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, asc);
    }
}
template<typename T>
inline void SortedList<T>::heapSortA()
{
    heapSort(list, items, true);
}
template<typename T>
inline void SortedList<T>::heapSortD()
{
    heapSort(list, items, false);
}

//****************************************************************************************************************************************
#endif