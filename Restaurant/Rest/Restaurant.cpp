#include <cstdlib>
#include <time.h>
#include<fstream>
#include<iomanip>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


#include <iostream>

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"..\Events\CancellationEvent.h"
#include"..\Events\PromotionEvent.h"
#include"..\Generic_DS\Node.h"
#include"..\Generic_DS\Stack.h"
void Restaurant::serve_waiting_vip()
{
	int size;
	bool assign;
	bool Urgent;
	Cook* pcook;
	Order* Order_vip = nullptr;
	// VIP_Orders_PrioQueue.peekFront(Order_vip);
	assign = true;
	Urgent = true;
	int last_index = 0;

	Order** VIP_Orders_Array = VIP_Orders_PrioQueue.toArray(size);

	for (int i = 0; i < size; i++)
	{

		if (VIP_Orders_Array[i]->getwattingtime() > VIP_wait_limit)
		{
			Urgent = true;
			break;
		}
	}


		Queue<Order*> VIP_Wait;


		while (!VIP_Orders_PrioQueue.isEmpty() && Urgent)
		{
			Urgent = false;
			assign = false;

			while (VIP_Orders_PrioQueue.peekFront(Order_vip))
			{
				VIP_Orders_PrioQueue.pop();
				if (Order_vip->getwattingtime() > VIP_wait_limit)
				{
					Urgent = true;
					break;
				}
				else
				{
					VIP_Wait.enqueue(Order_vip);
				}

			}

			if (Urgent == false)
			{
				while (VIP_Wait.dequeue(Order_vip))
					VIP_Orders_PrioQueue.insert(Order_vip, 'O');
				break;
			}

			Cook** vip_in_break = VIP_Cooks_PrioQueue.toArray(size);

			for (int j = 0; j < size; j++)
			{

				if (vip_in_break[j]->isAvaliable())
				{
					vip_in_break[j]->setAvaliable(false);
					pcook = vip_in_break[j];
					assign = true;
					break;
				}
				else if (vip_in_break[j]->getinbreak())
				{
					vip_in_break[j]->setinbreak(false);
					pcook = vip_in_break[j];
					pcook->setdoneOrderNum(0);
					vip_in_break[j]->setAvaliable(false);
					assign = true;
					break;

				}
				else if (vip_in_break[j]->isInjured() && !vip_in_break[j]->get_have_order())
				{
					vip_in_break[j]->setInjured(false);
					pcook = vip_in_break[j];
					vip_in_break[j]->set_was_injured_and_work(true);
					assign = true;
					break;
				}
			}
			if (!assign)
			{
				Cook** nor_in_break = Normal_Cooks_PrioQueue.toArray(size);
				for (int j = 0; j < size; j++)
				{
					if (nor_in_break[j]->isAvaliable())
					{
						nor_in_break[j]->setAvaliable(false);
						pcook = nor_in_break[j];
						assign = true;
						break;
					}
					else if (nor_in_break[j]->getinbreak())
					{
						nor_in_break[j]->setinbreak(false);
						pcook = nor_in_break[j];
						pcook->setdoneOrderNum(0);
						nor_in_break[j]->setAvaliable(false);
						assign = true;
						break;
					}
					else if (nor_in_break[j]->isInjured() && !nor_in_break[j]->get_have_order())
					{
						nor_in_break[j]->setInjured(false);
						nor_in_break[j]->set_was_injured_and_work(true);
						pcook = nor_in_break[j];

						assign = true;
						break;
					}
				}
			}
			if (!assign)
			{
				Cook** veg_in_break = Vegan_Cooks_PrioQueue.toArray(size);
				for (int j = 0; j < size; j++)
				{
					if (veg_in_break[j]->isAvaliable())
					{
						veg_in_break[j]->setAvaliable(false);
						pcook = veg_in_break[j];
						assign = true;
						break;
					}
					else if (veg_in_break[j]->getinbreak())
					{
						veg_in_break[j]->setinbreak(false);
						veg_in_break[j]->setInjured(false);
						pcook = veg_in_break[j];
						pcook->setdoneOrderNum(0);
						pcook->setAvaliable(false);
						assign = true;
						break;
					}
					else if (veg_in_break[j]->isInjured() && !veg_in_break[j]->get_have_order())
					{
						veg_in_break[j]->setInjured(false);
						veg_in_break[j]->set_was_injured_and_work(true);
						pcook = veg_in_break[j];
						assign = true;
						break;
					}
				}
			}


			if (assign)
			{
				pcook->setAvaliable(false);// set the avalability of the that cook to false so he can't take another order untill this  order is finished
				pcook->setOrderId(Order_vip->GetID());// each cook has a data member that tells what order was assigned to him , so here we set this data member to the id of the order
				pcook->setOrdertype(Order_vip->GetType());// each cook has a data member that tells what type of order was assigned to him , so here we set this data member to the type of the order
				Order_vip->setCookID(pcook);// each order has a data member that tells to which cook the order was assigned , so here we set that data member to the id of the cook
				Order_vip->setStatus(SRV);// changing the status of the order from waiting to serving
				Order_vip->setDoneDishes(Order_vip->getDonDishes() + pcook->getSpeed());
				pcook->set_have_order(true);
				Order_vip->setServTime(pcook); // To set the order in its place in the the serving orders list according to the finish time 
				Serve_List.insert(Order_vip);// changing the status of the order from waiting to serving
				count_urgent++;
			}
			else
			{
				VIP_Orders_PrioQueue.insert(Order_vip, 'O');
				while (VIP_Wait.dequeue(Order_vip))
				{
					VIP_Orders_PrioQueue.insert(Order_vip, 'O');
				}
				break;
			}
		}
	}

void Restaurant::print_number_of_avalible_cook()//this function print total number of avalible cook of each type
{
	int a = 0;//size of array 
	int N = 0, V = 0, G = 0;//number of normal avalible cook and vip and vegan 

	Cook** norm = Normal_Cooks_PrioQueue.toArray(a);
	for (int i = 0; i < a; i++)
	{
		if (norm[i]->isAvaliable())
			N++;

	}
	Cook** vip = VIP_Cooks_PrioQueue.toArray(a);
	for (int i = 0; i < a; i++)
	{
		if (vip[i]->isAvaliable())
			V++;


	}
	Cook** veg = Vegan_Cooks_PrioQueue.toArray(a);

	for (int i = 0; i < a; i++)
	{
		if (veg[i]->isAvaliable())
		{
			G++;
		}
	}
	string init("NAC(");
	init.append(to_string(N));
	init.append(")");
	init.append("VAC(");
	init.append(to_string(V));
	init.append(")");
	init.append("GAC(");
	init.append(to_string(G));
	init.append(")");

	pGUI->PrintMessage(init, 5, 'R');

}

