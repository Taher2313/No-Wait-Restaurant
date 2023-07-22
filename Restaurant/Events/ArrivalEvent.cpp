#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType , int size , double money) :Event(eTime, oID)
{
	OrdType = oType;
	OrdSize = (size>0)?size:2;
	OrdMoney = (money>0)?money:100;
}


void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	Order* pOrd = new Order(OrderID, OrdType, OrdSize, OrdMoney, EventTime); // (Senku ^_^)
	pRest->AddtowaitQueue(pOrd); 


	
}
