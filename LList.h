#include<iostream>
#include<string>
using namespace std;

//****************************************************************************************************************************************
template <typename T>
struct Node
{
    T data;
    Node<T>* next;

	Node()
	{
		data = { " ", " ", 0 };
		next = nullptr;
	};

	Node(const T& d, Node <T>* n = nullptr)
	{
		data = d;
		next = n;
	};
};

//****************************************************************************************************************************************
template <typename T>
class LList
{
private:
	Node <T>* first;
	//****************************************************************************************************************************************
	void insertOrderRec(Node <T>*& listPtr, const T& item)
	{
		if ((listPtr == nullptr) || (item < listPtr->data))
		{
			Node <T>* tempPtr = listPtr;
			listPtr = new Node <T>;
			listPtr->data = item;
			listPtr->next = tempPtr;
		}
		else
		{
			insertOrderRec(listPtr->next, item);
		}
	};
	//****************************************************************************************************************************************
	void deleteOrderRec(Node <T>*& listPtr, const T& item)
	{
		if (listPtr != nullptr)
		{
			if (item == listPtr->data)
			{
				Node<T>* tempPtr = listPtr;
				listPtr = listPtr->next;
				delete tempPtr;
			}
			else
			{
				deleteOrderRec(listPtr->next, item);
			}
		}
	};
	//****************************************************************************************************************************************
public:
	LList() 
	{
		first = nullptr;
	};
	//****************************************************************************************************************************************
	~LList()
	{
		Node<T>* del;
		while (first)
		{
			del = first;
			first = first->next;
			delete del;
		}
	};
	//****************************************************************************************************************************************
	void display() const 
	{
		Node<T>* temp = first;
		while (temp)
		{
			cout << temp->data << "\n";
			temp = temp->next;
		}
	};
	//****************************************************************************************************************************************
	void insertOrder(const T& item) 
	{
		insertOrderRec(first, item);
	};
	//****************************************************************************************************************************************
	void deleteNode(const T& item) 
	{
		deleteOrderRec(first, item);
	};
	//****************************************************************************************************************************************
};