void Restaurant::Dynamic_Deallocation()
{
	// deallocate cooks

	Cook* pCook;
	Order* pOrd;
	for (int i = 0; i < count_N_Cooks; i++)
	{
		Normal_Cooks_PrioQueue.peekFront(pCook);
		Normal_Cooks_PrioQueue.pop();
		delete pCook;
	}
	for (int i = 0; i < count_VG_Cooks; i++)
	{
		Vegan_Cooks_PrioQueue.peekFront(pCook);
		Vegan_Cooks_PrioQueue.pop();
		delete pCook;
	}
	for (int i = 0; i < count_VIP_Cooks; i++)
	{
		VIP_Cooks_PrioQueue.peekFront(pCook);
		VIP_Cooks_PrioQueue.pop();
		delete pCook;
	}

	// deallocate orders
	for (int i = 0; i < count_Orders; i++)
	{
		if(Finish_Queue.dequeue(pOrd))
		delete pOrd;
	}

}

void  Restaurant::Reduce_avaliblity_cook()//Reduce break time
{
	Cook* pCook;
	int size = 0;
	//--------------------------Normal----------------------------------//
	Cook** Demo_Cooks_Array = Normal_Cooks_PrioQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pCook = Demo_Cooks_Array[i];
		if (pCook->getinbreak()&&!pCook->get_have_order())//if the cook in break 
		{
			if ((pCook->get_counter()) == (pCook->getBreakTime() - 1))//if he take his break
			{
				pCook->setcounter(0);//reset counter 
				pCook->setAvaliable(true);//make the cook avalible
				pCook->setinbreak(false);//and he isnnot in break durtion
			}
			else
				pCook->count();// increasing counter
		}
	}


	//------------------------------vegan----------------------------------//
	Demo_Cooks_Array = Vegan_Cooks_PrioQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{

		pCook = Demo_Cooks_Array[i];

		if (pCook->getinbreak() && !pCook->get_have_order())//if the cook in break 
		{

			if ((pCook->get_counter()) == pCook->getBreakTime() - 1)
			{
				pCook->setcounter(0);
				pCook->setAvaliable(true);
				pCook->setinbreak(false);
			}
			else
				pCook->count();
		}
	}

	//---------------------------vip---------------------------------------//
	Demo_Cooks_Array = VIP_Cooks_PrioQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		pCook = Demo_Cooks_Array[i];

		if (pCook->getinbreak() && !pCook->get_have_order())//if the cook in break 
		{
			// modify name to increamentNumOrdDone     56789
			if ((pCook->get_counter()) == pCook->getBreakTime() - 1)
			{
				pCook->setcounter(0); // 00000      add to the whole section
				pCook->setAvaliable(true);
				pCook->setinbreak(false);
			}
			else
				pCook->count();
		}
	}
}
bool Restaurant::RemoveFromnList(int id)
{
	int size = 0;
	Order* pORd;
	pORd = Normal_Orders_List.remove(id);
	if (pORd != nullptr)
		return true;
	else
		return false;
}

template < typename T>
void Restaurant::FillDrawingList(T* obj)
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	pGUI->AddToDrawingList(obj);
}
void Restaurant::GetProOrder(int id)
{
	int size = 0;
	int n = 0;// size
	Order* pOrd = NULL;
	bool served = false;
	bool finish = false;
	// convert the finish queue to array to access its elements
	Order** finish_order = Finish_Queue.toArray(n);
	// check if the order is finished
	for (int k = 0; k < n; k++)
	{
		if (finish_order[k]->GetID() == id)
		{
			finish = true;
			break;
		}
	}
	if (finish)// if the order is done print message and it can't be pronoted

	{
		char iD[10];
		itoa(id, iD, 10);
		string init(" order finished  we cannot promote it: ID->");
		string add(iD);
		init.append(add);
		pGUI->PrintMessage(init, 1, 'R');

		return;
	}
	//check if the order is served 
	served = Serve_List.search(id);

	if (served)  // if served print the following message and it can't be promoted
	{
		char iD[10];
		itoa(id, iD, 10);
		string init(" order served we cannot promote it:ID->");
		string add(iD);
		init.append(add);
		pGUI->PrintMessage(init, 1, 'R');

		return;
	}
	pOrd = Normal_Orders_List.remove(id);

	if (pOrd) // check if there is an order with the sent data
	{
		pOrd->setOrdType(TYPE_VIP);
		VIP_Orders_PrioQueue.insert(pOrd, 'V');
	}
}
void Restaurant::Generate_R()
{
	float R;
	Cook* pCook = nullptr;
	R = (rand() % 101) / 100.0;
	if ( R <= injuring_probability)
	{
		if (!Serve_List.isEmpty())
		{
			Order* pOrd = nullptr;
			Serve_List.seeFirstElement(pOrd);
			pCook = pOrd->getCookID();
			if (!pCook->isInjured())
			{
				if (!pCook->get_was_injured_and_work())
				{
					pCook->setInjured(true); // we set him injured
					pCook->setMedicPeriod(getmedicalRest());  // we set the medical period of the cook to the medical rest that was read from the input file in the function load file in restaurant.cpp
					pCook->setSpeed(pCook->getSpeed() / 2);   // we always set the speed of the cook to its half if he is injured , 
					count_injured++;                          //as if an order was assigned to him during his medical rest he should work with half of his speed ,
				}									          //so it won't matter if he didn't work during his medical rest and his speed = its half 
			}
		}
	}
}

void Restaurant::Decrement_Orders_Count_For_Cancellation()
{
	count_Orders--;
	count_N_Orders--;
}

void Restaurant::setmedicalRest(int mR)
{
	medicalRest = mR;
}

int Restaurant::getmedicalRest()
{
	return medicalRest;
}




//Default Constructor
Restaurant::Restaurant()
{
	//Initiallize data members

	timeStep = 1;
	pGUI = NULL;
	Total_num_Ser_Normal_Ord = 0;
	Total_num_Ser_Vegan_Ord = 0;
	Total_num_Ser_Vip_Ord = 0;

	count_Orders = 0;
	count_N_Orders = 0;
	count_VG_Orders = 0;
	count_VIP_Orders = 0;

	count_Cooks = 0;
	count_N_Cooks = 0;
	count_VG_Cooks = 0;
	count_VIP_Cooks = 0;

	count_autoPromoted = 0;
	count_urgent = 0;
	count_injured = 0;
}

