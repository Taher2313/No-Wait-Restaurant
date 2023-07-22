#pragma once
#include "Event.h"
class PromotionEvent : public Event
{
	int extraMoney;
public :
	PromotionEvent(int eTime, int oID, int eMoney);

	virtual void Execute(Restaurant* pRest);	


};

