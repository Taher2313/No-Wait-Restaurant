#include "CancellationEvent.h"
#include"..\Rest\Restaurant.h"
CancellationEvent::CancellationEvent(int eTime, int oID) :Event(eTime, oID)
{
}

void CancellationEvent::Execute(Restaurant* pRest) //Senku ^_^
{
	bool state;
	state = pRest->RemoveFromnList(OrderID);
	if (state)
		pRest->Decrement_Orders_Count_For_Cancellation();
}