//The simulator which choose which mode to work
void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getGUIMode(); // get the mode from the user


	ofstream outputFile;

	string namefile;      // output file name
	pGUI->ClearStatusBar();

	if (mode == 0)
		pGUI->PrintMessage(" InterActive Mode : please enter output file name ", 1, 'L');
	else if (mode == 1)
		pGUI->PrintMessage(" Step by Step Mode : please enter output file name ", 1, 'L');
	else if (mode == 2)
		pGUI->PrintMessage(" Silent Mode : please enter output file name ", 1, 'L');

	namefile = pGUI->GetString().c_str();
	outputFile.open(namefile, ios::out); //Open the output file

	srand(time(NULL));
	string filename;                     // input file name
	pGUI->ClearStatusBar();

	if (mode == 0)
		pGUI->PrintMessage(" InterActive Mode : please enter input file name ", 1, 'L');
	else if (mode == 1)
		pGUI->PrintMessage(" Step by Step Mode : please enter input file name ", 1, 'L');
	else if (mode == 2)
		pGUI->PrintMessage(" Silent Mode : please enter input file name ", 1, 'L');


	filename = pGUI->GetString().c_str();

	ifstream file(filename);

	while (!file.is_open()) // check that the name matches an existing file
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage(" No file matches the input name : please enter a vaild file name  ", 1, 'L');
		filename = pGUI->GetString().c_str();
		file.open(filename, ios::in);
	}

	loadFile(file);  // read them from the file


	pGUI->ClearStatusBar();
	if (mode == 0)
	{
		pGUI->PrintMessage(" Ineractive Mode : please click to start simulation ", 1, 'L');
		pGUI->waitForClick(); //Interactive mode wait for a click to continue simulation
	}
	else if (mode == 1)
	{
		pGUI->PrintMessage(" Step by Step Mode : please click to start simulation ", 1, 'L');
		pGUI->waitForClick(); //Step by Step mode wait for a click to continue simulation
	}

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || !Serve_List.isEmpty() || !Normal_Orders_List.isEmpty() || !Vegan_Orders_Queue.isEmpty() || !VIP_Orders_PrioQueue.isEmpty())
	{

		Generate_R();                                        // 1

		if (mode == 0 || mode == 1)
		{
			PrintingTimestep();                              // 2
		}

		Reduce_avaliblity_cook();                            // 3

		ReduceMedicalRest();                                 // 4

		ExecuteEvents(timeStep);	                         // 5

		if (mode == 0 || mode == 1)
		{
			DrawingAllAssignedCooksInTheLastTimeTimestep();  // 6
		}
		
		MovingOrdersFromServingToDone();                    //7  

		AssigningOrdersToCooks();                           //9

		AutopromotionOfOrders();                             // 10

		serve_waiting_vip();                                   //8  

		if (mode == 0 || mode == 1)
		{
			print_number_of_avalible_cook();                 // 11

			Print_Injured_Cooks();                           // 12

			Print_Cooks_In_Break();                          // 13

			DrawAllCooks();                                  // 14
		}

		DrawingAllWaitingOrders(mode);                       // 15

		if (mode == 0 || mode == 1)
		{
			DrawingAllCurrentlyServingOrders();              //  16

			FinshingOfDrawingAllDoneOrders();                // 17
		}

		if (mode == 0 || mode == 1)
		{
			pGUI->UpdateInterface();

			if (mode == 0)
				pGUI->waitForClick();
			else
				Sleep(1000); //Step By Step mode continue simulation after one second

			timeStep++;	//advance timestep
			pGUI->ResetDrawingList();
		}
		else
			timeStep++;	//advance timestep

	}

	OutputFileOptimization(outputFile);                      // 18

	outputFile.close();


	if (mode == 0 || mode == 1)
	{
		pGUI->ClearStatusBar();
		pGUI->PrintMessage("No more orders nor events found , click to END program", 1, 'L');
		pGUI->waitForClick();
	}
	Dynamic_Deallocation();                                  // 19

}

//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() != CurrentTimeStep)	//no more events at current timestep
			return;
		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

//Class Destructor
Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI; //deallocate GUI object from memory if they exists
}

//Return the current timestep
int Restaurant::getTimeStep()
{
	return timeStep;
}


void Restaurant::loadFile(ifstream& fileName)

