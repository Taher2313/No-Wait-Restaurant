#include "Cook.h"

//---------------------->> Constructors <<----------------------------//

Cook::Cook()
{
}

Cook::Cook(int id, ORD_TYPE ordType, int Speed, int bTime)
{
	setID(id);
	setType(ordType);
	setSpeed(Speed);
	setBreakTime(bTime);
	injured = false;
	avaliable = true;
	doneOrderNum = 0;
	in_break = false;
	counter = 0;
	was_injured_and_work = false;
	have_orde = false;
}

//---------------------->> Destructor <<----------------------------//

Cook::~Cook()
{
}

//------------------------------>> Setters & Getters <<---------------------------//
void Cook::set_was_injured_and_work(bool a)
{
	was_injured_and_work = a;


}
bool Cook::get_was_injured_and_work()
{

	return was_injured_and_work;

}
void Cook::set_have_order(bool a)
{
	have_orde = a;

}
bool Cook::get_have_order()
{
	return have_orde;

}
int Cook::GetdoneOrderNum()
{
	return doneOrderNum;
}
void Cook::setdoneOrderNum(int a)
{
	doneOrderNum = a;
}
int Cook::GetID() const
{
	return ID;
}


void Cook::setinbreak(bool a)
{
	in_break = a;

}
bool Cook::getinbreak()
{
	return in_break;
}
bool Cook::check_break(int a)
{

	if (doneOrderNum == a)
	{
		doneOrderNum = 0;
		return true;

	}
	else
		return false;


}

void Cook::setcounter(int a)
{
	counter = a;
}

void Cook::count()
{
	counter++;
	
}
int  Cook::get_counter()
{
	return counter;
}

ORD_TYPE Cook::GetType() const
{
	return type;
}

double Cook::getSpeed()
{
	return speed;
}

int Cook::getBreakTime()
{
	return breakTime;
}



int Cook::getMedicPeriod()
{
	return medicalrest;
}

void Cook::setMedicPeriod(int mP)
{
	medicalrest = mP;
}

int Cook::getOrderId()
{
	return orderid;
}

ORD_TYPE Cook::getOrderType()
{
	return ordertype;
}

bool Cook::isInjured()
{
	return injured;
}

bool Cook::isAvaliable()
{
	return avaliable;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setOrderId(int id)
{
	orderid = id;
}

void Cook::setOrdertype(ORD_TYPE t)
{
	ordertype = t;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::setSpeed(double x)
{
	if (x > 0)
		speed = x;
	else
		speed = 2;
}

void Cook::setBreakTime(int x)
{
	if (x > 0)
		breakTime = x;
	else
		breakTime = 0;
}


void Cook::setInjured(bool x)
{
	injured = x;
}

void Cook::setAvaliable(bool x)
{
	avaliable = x;
}

Cook Cook::getCook() 
{
	return Cook(ID, type, speed, breakTime);
}

bool Cook::operator < (Cook pCook)  //for priority of cook's speed
{
	if (speed < pCook.speed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

