#include "PromotionEvent.h"
#include"..\Rest\Restaurant.h"
PromotionEvent::PromotionEvent(int eTime, int oID, int eMoney):Event(eTime, oID)
{
	extraMoney = (eMoney>0)?eMoney:100;
}

void PromotionEvent::Execute(Restaurant* pRest) //Senku ^_^
{
	
	/*int ID = this->getOrderID();*/
	//Order* pOrd = pRest->GetProOrder(ID); //RERM
	pRest->GetProOrder(OrderID); //RERM
	// waiting till we decide where we will insert the promoted order (in the top of VIP Orders , push it or put it due to a piriority equation)
}
