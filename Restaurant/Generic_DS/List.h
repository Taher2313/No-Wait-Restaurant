#pragma once
#include <iostream>
using namespace std;
#include"Node.h"
template < typename T>

class List
{
	Node<T>* start;

public:

	List()
	{
		start = NULL;
	}
	void insert(T x)
	{
		Node<T>* t = start;
		if (start != NULL)
		{
			while (t->getNext() != NULL)
			{
				t = t->getNext();
			}
			Node<T>* n = new Node<T>;
			t->setNext(n);
			n->setItem(x);
			n->setNext(NULL);
		}
		else
		{
			Node<T>* n = new Node<T>;
			n->setItem(x);
			n->setNext(NULL);
			start = n;
		}
	}
	bool isEmpty() const
	{
		if (start == nullptr)
			return true;
		else
			return false;
	}
	void remove(T x)
	{

		if (start == NULL)
		{
			return;
		}
		else if (start->getItem() == x)
		{
			Node<T>* temp = start;
			start = start->getNext();
			delete temp;
			return;
		}

		Node<T>* temp = start, * parent = start;

		while (temp != NULL && temp->getItem() != x)
		{
			parent = temp;
			temp = temp->getNext();
		}

		if (temp == NULL)
		{
		
			return;
		}

		parent->setNext(temp->getNext());
		delete temp;
	}

	T* toArray(int& countt)
	{
		countt = 0;

		if (!start)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = start;
		while (p)
		{
			countt++;
			p = p->getNext();
		}


		T* Arr = new T[countt];
		p = start;
		for (int i = 0; i < countt; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

	bool removeFirst(T& frntEntry) // taher 
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = start;
		frntEntry = start->getItem();
		start = start->getNext();
		// Queue is not empty; remove front

		//==========================> check here

		//if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
			// backPtr = nullptr;

		// Free memory reserved by the dequeued node
		delete nodeToDeletePtr;


		return true;

	}

	bool seeFirstElement(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = start->getItem();
		return true;

	}
};

//Template specialization for order
//Specialize both Node class and List class
template<>
class Node<Order*>
{
	Order* item;
	Node<Order*>* next;
public:
	Node()
	{
		next = nullptr;
	}
	Node(Order* r_Item)
	{
		item = r_Item;
		next = nullptr;
	}
	void setItem(Order* it)
	{
		item = it;
	}
	Order* getItem()
	{
		return item;
	}
	void setNext(Node<Order*>* n)
	{
		next = n;
	}
	Node<Order*>* getNext()
	{
		return next;
	}

};
template<>
class List<Order*>
{
	Node<Order*>* start;
public:
	List()
	{
		start = NULL;
	}
	void insert(Order* x)
	{
		Node<Order*>* t = start;
		if (start != NULL)
		{
			while (t->getNext() != NULL)
			{
				t = t->getNext();
			}
			Node<Order*>* n = new Node<Order*>;
			t->setNext(n);
			n->setItem(x);
			n->setNext(NULL);
		}
		else
		{
			Node<Order*>* n = new Node<Order*>;
			n->setItem(x);
			n->setNext(NULL);
			start = n;
		}
	}
	bool isEmpty() const
	{
		if (start == nullptr)
			return true;
		else
			return false;
	}
	Order* remove(int id)
	{
		Order* t;
		if (start == NULL)
		{
			return NULL;
		}
		else if (start->getItem()->GetID() == id)
		{
			Node<Order*>* temp = start;
			start = start->getNext();
			t = temp->getItem();
			delete temp;
			return t;
		}

		Node<Order*>* temp = start, * parent = start;

		while (temp != NULL && temp->getItem()->GetID() != id)
		{
			parent = temp;
			temp = temp->getNext();
		}

		if (temp == NULL)
		{
			return NULL;
		}

		parent->setNext(temp->getNext());
		t = temp->getItem();
		delete temp;
		return t;
	}
	void remove(Order* x)
	{

		if (start == NULL)
		{
			return;
		}
		else if (start->getItem() == x)
		{
			Node<Order*>* temp = start;
			start = start->getNext();
			delete temp;
			return;
		}

		Node<Order*>* temp = start, * parent = start;

		while (temp != NULL && temp->getItem() != x)
		{
			parent = temp;
			temp = temp->getNext();
		}

		if (temp == NULL)
		{
			return;
		}

		parent->setNext(temp->getNext());
		delete temp;
	}
	void search(Order* x)
	{
		Node<Order*>* t = start;
		int found = 0;
		while (t != NULL)
		{
			if (t->getItem() == x)
			{
				found = 1;
				break;
			}
			t = t->getNext();
		}
		if (found == 0)
		{
		}
	}
	bool search(int x)
	{
		Node<Order*>* t = start;
		bool found = false;
		while (t != NULL)
		{
			if (t->getItem()->GetID() == x)
			{
				found = true;
				break;
			}
			t = t->getNext();
		}
		return found;
	}

	void reverse()
	{
		Node<Order*>* first = start;
		Node<Order*>* second = first->getNext();
		while (second != NULL)
		{
			Node<Order*>* tem = second->getNext();
			second->setNext(first);
			first = second;
			second = tem;
		}
		start->setNext(NULL);
		start = first;
	}
	Order** toArray(int& countt)
	{
		countt = 0;

		if (!start)
			return nullptr;
		//counting the no. of items in the Queue
		Node<Order*>* p = start;
		while (p)
		{
			countt++;
			p = p->getNext();
		}

		Order** Arr = new Order * [countt];
		p = start;
		for (int i = 0; i < countt; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

	bool removeFirst(Order*& frntEntry) // taher 
	{
		if (isEmpty())
			return false;

		Node<Order*>* nodeToDeletePtr = start;
		frntEntry = start->getItem();
		start = start->getNext();
		// Queue is not empty; remove front

		//==========================> check here

		//if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
			// backPtr = nullptr;

		// Free memory reserved by the dequeued node
		delete nodeToDeletePtr;


		return true;

	}

	bool seeFirstElement(Order*& frntEntry)  const  // taher
	{
		if (isEmpty())
			return false;

		frntEntry = start->getItem();
		return true;

	}
};