#pragma once
#include<iostream>
using namespace std;
template<class t>
class node
{
	t item;
	node<t>* next;
public:
	node()
	{
		next = nullptr;
	}
	void setitem(t it)
	{
		item = it;
	}
	t getitem()
	{
		return item;
	}
	void setnext(node<t>* n)
	{
		next = n;
	}
	node<t>* getnext()
	{
		return next;
	}

};
template<class t>
class PriorityQueue
{
	node<t>* forward, * rare;
	int id;
	int count;
public:
	PriorityQueue()
	{
		forward = nullptr;
		rare = nullptr;
		count = 0;
	}

	void sort()
	{
		node<t>* i = forward;

		while (i->getnext())

		{
			node<t>* u = i->getnext();
			while (u)
			{
				if (i->getitem() < u->getitem())
				{
					t temp = i->getitem();
					i->setitem(u->getitem());
					u->setitem(temp);

				}
				u = u->getnext();
			}

			i = i->getnext();
		}


	}
	void pop()
	{
		node<t>* o = forward;
		forward = forward->getnext();
		delete o;
		count--;


	}
	
	bool isEmpty() const
	{
		if (forward == nullptr)
			return true;
		else
			return false;
	}
	bool peekFront(t& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = forward->getitem();
		return true;

	}
	t*toArray(int& countt)
	{
		countt = 0;

		if (!forward)
			return nullptr;
		//counting the no. of items in the Queue
		node<t>* p = forward;
		while (p)
		{
			countt++;
			p = p->getnext();
		}


		t* Arr = new t[countt];
		p = forward;
		for (int i = 0; i < countt; i++)
		{
			Arr[i] = p->getitem();
			p = p->getnext();
		}
		return Arr;
	}
};

//Template specialization for orders to be sorted 
//according to priority equation of VIP orders 

template<>
class node<Order*>
{
	Order* item;
	node<Order*>* next;
public:
	node()
	{
		next = nullptr;

	}
	void setitem(Order* it)
	{
		item = it;
	}
	Order* getitem()
	{
		return item;
	}
	void setnext(node<Order*>* n)
	{
		next = n;
	}
	node<Order*>* getnext()
	{

		return next;
	}

};
template<>
class PriorityQueue<Order*>
{
	node<Order*>* forward, * rare;
	int count;
public:
	PriorityQueue()
	{
		forward = nullptr;
		rare = nullptr;
		count = 0;
	}

	void insert(Order* it, char c) 
	{
		node<Order*>* u = new node<Order*>;
		u->setitem(it);
		u->setnext(nullptr);
		if (!forward)
		{
			forward = u;
			rare = u;
		}
		else
		{
			rare->setnext(u);
			rare = u;
		}
		count++;
		sort(c);
	}

	//while inserting check this is VIP order or cook using character for this indication
	//'V' for VIP

	void sort(char c) 
	{
		node<Order*>* i = forward;

		while (i->getnext())

		{
			node<Order*>* u = i->getnext();
			while (u)
			{
				//Turn pointers to objects for overloading
				//with all the imodified parameters to be set

				Order ord1 = i->getitem()->getOrder();
				ord1.setCookID(i->getitem()->getCookID());
				Order ord2 = u->getitem()->getOrder();
				ord2.setCookID(u->getitem()->getCookID());

				if (c == 'V' && ord1 < ord2)
				{
					Order* temp = i->getitem();
					i->setitem(u->getitem());
					u->setitem(temp);
				}
				u = u->getnext();
			}

			i = i->getnext();
		}

	}
	void pop()
	{
		node<Order*>* o = forward;
		forward = forward->getnext();
		delete o;
		count--;
	}

	bool isEmpty() const
	{
		if (forward == nullptr)
			return true;
		else
			return false;
	}
	bool peekFront(Order*& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = forward->getitem();
		return true;

	}
	Order** toArray(int& countt)
	{
		countt = 0;

		if (!forward)
			return nullptr;
		//counting the no. of items in the Queue
		node<Order*>* p = forward;
		while (p)
		{
			countt++;
			p = p->getnext();
		}


		Order** Arr = new Order * [countt];
		p = forward;
		for (int i = 0; i < countt; i++)
		{
			Arr[i] = p->getitem();
			p = p->getnext();
		}
		return Arr;
	}
};

//Template specialization for cooks to be 
//sorted according to speed of cooks 

template<>
class node<Cook*>
{
	Cook* item;
	node<Cook*>* next;
public:
	node()
	{
		next = nullptr;

	}
	void setitem(Cook* it)
	{
		item = it;


	}
	Cook* getitem()
	{

		return item;
	}
	void setnext(node<Cook*>* n)
	{
		next = n;

	}
	node<Cook*>* getnext()
	{

		return next;
	}

};
template<>
class PriorityQueue<Cook*>
{
	node<Cook*>* forward, * rare;
	int count;
public:
	PriorityQueue()
	{
		forward = nullptr;
		rare = nullptr;
		count = 0;
	}

	void insert(Cook* it, char c) 
	{
		node<Cook*>* u = new node<Cook*>;
		u->setitem(it);
		u->setnext(nullptr);
		if (!forward)
		{
			forward = u;
			rare = u;
		}
		else
		{
			rare->setnext(u);
			rare = u;
		}
		count++;
		sort(c);
	}

	//while inserting check this is VIP order or cook using character for this indication
	//'C' for cooks

	void sort(char c) 
	{
		node<Cook*>* i = forward;

		while (i->getnext())

		{
			node<Cook*>* u = i->getnext();
			while (u)
			{
				//Turn pointers to objects for overloading
				//with all the imodified parameters to be set

				Cook cook1 = i->getitem()->getCook();
				Cook cook2 = u->getitem()->getCook();
				if (c == 'C' && (cook1 < cook2))
				{
					Cook* temp = i->getitem();
					i->setitem(u->getitem());
					u->setitem(temp);
				}
				u = u->getnext();
			}
			i = i->getnext();
		}

	}
	void pop()
	{
		node<Cook*>* o = forward;
		forward = forward->getnext();
		delete o;
		count--;
	}

	bool isEmpty() const
	{
		if (forward == nullptr)
			return true;
		else
			return false;
	}
	bool peekFront(Cook*& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = forward->getitem();
		return true;

	}
	Cook** toArray(int& countt)
	{
		countt = 0;

		if (!forward)
			return nullptr;
		//counting the no. of items in the Queue
		node<Cook*>* p = forward;
		while (p)
		{
			countt++;
			p = p->getnext();
		}


		Cook** Arr = new Cook * [countt];
		p = forward;
		for (int i = 0; i < countt; i++)
		{
			Arr[i] = p->getitem();
			p = p->getnext();
		}
		return Arr;
	}
};