{
	fileName >> count_N_Cooks >> count_VG_Cooks >> count_VIP_Cooks;
	count_Cooks = count_N_Cooks + count_VG_Cooks + count_VIP_Cooks;


	int normal_min_speed;
	int normal_max_speed;

	int vegan_min_speed;
	int vegan_max_speed;

	int VIP_min_speed;
	int VIP_max_speed;

	fileName >> normal_min_speed >> normal_max_speed >> vegan_min_speed >> vegan_max_speed >> VIP_min_speed >> VIP_max_speed;


	fileName >> order_before_break;//no one //number of order before break

	int normal_min_break_time;
	int normal_max_break_time;

	int vegan_min_break_time;
	int vegan_max_break_time;

	int VIP_min_break_time;
	int VIP_max_break_time;

	//	fileName >> order_before_break;//no one //number of order before break

	fileName >> normal_min_break_time >> normal_max_break_time >> vegan_min_break_time >> vegan_max_break_time >> VIP_min_break_time >> VIP_max_break_time;

	fileName >> injuring_probability >> medicalRest;

	int eventCount;// number of Event 

	fileName >> autoPromotionLimit >> VIP_wait_limit >> eventCount;

	// -------------------------------------- cooks section ---------------------------------\\

	char cookType;
	int cookID = 1;
	double cookSpeed;
	int breakTime;
	Cook* pCook;

	for (int i = 0; i < count_N_Cooks; i++)
	{
		cookSpeed = rand() % (normal_max_speed - normal_min_speed + 1) + normal_min_speed;
		breakTime = rand() % (normal_max_break_time - normal_min_break_time + 1) + normal_min_break_time;
		pCook = new Cook(cookID, TYPE_NRM, cookSpeed, breakTime);
		Normal_Cooks_PrioQueue.insert(pCook, 'C');  ///add cook in his queue
		cookID++;
	}
	for (int i = 0; i < count_VG_Cooks; i++)
	{

		cookSpeed = rand() % (vegan_max_speed - vegan_min_speed + 1) + vegan_min_speed;
		breakTime = rand() % (vegan_max_break_time - vegan_min_break_time + 1) + vegan_min_break_time;
		pCook = new Cook(cookID, TYPE_VGAN, cookSpeed, breakTime);
		Vegan_Cooks_PrioQueue.insert(pCook, 'C');
		cookID++;
	}
	for (int i = 0; i < count_VIP_Cooks; i++)
	{

		cookSpeed = rand() % (VIP_max_speed - VIP_min_speed + 1) + VIP_min_speed;
		breakTime = rand() % (VIP_max_break_time - VIP_min_break_time + 1) + VIP_min_break_time;
		pCook = new Cook(cookID, TYPE_VIP, cookSpeed, breakTime);
		VIP_Cooks_PrioQueue.insert(pCook, 'C'); // c refers to cook
		cookID++;
	}

	// -------------------------------------- Events section ---------------------------------\\
	

	int EventTime; //time step
	int OrderID;    //order id
	int OrdSize;	        //order size	                
	double OrdMoney;	    //Total order money
	ArrivalEvent* pEvent;
	CancellationEvent* Cevent;
	bool defaultDessertCook = false;
	char eventType, ordTpe;

	for (int i = 0; i < eventCount; i++)
	{
		fileName >> eventType;
		if (eventType == 'R')
		{
			fileName >> ordTpe;
			fileName >> EventTime;
			fileName >> OrderID;
			fileName >> OrdSize;
			fileName >> OrdMoney;
			if (OrdSize < 0 || OrdMoney < 0 || EventTime < 0)//no one if ordersize , money or time nagitive donot accept it 
				continue;
			count_Orders++; //increment number of orders
			//----------------------------------Normal order----------------------------------------------// 
			if (ordTpe == 'N')
			{
				if (Normal_Cooks_PrioQueue.isEmpty() && VIP_Cooks_PrioQueue.isEmpty() && Vegan_Cooks_PrioQueue.isEmpty())
					continue;//if no cooks to serve order order refused

				// vegan is added because normal orders will be automatically promoted vagen cooks can do them 
				pEvent = new ArrivalEvent(EventTime, OrderID, TYPE_NRM, OrdSize, OrdMoney);//create a new order
				count_N_Orders++; //increment number of normal order //outputFile optimization
				defaultDessertCook = true;//assign a default Dessert cook if the orde autoprometed

			}
			//-------------------------------------vegan order------------------------------------------------------//
			else if (ordTpe == 'G')
			{
				if (Vegan_Cooks_PrioQueue.isEmpty())  //not accept if no cooks vegan to serve order
					continue;

				pEvent = new ArrivalEvent(EventTime, OrderID, TYPE_VGAN, OrdSize, OrdMoney);
				count_VG_Orders++;
			}
			//------------------------------------------ViP----------------------------------//
			else if (ordTpe == 'V')
			{
				if (Normal_Cooks_PrioQueue.isEmpty() && VIP_Cooks_PrioQueue.isEmpty() && Vegan_Cooks_PrioQueue.isEmpty())
					continue;              //   the order donot accept if no cooks serve it

				pEvent = new ArrivalEvent(EventTime, OrderID, TYPE_VIP, OrdSize, OrdMoney);
				count_VIP_Orders++;
			}

			else
				continue; //if invalid char 
			EventsQueue.enqueue(pEvent);//add order in Event Queue

		}
		else if (eventType == 'X') //cancellation
		{
			fileName >> EventTime;
			fileName >> OrderID;
			Cevent = new CancellationEvent(EventTime, OrderID);
			EventsQueue.enqueue(Cevent);

		}
		else if ('P') //promotion
		{

			fileName >> EventTime >> OrderID >> OrdMoney;
			PromotionEvent* Pevent = new PromotionEvent(EventTime, OrderID, OrdMoney);
			EventsQueue.enqueue(Pevent);

		}
		else
			continue;// if invalid char

	}
	fileName.close();
}

void Restaurant::PrintingTimestep()
{
	// clear the status bar
	pGUI->ClearStatusBar();

	//print current timestep
	char timestep[10];
	itoa(timeStep, timestep, 10);

	// concatenation

	string init("The current timestep is : ");
	string add(timestep);
	init.append(add);
	pGUI->PrintMessage(init, 1, 'L');

}


void Restaurant::ReduceMedicalRest()
{
	Cook* pCook; // to store the injured cook 
	int size = 0;

	Cook** Demo_Cooks_Array = Normal_Cooks_PrioQueue.toArray(size);   // storing the elements of the priority queue in an array to be able to go through all of them 
	for (int i = 0; i < size; i++)  // traversing the array
	{
		pCook = Demo_Cooks_Array[i];
		if (pCook->isInjured() && !pCook->get_have_order())  // check if the cook is injured or not
		{ // medicalPeriod is an int variable , 
			if (pCook->getMedicPeriod() > 0)   //if the cook hasn't finished his medical rest yet , reduce medicalPeriod by 1 to indicate that he has spent one more time step in medical rest 
				pCook->setMedicPeriod(pCook->getMedicPeriod() - 1);  // reducing medicalPeriod
			else  // if the medicalPeriod is 0 that tells that the cook has finished his medical rest 
			{
				pCook->setInjured(false);  // so we set him uninjured 
				pCook->setAvaliable(true);
				pCook->setSpeed(pCook->getSpeed() * 2);  // his speed is back to its original 
				// we choose to make the execute of the injured event to always set the speed of the cook to its half and when he finishes his medical rest we set his speed back to its original 
				// that's to make it easier if an order was assigned to the injured cook , as in this case he should work with half of his speed , and in case if nothing was assigned to him , reducing his speed won't be a big deal
			}
		}
	}
	Demo_Cooks_Array = Vegan_Cooks_PrioQueue.toArray(size);    // storing the elements of the priority queue in an array to be able to go through all of them 
	for (int i = 0; i < size; i++)    // traversing the array
	{
		pCook = Demo_Cooks_Array[i];
		if (pCook->isInjured() && !pCook->get_have_order())  // check if the cook is injured or not
		{ // medicalPeriod is an int variable ,
			if (pCook->getMedicPeriod() > 0)    //if the cook hasn't finished his medical rest yet , reduce medicalPeriod by 1 to indicate that he has spent one more time step in medical rest 
				pCook->setMedicPeriod(pCook->getMedicPeriod() - 1);     // reducing medicalPeriod
			else    // if the medicalPeriod is 0 that tells that the cook has finished his medical rest 
			{
				pCook->setInjured(false);     // so we set him uninjured 
				pCook->setAvaliable(true);
				pCook->setSpeed(pCook->getSpeed() * 2);     // his speed is back to its original 
				// we choose to make the execute of the injured event to always set the speed of the cook to its half and when he finishes his medical rest we set his speed back to its original 
				// that's to make it easier if an order was assigned to the injured cook , as in this case he should work with half of his speed , and in case if nothing was assigned to him , reducing his speed won't be a big deal
			}
		}

	}
	Demo_Cooks_Array = VIP_Cooks_PrioQueue.toArray(size);   // storing the elements of the priority queue in an array to be able to go through all of them 
	for (int i = 0; i < size; i++)   // traversing the array
	{
		pCook = Demo_Cooks_Array[i];
		if (pCook->isInjured() && !pCook->get_have_order())  // check if the cook is injured or not
		{ // medicalPeriod is an int variable ,
			if (pCook->getMedicPeriod() > 0)     //if the cook hasn't finished his medical rest yet , reduce medicalPeriod by 1 to indicate that he has spent one more time step in medical rest 
				pCook->setMedicPeriod(pCook->getMedicPeriod() - 1);     // reducing medicalPeriod
			else    // if the medicalPeriod is 0 that tells that the cook has finished his medical rest 
			{
				pCook->setInjured(false);     // so we set him uninjured
				pCook->setAvaliable(true);
				pCook->setSpeed(pCook->getSpeed() * 2);     // his speed is back to its original 
				// we choose to make the execute of the injured event to always set the speed of the cook to its half and when he finishes his medical rest we set his speed back to its original 
				// that's to make it easier if an order was assigned to the injured cook , as in this case he should work with half of his speed , and in case if nothing was assigned to him , reducing his speed won't be a big deal
			}
		}
	}
	
}

