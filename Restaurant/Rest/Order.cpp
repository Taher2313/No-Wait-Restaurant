#include "Order.h"
#include<cmath>

//---------------------->> Constructors <<----------------------------//

Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	size = 5;
	pDessert = NULL;
	watingtime = 0; 
	doneDishes = 0;
}

Order::Order(int id, ORD_TYPE r_Type, int Size, double money, int arrivalTime)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	status = WAIT;
	size = Size;
	totalMoney = money;
	ArrTime = arrivalTime;
	pDessert = NULL;
	watingtime = 0;
	doneDishes = 0;
}

//---------------------->> Destructor <<----------------------------//

Order::~Order()
{
}
//------------------------------>> Setters & Getters <<---------------------------//
Order Order::getOrder()
{
	return Order(ID, type, size, totalMoney, ArrTime);
}

int Order::GetID()
{
	return ID;
}
void Order::setArrivaltime(int a)
{
	ArrTime = a;



}
ORD_TYPE Order::GetType() const
{
	return type;
}

double Order::GetMoney() const
{
	return totalMoney;
}


void Order::SetSize(int d)
{
	size = d>0?d:0;
}

int Order::GetSize() const
{
	return size;
}

void Order::setServTime(Cook* Pcook )
{
	ServTime = ceil((1.0*size)/ Pcook->getSpeed());
	setFinishTime();
;
}

void Order::setFinishTime()
{
	FinishTime = ArrTime + watingtime + ServTime ;
}

void Order::setStatus(ORD_STATUS s)
{
	status = s;
}
void Order::setDessert(Order* ord)
{
	pDessert = ord;
}
void Order::setOrdType(ORD_TYPE ot)
{
	type = ot;
}
ORD_STATUS Order::getStatus() const
{
	return status;
}

int Order::getArrivalTime()
{
	return ArrTime;
}


int Order::getwattingtime()
{
	return watingtime;

}
void Order::settotalmoney(double a)
{
	totalMoney = a;

}

void Order::setCookID(Cook* pC)
{
	pCook = pC;
}

void Order::setwatingtime(int tw)
{
	watingtime = (tw > 0) ? tw : 0;

}
void Order::setDoneDishes(double dD)
{
	doneDishes = dD;
}
int Order::getFinishTime()
{
	return FinishTime;

}
double Order::getDonDishes()
{
	return doneDishes;
}

int Order::getServTime()
{
	return ServTime;
}
Cook* Order::getCookID()
{
	return pCook;
}


int Order::CalcPriortyVIPEqn() 
{
	Priority_eqn = (3.0 * totalMoney / size) + (MaxPossibleOrdCnt - ArrTime) ;
	return Priority_eqn;
}
bool Order::operator < (Order pOrder) //for priority of VIP
{
	if (CalcPriortyVIPEqn() < pOrder.CalcPriortyVIPEqn())
	{
		return true;
	}
	else
	{
		return false;
	}
}
int Order::CalcPriortyServeEqn() 
{
	int servingTime = ceil(size * 1.0 / pCook->getSpeed());
	return servingTime;
}
bool Order::operator >= (Order pOrder)  //for priority of Serving
{
	if (CalcPriortyServeEqn() >= pOrder.CalcPriortyServeEqn())
	{
		return true;
	}
	else
	{
		return false;
	}
}