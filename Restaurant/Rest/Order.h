#ifndef __ORDER_H_
#define __ORDER_H_

#include"Cook.h"
#include "..\Defs.h"
class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int size;	// number of dishes in the order 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times	
	double doneDishes; //number of done dishes
	int watingtime; //The time this order waited
	Cook* pCook; //Assigned Cook to this order 
	int Priority_eqn; //Priority equation 
	Order* pDessert; //Bonus :: Dessert order for the auto promoted guest

public:

	//---------------------->> Constructors <<----------------------------//

	Order(int ID, ORD_TYPE r_Type);
	Order(int ID, ORD_TYPE r_Type , int size , double money , int arrivalTime);

	//---------------------->> Destructor <<----------------------------//

	virtual ~Order();

	//----------------------------Getters-------------------------------------//

	int GetID();
	ORD_TYPE GetType() const;
	double GetMoney() const;
	int GetSize() const;
	ORD_STATUS getStatus() const;
	int getArrivalTime();
	int getwattingtime();
	int getFinishTime();
	double getDonDishes();
	int getServTime();
	Cook* getCookID();
	

	//----------------------------Setters-------------------------------------//

	void SetSize(int d);
	void setServTime(Cook*pcook);
	void setFinishTime(); 
	void setStatus(ORD_STATUS s);
	void setwatingtime(int tw);
	void setDoneDishes(double dD);
	void settotalmoney(double);
	void setCookID(Cook* pC);
	void setOrdType(ORD_TYPE ot);
	void setDessert(Order* ord);
	void setArrivaltime(int );
	//===================>>  Priority  <<==========================//
	//===================>> VIP Priority  <<===========================//

	bool operator < (Order pOrder); //oveloading operator < for priority queue and priority eqn
	int CalcPriortyVIPEqn(); // calculate and get the priority equation for VIP

	//====================>> Serving Priority <<==========================//

	bool operator >= (Order pOrder);
	int CalcPriortyServeEqn(); // calculate and get the priority equation for Serving orders

	Order getOrder(); //Convert pointer order to object order ,For operating overloading 

};

#endif