void Restaurant::MovingOrdersFromServingToDone()
{
	
	int size;
	Order* pOrd; // Order pointer
	Stack<Order*> S1; //Create stack object to help in sorting finish orders ascendingly according to serving time

	if (!Serve_List.isEmpty()) //Check if serve list is not empty
	{
		size = 0; // Initiallize size with zero and change its value according to the next array size
		Order** serve_Orders_Array = Serve_List.toArray(size); //Change serve list to array to traverse on it
		for (int i = 0; i < size; i++)
		{
			pOrd = serve_Orders_Array[i];
			if (pOrd->getDonDishes() >= pOrd->GetSize()) //Check if the finish time for the order has come according to number of order's done
			{
				Serve_List.remove(pOrd); //if yes, then remove the order from serve list
				pOrd->setStatus(DONE); // change its tsatus to done instead of serve
				Cook* t = pOrd->getCookID(); //Change some parameters for the cook assigned to the done order
				t->setdoneOrderNum(t->GetdoneOrderNum() + 1); // increment number of orders made by this cook
				if (t->isInjured())
					t->setAvaliable(false);
				else
				{
					t->setAvaliable(true); // Make the cook available again
				}
				t->set_have_order(false);
				if (t->GetdoneOrderNum() == order_before_break && t->getBreakTime() != 0)
				{
					if (t->get_was_injured_and_work())
					{
						t->setSpeed(t->getSpeed() * 2);
						t->set_was_injured_and_work(false);
						t->setdoneOrderNum(0);   //Reset the done order number for the cook after finishing the break
						t->setAvaliable(false); // Don't Make the cook available if it is his break time
						t->setinbreak(true); //You worked alot , Have some break according to general break number of orders
					}
					else if (t->isInjured())
					{
						t->setAvaliable(false);
						t->setdoneOrderNum(0);
						t->setinbreak(false);
					}
					else
					{
						t->setdoneOrderNum(0);   //Reset the done order number for the cook after finishing the break
						t->setAvaliable(false); // Don't Make the cook available if it is his break time
						t->setinbreak(true); //You worked alot , Have some break according to general break number of orders
					}
					
				}
				pOrd->setCookID(nullptr); // Order is finished then no cook is assigned to it
				S1.push(pOrd); // put the finished order in the helper stack
				//increment number of orders which has done from serving according to the order type
				if (pOrd->GetType() == TYPE_NRM)
					++Total_num_Ser_Normal_Ord;
				else if (pOrd->GetType() == TYPE_VGAN)
					++Total_num_Ser_Vegan_Ord;
				else if (pOrd->GetType() == TYPE_VIP)
					++Total_num_Ser_Vip_Ord;
			}
			else
				pOrd->setDoneDishes(pOrd->getDonDishes() + (pOrd->getCookID()->getSpeed())); //Increment number of done dishes for this order according to speed of cook -speed is number of dishes-
		}
		//To have the right order of finished order descendingly according to FT and ascendingly according to ST
		//then pop the stack into a queue
		Order* helper;
		while (S1.pop(helper))
		{
			Finish_Queue.enqueue(helper);
		}
	}
	   	

}

