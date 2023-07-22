#pragma once

#include "..\Defs.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	double speed;		//dishes it can prepare in one clock tick (in one timestep)
	int breakTime;
	bool injured;
	int medicalrest;// we need this to determine wether the cook will get an order or not during his injury 
	                //while injured ==true,each time step we decrease the medRest by 1,and when it gets 0 we set "injured" false 
	                // if it's not 0 and there are no avaliable cooks we will set the speed of tht cook to its half and decrease the medRest each step
	                //when it's 0 and the speed is half , we reset the speed 

	bool avaliable; // show if the cook was assingned an order or not
	int orderid;
	bool was_injured_and_work;///esraa
	bool have_orde;
	ORD_TYPE ordertype;

	bool in_break;//Check if cook is in brek or not
	int counter;//Counts the number of orders done by the cook
	int doneOrderNum; //Number of orders done by the cook to determine when he will get his break 

public:

	//---------------------->> Constructors <<----------------------------//

	Cook(); // keep it for the demo to run properly
	Cook(int id, ORD_TYPE ordType, int Speed, int bTime);

	//---------------------->> Destructor <<----------------------------//

	virtual ~Cook();

	//------------------------------>> Getters <<---------------------------//

	void set_have_order(bool);
	bool get_have_order();
	void set_was_injured_and_work(bool);
	bool get_was_injured_and_work();
	int GetID() const;
	ORD_TYPE GetType() const;
	double getSpeed();
	int  getBreakTime();
	int getMedicPeriod();
	int get_counter();
	int GetdoneOrderNum();
	int getOrderId();
	ORD_TYPE getOrderType();
	bool isInjured();
	bool isAvaliable();

	//------------------------------>> Setters <<---------------------------//

	void setID(int);
	void setOrderId(int id);   
	void setOrdertype(ORD_TYPE);  
	void setType(ORD_TYPE);
	void setSpeed(double);
	void setBreakTime(int);
	void setInjured(bool);
	void setAvaliable(bool);
	void setMedicPeriod(int mP);
	void setinbreak(bool);
	bool getinbreak();
	void setcounter(int a);
	void setdoneOrderNum(int a);

		//------------------------------>> Additional Functions <<----------------------------------------------//

	void count(); //Increment Counter
	Cook getCook(); //Convert pointer cook to object cook , For operating overloading 
	bool operator < (Cook pOrder);//oveloading operator < for priority queue according to speed
	bool check_break(int);//Check if cook is in break or not

};
