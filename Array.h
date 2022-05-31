#ifndef ARRAY_H
#define ARRAY_H
#include<iostream>
//*****************************************************************************************************
template<typename T>
class ArrayList {
private:
    T* list;
    int size;
    int items;
    void binarySearchRec(const T list[], int first, int last, const T& item, bool& found, int& loc);
public:
    ArrayList(int s = 10);
    ~ArrayList();
    ArrayList(const ArrayList<T>& a);
    void insert(const T& value);
    void insertA(const T& value);
    bool isFull() const;
    bool isEmpty() const;
    int listSize() const;
    void print(std::ostream& os = std::cout) const;
    int binarySearch(const T& value);
};
//*****************************************************************************************************
template<typename T>
ArrayList<T>::ArrayList(int s)
{
    size = s;
    items = 0;
    list = new T[size];
}
//*****************************************************************************************************
template<typename T>
ArrayList<T>::~ArrayList()
{
    delete[] list;
}
//*****************************************************************************************************
template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& a)
{
    size = a.size;
    items = a.items;
    list = new T[a.size];
    for (int i = 0; i < items; i++)
        list[i] = a.list[i];
}
//*****************************************************************************************************
template<typename T>
void ArrayList<T>::insert(const T& value)
{
    if (isFull())
    {
        std::cout << "\nList is full, unable to store this item: " << value;
    }
    else
    {
        items++;
        bool found = false;
        T temp = value;
        for (int i = 0; i < items; i++)
        {
            if (list[i] < value)
                found = true;
            if (found)
                swap(temp, list[i]);
        }
    }
}
//*****************************************************************************************************
template<typename T>
void ArrayList<T>::insertA(const T& value)
{
    if (isFull())
    {
        std::cout << "\nList is full, unable to store this item: " << value;
    }
    else
    {
        bool found = false;
        T temp = value;
        int i = 0;
        while (!found && i < items)
        {
            if (list[i] > value)
            {
                found = true;
                break;
            }
            i++;
        }
        if (i < items)
        {
            while (i <= items)
            {
                std::swap(temp, list[i]);
                i++;
            }
        }
        else
            list[items] = temp;
        items++;
    }
}
//*****************************************************************************************************
template<typename T>
inline bool ArrayList<T>::isFull() const
{
    return(items >= size);
}
//*****************************************************************************************************
template<typename T>
inline bool ArrayList<T>::isEmpty() const
{
    return(items == 0);
}
//*****************************************************************************************************
template<typename T>
inline int ArrayList<T>::listSize() const
{
    return items;
}
//*****************************************************************************************************
template<typename T>
void ArrayList<T>::print(std::ostream& os) const
{
    if (!os)
    {
        std::cout << "\nItems:\n";
        for (int i = 0; i < items; i++)
            std::cout << list[i] << std::endl;
    }
    else
    {
        for (int i = 0; i < items; i++)
            os << list[i] << std::endl;
    }
    
}
//*****************************************************************************************************
template<typename T>
void ArrayList<T>::binarySearchRec(const T list[], int first, int last, const T& item, bool& found, int& loc)
{
    if (first > last)
        found = false;
    else
    {
        loc = (first + last) / 2;
        if (item < list[loc])
            binarySearchRec(list, first, loc - 1, item, found, loc);
        else if (item > list[loc])
            binarySearchRec(list, loc + 1, last, item, found, loc);
        else
            found = true;
    }
}
//*****************************************************************************************************
template<typename T>
int ArrayList<T>::binarySearch(const T& value)
{
    int loc;
    bool found = false;
    binarySearchRec(list, 0, items, value, found, loc);
    if (found == true)
        return loc;
    else
        return -1;
}
//*****************************************************************************************************

#endif