void Restaurant::AssigningOrdersToCooks()
{

	
	Cook* pcook;
	int size = 0;
	Cook** Demo_Cooks_Array;
	Order* porder;
	bool assigned = false;
	//-------------------------------------------- VIP --------------------------------------\\

	while (!VIP_Orders_PrioQueue.isEmpty())// getting into the queue
	{
		assigned = false;

		VIP_Orders_PrioQueue.peekFront(porder);

		//----------------------------------------- VIP cooks -------------------------------------------

		Demo_Cooks_Array = VIP_Cooks_PrioQueue.toArray(size);// storing the queue's element in an array to get the avaialble cook
		pcook = nullptr;

		for (int i = 0; i < size; i++)
		{
			if (Demo_Cooks_Array[i]->isAvaliable())
			{
				pcook = Demo_Cooks_Array[i];
				assigned = true;
				break;
			}
		}
		//----------------------------------------------------- Normal cooks  --------------------------------------------------------


		if (!assigned)
		{
			Demo_Cooks_Array = Normal_Cooks_PrioQueue.toArray(size);// storing the queue's element in an array to get the avaialble cook
			pcook = nullptr;

			for (int i = 0; i < size; i++)
			{
				if (Demo_Cooks_Array[i]->isAvaliable())
				{
					pcook = Demo_Cooks_Array[i];
					assigned = true;
					break;
				}
			}
		}


		// --------------------------------------------- vegan cooks ------------------------------------------------------

		if (!assigned)
		{
			Demo_Cooks_Array = Vegan_Cooks_PrioQueue.toArray(size);// storing the queue's element in an array to get the avaialble cook
			pcook = nullptr;

			for (int i = 0; i < size; i++)
			{
				if (Demo_Cooks_Array[i]->isAvaliable())
				{
					pcook = Demo_Cooks_Array[i];
					assigned = true;
					break;
				}
			}
		}

		if (assigned)// if the order is assigned to an available cook
		{
			pcook->setAvaliable(false);// set the avalability of the that cook to false so he can't take another order untill this  order is finished
			pcook->setOrderId(porder->GetID());// each cook has a data member that tells what order was assigned to him , so here we set this data member to the id of the order
			pcook->setOrdertype(porder->GetType());// each cook has a data member that tells what type of order was assigned to him , so here we set this data member to the type of the order
			VIP_Orders_PrioQueue.pop();// dequeuing the order from the queue so it won't be assigned to another cook in parallel with that cook
			porder->setCookID(pcook);// each order has a data member that tells to which cook the order was assigned , so here we set that data member to the id of the cook
			porder->setStatus(SRV);// changing the status of the order from waiting to serving
			porder->setDoneDishes(pcook->getSpeed() + porder->getDonDishes());
			porder->setServTime(pcook); // To set the order in its place in the the serving orders list according to the finish time 
			pcook->set_have_order(true);
			Serve_List.insert(porder); // changing the status of the order from waiting to serving
		}
		else// there no available cook
			break;
	}

	//-------------------------------------------------------------------------- vegan ---------------------------------------------------\\
	//======================================================================================================================================



	// same like the previous section but here we search for vegan orders
	while (!Vegan_Orders_Queue.isEmpty())
	{
		assigned = false;
		Vegan_Orders_Queue.peekFront(porder);

		Demo_Cooks_Array = Vegan_Cooks_PrioQueue.toArray(size);// storing the queue's element in an array to get the avaialble cook
		pcook = nullptr;

		for (int i = 0; i < size; i++)
		{
			if (Demo_Cooks_Array[i]->isAvaliable())
			{
				pcook = Demo_Cooks_Array[i];
				assigned = true;
				break;
			}
		}
		if (assigned)
		{
			pcook->setAvaliable(false);// set the avalability of the that cook to false so he can't take another order untill this  order is finished
			pcook->setOrderId(porder->GetID());// each cook has a data member that tells what order was assigned to him , so here we set this data member to the id of the order
			pcook->setOrdertype(porder->GetType());// each cook has a data member that tells what type of order was assigned to him , so here we set this data member to the type of the order
			Vegan_Orders_Queue.dequeue(porder);
			porder->setDoneDishes(porder->getDonDishes() + pcook->getSpeed());
			porder->setCookID(pcook);// each order has a data member that tells to which cook the order was assigned , so here we set that data member to the id of the cook
			porder->setStatus(SRV);// changing the status of the order from waiting to serving
			porder->setServTime(pcook); // To set the order in its place in the the serving orders list according to the finish time 
			pcook->set_have_order(true);
			Serve_List.insert(porder); // changing the status of the order from waiting to serving
		}
		else
			break;
	}


	//--------------------------------------------------------------------------------- Normal --------------------------------------------------------------\\
	//===========================================================================================================================================

	// same like the previous section but here we search for normal orders
	while (!Normal_Orders_List.isEmpty())
	{
		assigned = false;
		Normal_Orders_List.seeFirstElement(porder);

		Demo_Cooks_Array = Normal_Cooks_PrioQueue.toArray(size);// storing the queue's element in an array to get the avaialble cook
		pcook = nullptr;

		for (int i = 0; i < size; i++)
		{
			if (Demo_Cooks_Array[i]->isAvaliable())
			{
				pcook = Demo_Cooks_Array[i];
				assigned = true;
				break;
			}
		}
		if (!assigned)
		{

			Demo_Cooks_Array = VIP_Cooks_PrioQueue.toArray(size);// storing the queue's element in an array to get the avaialble cook
			pcook = nullptr;

			for (int i = 0; i < size; i++)
			{
				if (Demo_Cooks_Array[i]->isAvaliable())
				{
					pcook = Demo_Cooks_Array[i];
					assigned = true;
					break;
				}
			}
		}

		if (assigned)
		{
			pcook->setAvaliable(false);
			pcook->setOrderId(porder->GetID());
			pcook->setOrdertype(porder->GetType());
			Normal_Orders_List.removeFirst(porder);
			porder->setCookID(pcook);
			porder->setDoneDishes(porder->getDonDishes() + pcook->getSpeed());
			porder->setStatus(SRV);
			porder->setServTime(pcook);
			pcook->set_have_order(true);
			Serve_List.insert(porder);
		}
		else
			break;
	}
	
}


void Restaurant::AutopromotionOfOrders()
{
	
	Order* porder; //Create pointer of order

	//Check first if not served
	if (!Normal_Orders_List.isEmpty())
	{
		int size_norm = 0; // Initiallize the size which will be updated after creating the next array
		Order** norm_Orders_Array = Normal_Orders_List.toArray(size_norm); //put the list in array to easily traverse on it
		for (int i = 0; i < size_norm; i++)
		{
			porder = norm_Orders_Array[i];

			if ((timeStep - porder->getArrivalTime()) == autoPromotionLimit) //Check if the order has waited a time which equals the auto promotion limit
			{
				count_autoPromoted++; //Promoted then increment number of auto promoted orders out of total normal orders
				Normal_Orders_List.removeFirst(porder); //remove the order from normal list
				porder->setOrdType(TYPE_VIP); //change the order type to VIP
				porder->setArrivaltime(porder->getArrivalTime()+ autoPromotionLimit);
				porder->setwatingtime(0);
				VIP_Orders_PrioQueue.insert(porder, 'V'); //put the autopromoted order into the VIP Priority Queue
				
			}
			else
				break;
		}
	}

	
}

void Restaurant::DrawAllCooks()
{

	int size;
	Cook** Demo_Cooks_Array;
	Cook* pCook;
	   		 	  	  
	size = 0;

	// ------------------------- draw normal cooks ---------------------------\\

	// prepare the output file

	// covert the priority queue to array to access its elements
	Demo_Cooks_Array = Normal_Cooks_PrioQueue.toArray(size);
	// loop on the array to draw the cooks
	for (int i = 0; i < size; i++)
	{
		pCook = Demo_Cooks_Array[i];

		if (Demo_Cooks_Array[i]->isAvaliable())   // if the cook is avaliable draw it and add it to the output file
		{
			FillDrawingList(pCook);
		}
	}

	// ------------------------- draw vegan cooks ---------------------------\\

	// covert the priority queue to array to access its elements
	Demo_Cooks_Array = Vegan_Cooks_PrioQueue.toArray(size); //for waiting orders

	// loop on the array to draw the cooks
	for (int i = 0; i < size; i++)
	{
		pCook = Demo_Cooks_Array[i];

		if (pCook->isAvaliable())  // if the cook is avaliable draw it and add it to the output file
		{
			FillDrawingList(pCook);
		}
	}

	// ------------------------- draw vip cooks ---------------------------\\

	// covert the priority queue to array to access its elements
	Demo_Cooks_Array = VIP_Cooks_PrioQueue.toArray(size);

	// loop on the array to draw the cooks
	for (int i = 0; i < size; i++)
	{
		pCook = Demo_Cooks_Array[i];

		if (Demo_Cooks_Array[i]->isAvaliable())  // if the cook is avaliable draw it and add it to the output file
		{
			FillDrawingList(pCook);
		}

	}
	 

}

