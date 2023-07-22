#pragma once
#include "Event.h"

class CancellationEvent : public Event
{
public :
	CancellationEvent (int eTime, int oID);
	virtual void Execute(Restaurant* pRest); 

};

