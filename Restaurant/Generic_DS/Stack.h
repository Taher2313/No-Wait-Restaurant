#pragma once
#include"Node.h"
template<class T>
class Stack
{
	Node<T>* top;
public:

	Stack() //Constructor
	{
		top = NULL;
	}

	void push(T x) //fill the stack 
	{
		Node<T>* n = new Node<T>;
		n->setItem(x);
		n->setNext(top);
		top = n;
	}

	bool pop(T& x)
	{
		if (top == NULL)
		{
			return false;
		}
		else
		{
			x = top->getItem();
			Node<T>* t = top;
			top = top->getNext();
			delete t;
			return true;
		}
	}

	bool isEmpty() const
	{
		if (top == nullptr)
			return true;
		else
			return false;
	}

	bool seeFirstElement(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = top->getItem();
		return true;
	}
};