void Restaurant::DrawingAllAssignedCooksInTheLastTimeTimestep()
{
	// it's required to print what orders was assigned in the last time step to whom 
	// the cook type should be written first then his id then in brackets the order type and it's id , N6(V2)  vip order with id 2 was assigned to normal cook with id 6
	

	int size;
	Cook* pCook;
	string init;

	size = 0;
	Order** Last_Assigned_Array = Serve_List.toArray(size);
	int id;
	init = "";
	int line = 2;
	bool stop = false;
	for (int i = 0; i < size; i++)
	{
		if ((Last_Assigned_Array[i]->getArrivalTime() + Last_Assigned_Array[i]->getwattingtime()) == timeStep - 1)  // check if the order was assigned in the last time step
		{
			if (i != 0 && i % 8 == 0)  // the area where we would write the messages only accommodates 8 words , so here we check if we reached the limit or not
			{ // if so , we print them and then we print the others in another line
				pGUI->PrintMessage(init, line, 'R');
				init = "";
				++line;
			}
			else  // if not, we continue storing the words to print them as one message
			{
				init.append("   ");
				pCook = Last_Assigned_Array[i]->getCookID();  // get the cook id to print it
				if (pCook->GetType() == TYPE_NRM) // check the cook type
				{
					init.append("N");
					id = pCook->GetID();
					init.append(to_string(id));
					init.append("(");
					if (Last_Assigned_Array[i]->GetType() == TYPE_NRM) // check the order type
						init.append("N");
					else if (Last_Assigned_Array[i]->GetType() == TYPE_VGAN)// check the order type
						init.append("G");
					else if (Last_Assigned_Array[i]->GetType() == TYPE_VIP)// check the order type
						init.append("V");

					init.append(to_string(Last_Assigned_Array[i]->GetID())); // get the order id
					init.append(") ");
				}
				else if (Last_Assigned_Array[i]->getCookID()->GetType() == TYPE_VGAN)// check the cook type
				{
					init.append("G");
					id = pCook->GetID();
					init.append(to_string(id));
					init.append("(");
					if (Last_Assigned_Array[i]->GetType() == TYPE_NRM)// check the order type
						init.append("N");
					else if (Last_Assigned_Array[i]->GetType() == TYPE_VGAN)// check the order type
						init.append("G");
					else if (Last_Assigned_Array[i]->GetType() == TYPE_VIP)// check the order type
						init.append("V");

					init.append(to_string(Last_Assigned_Array[i]->GetID()));// get the order id
					init.append(") ");
				}
				else if (Last_Assigned_Array[i]->getCookID()->GetType() == TYPE_VIP)// check the cook type
				{
					init.append("V");
					id = pCook->GetID();
					init.append(to_string(id));
					init.append("(");
					if (Last_Assigned_Array[i]->GetType() == TYPE_NRM)// check the order type
						init.append("N");
					else if (Last_Assigned_Array[i]->GetType() == TYPE_VGAN)// check the order type
						init.append("G");
					else if (Last_Assigned_Array[i]->GetType() == TYPE_VIP)// check the order type
						init.append("V");

					init.append(to_string(Last_Assigned_Array[i]->GetID()));// get the order id
					init.append(") ");
				}

			}

		}
	}

	pGUI->PrintMessage(init, line, 'R'); // print the message 
		
}

void Restaurant::DrawingAllWaitingOrders(int mode)
{
	   		 	  

	int size1, size2, size3, sizeTotal; // the size of all arrays that contain waiting orders
	string init;
	Order* pOrd;

	// preparing the output file and GUI to recive waiting orders  

	string wait("\n #Waiting orders at current timeStep : ");
	init.append(wait);

	// convert all waiting orders to arrays to access them

	Order** Normal_Orders_Array = Normal_Orders_List.toArray(size1); //for waiting orders
	Order** Vegan_Orders_Array = Vegan_Orders_Queue.toArray(size2); //for waiting orders
	Order** VIP_Orders_Array = VIP_Orders_PrioQueue.toArray(size3); //for waiting orders


	sizeTotal = size1 + size2 + size3;

	Order** All_Orders_Array = new Order * [sizeTotal]; //for waiting orders
	int count = 0;
	int i;

	// collect all orders in a larger array to sort them so them are printed according to 
	// the arrival time

	for (i = 0; i < size1; i++)
	{
		All_Orders_Array[count] = Normal_Orders_Array[i];
		count++;
	}
	for (i = 0; i < size2; i++)
	{
		All_Orders_Array[count] = Vegan_Orders_Array[i];
		count++;
	}
	for (i = 0; i < size3; i++)
	{
		All_Orders_Array[count] = VIP_Orders_Array[i];
		count++;
	}

	// sort all orders using heap sort
	if (mode == 0 || mode == 1)
		heapSortForWaitOrders(All_Orders_Array, sizeTotal);

	// loop on the sorted array and draw orders

	for (int i = 0; i < sizeTotal; i++)
	{
		pOrd = All_Orders_Array[i];
		if (mode == 0 || mode == 1)
			FillDrawingList(pOrd);                             // draw orders
		pOrd->setwatingtime(pOrd->getwattingtime() + 1);   // increment waiting time 

	}

	if (mode == 0 || mode == 1)
	{
		// print number of normal waiting orders in GUI
		char S[10];
		string N("N ");
		wait.append(N);
		itoa(size1, S, 10);
		wait.append(S);

		// print number of vegan waiting orders in GUI
		string V(" ,VG ");
		wait.append(V);
		itoa(size2, S, 10);
		wait.append(S);

		// print number of VIP waiting orders in GUI

		string VP(" ,VIP ");
		wait.append(VP);
		itoa(size3, S, 10);
		wait.append(S);

		pGUI->PrintMessage(wait, 2, 'L');
	   		 	  
	}
}

void Restaurant::DrawingAllCurrentlyServingOrders()
{

	int size;
	Order* porder;


	// prepare the output file to recive served orders
	Order** Demo_ServedOrders_Array = Serve_List.toArray(size);
	for (int i = 0; i < size; i++)
	{
		porder = Demo_ServedOrders_Array[i];
		FillDrawingList(porder);    // draw the order

	}

		 
}


void Restaurant::FinshingOfDrawingAllDoneOrders()
{

	int size;
	string init;
	string add;

	// prepare the output file to recive the done orders
	size = 0;

	// covert the queue to array to access its elements
	Order** Finish_Orders_Array = Finish_Queue.toArray(size);

	// loop on the array to draw the done orders
	for (int i = 0; i < size; i++)
	{
		FillDrawingList(Finish_Orders_Array[i]);   // draw the order
	}


	// print the total served number of normal orders

	char Normnum[10];
	itoa(Total_num_Ser_Normal_Ord, Normnum, 10);

	init = "Served NRM Ord:";
	init.append(Normnum);
	char Vegnum[10];

	// print the total served number of vegan orders

	itoa(Total_num_Ser_Vegan_Ord, Vegnum, 10);
	init.append(" -Served VGN Ord:");
	add = Vegnum;
	init.append(add);

	char Vipnum[10];

	// print the total served number of vip orders

	itoa(Total_num_Ser_Vip_Ord, Vipnum, 10);
	init.append(" -Served VIP Ord:");
	add = Vipnum;
	init.append(add);

	// print the total served number of dessert orders


	pGUI->PrintMessage(init, 3, 'L');
	  
}

void Restaurant::OutputFileOptimization(ofstream& outputFile)
{
	 //outputFile optimization as sample one in documentation


	int size = 0;     // Initiallize the size which will be updated according to the next array siza 
	int sum_wait = 0; //Initiallize the sum of wait time for each order
	int sum_serv = 0; //Initiallize the sum of serve time for each order
	Order** Finish_Orders_Array = Finish_Queue.toArray(size); //Put the queue in array for traverse

	outputFile << "FT" << "     ID" << "     AT" << "     WT" << "     ST" << endl;

	//Present in the output file FT ID AT WT ST at each column
	for (int i = 0; i < size; i++)
	{
		outputFile << setw(7) << std::left << Finish_Orders_Array[i]->getFinishTime();
		outputFile << setw(7) << std::left << Finish_Orders_Array[i]->GetID();
		outputFile << setw(7) << std::left << Finish_Orders_Array[i]->getArrivalTime();
		outputFile << setw(7) << std::left << Finish_Orders_Array[i]->getwattingtime();
		sum_wait += Finish_Orders_Array[i]->getwattingtime(); // Calculate the sum of wait time for each order
		outputFile << setw(7) << std::left << Finish_Orders_Array[i]->getServTime() << endl;
		sum_serv += Finish_Orders_Array[i]->getServTime(); // Calculate the sum of serve time for each order
	}
	outputFile << endl;
	int count_real_orders_num = size;
	// Some orders may be not served then have the real number of served orders 
	//Give some statistics

	//----------------------------- Orders ----------------------------------\\
	//Represent number of all served orders

	outputFile << "Orders:" << setw(5) << std::left << count_real_orders_num << " [Norm:" << setw(5) << std::left << count_N_Orders;
	outputFile << ", Veg:" << setw(5) << std::left << count_VG_Orders << ", VIP:" << setw(5) << std::left << count_VIP_Orders << "]" << endl;;

	//----------------------------- Cooks ----------------------------------\\
	//Represent number of all Cooks

	outputFile << "Cooks: " << setw(5) << std::left << count_Cooks << " [Norm:" << setw(5) << std::left << count_N_Cooks;
	outputFile << ", Veg:" << setw(5) << std::left << count_VG_Cooks << ", VIP:" << setw(5) << std::left << count_VIP_Cooks;
	outputFile << ", Injured:" << count_injured << "]" << endl;

	//----------------------------- Averages ----------------------------------\\
	//Give the average of waiting and serving time
	//Percentage of the auto promoted orders according to all normal orders

	double Avg_Wait = (sum_wait * 1.0) / count_real_orders_num;
	double Avg_Serv = (sum_serv * 1.0) / count_real_orders_num;
	double Auto_promoted_percent = (count_autoPromoted * 100.0) / count_N_Orders;
	outputFile << "Avg Wait= " << Avg_Wait << ", Avg Serv= " << Avg_Serv << endl;
	outputFile << "Urgent orders: " << count_urgent << ", Auto promoted: " << Auto_promoted_percent << "%" << endl;

}

void Restaurant::AddtowaitQueue(Order* po)
{
	// check if the order is normal
	if (po->GetType() == TYPE_NRM)
	{
		Normal_Orders_List.insert(po);  // add it to the normal orders list
	}
	// check if the order is vegan
	else if (po->GetType() == TYPE_VGAN)
	{
		Vegan_Orders_Queue.enqueue(po); // add it to the normal orders queue
	}
	// check if the order is vip
	else if (po->GetType() == TYPE_VIP)
	{
		VIP_Orders_PrioQueue.insert(po, 'V'); // add it to the normal orders priority queue
	}

}


void Restaurant::heapify(Order* arr[], int n, int root)
{
	int largest = root; // root is the largest element
	int l = 2 * root + 1; // left = 2*root + 1
	int r = 2 * root + 2; // right = 2*root + 2

	// If left child is larger than root
	if (l < n && arr[l]->GetID() > arr[largest]->GetID())
		largest = l;

	// If right child is larger than largest so far
	if (r < n && arr[r]->GetID() > arr[largest]->GetID())
		largest = r;

	// If largest is not root
	if (largest != root)
	{
		//swap root and largest
		swap(arr[root], arr[largest]);

		// Recursively heapify the sub-tree
		heapify(arr, n, largest);
	}
}

void Restaurant::Print_Cooks_In_Break()
{
	int size = 0;
	string init;
	init = "cooks in break ( ";
	Cook** normalCook = Normal_Cooks_PrioQueue.toArray(size);
	// loop on the cooks to check who is in break and print it
	for (int i = 0; i < size; i++)
	{
		if (normalCook[i]->getinbreak())  // if the cook in break 
		{
			init.append(to_string(normalCook[i]->GetID())); // print its ID 
			init.append(" ");                               // add space
		}
	}
	Cook** veganCook = Vegan_Cooks_PrioQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		if (veganCook[i]->getinbreak())
		{
			init.append(to_string(veganCook[i]->GetID()));
			init.append(" ");
		}
	}
	Cook** vipCook = VIP_Cooks_PrioQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		if (vipCook[i]->getinbreak())
		{
			init.append(to_string(vipCook[i]->GetID()));
			init.append(" ");
		}
	}

	init.append(" )");
	pGUI->PrintMessage(init, 4, 'L');

}

void Restaurant::Print_Injured_Cooks()
{

	string init = "injured cooks ( ";
	int size = 0;
	Cook** normalCook = Normal_Cooks_PrioQueue.toArray(size);
	// loop on the cooks to check who is injured and print it
	for (int i = 0; i < size; i++)
	{
		if (normalCook[i]->isInjured())  // if the cook is injured
		{
			init.append(to_string(normalCook[i]->GetID()));  // print its ID
			init.append(" ");                                // print space
		}
	}
	Cook** veganCook = Vegan_Cooks_PrioQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		if (veganCook[i]->isInjured())
		{
			init.append(to_string(veganCook[i]->GetID()));
			init.append(" ");
		}
	}
	Cook** vipCook = VIP_Cooks_PrioQueue.toArray(size);
	for (int i = 0; i < size; i++)
	{
		if (vipCook[i]->isInjured())
		{
			init.append(to_string(vipCook[i]->GetID()));
			init.append(" ");
		}
	}

	init.append(" )");
	pGUI->PrintMessage(init, 5, 'L');
}
void Restaurant::heapSortForWaitOrders(Order* arr[], int n)
{
	// build heap
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// extracting elements from heap one by one
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(arr[0], arr[i]);

		// again call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}
