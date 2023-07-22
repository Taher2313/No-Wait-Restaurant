#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"..\Generic_DS\List.h"
#include"..\Generic_DS\PriorityQueue.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;              // Responsible for the interface
	int timeStep; 
	int autoPromotionLimit; // the limit which the normal order will turn automatically to VIP 
	int VIP_wait_limit;     // the limit which the VIP order will turn automatically to urgent order 
	int medicalRest;        // Time cook will take for rest
	float injuring_probability;
	// --------------------------------- Events -------------------------------------\\

	Queue<Event*> EventsQueue;	   //Queue of all events that will be loaded from file

	template < typename T>         //The next function is template function
	void FillDrawingList(T* obj);  //Take cooks or orders to draw them

	// --------------------------------- Orders -------------------------------------\\



	List<Order*> Normal_Orders_List;                // this must be a list to deal with cancellation and promotion
	Queue<Order*> Vegan_Orders_Queue;               // this will stay queue as orders are sorted depending on arrival time only
	PriorityQueue<Order*> VIP_Orders_PrioQueue;     // this must be a priority queue depending on the priority equation
	List <Order*> Serve_List;                       // this will be a list that will sort 
	  							       	  	        //  orders depending on their interance in serving which 
								                    // and also to remove from inside the list not only the begging
								                    // to remove the finished orders

	Queue<Order*> Finish_Queue;  // this must be a queue as the orders are sorted
								 // depending on their finishing time and this will 
								 // contain all kinds of orders

	
	   
	// --------------------------------- Cooks  -------------------------------------\\


	PriorityQueue <Cook*> Normal_Cooks_PrioQueue;     // all cooks must be put in priority queue so they are soreted 
	PriorityQueue <Cook*> Vegan_Cooks_PrioQueue;      // depending on their speed , this modification was done due to the 
	PriorityQueue <Cook*> VIP_Cooks_PrioQueue;        // the bonus section only , but without the bonus they would be 
	
	
	//Some needed variables in some functions

	//Summation for orders are dine from serving in each order type
	int Total_num_Ser_Normal_Ord; 
	int Total_num_Ser_Vegan_Ord;  
	int Total_num_Ser_Vip_Ord;    
	int order_before_break;       //Number of orders must be done by each order before break time done by each cook
public:
	


	Restaurant();        //Constructor
	~Restaurant();       //Destructor

	int getTimeStep();   //Getter for TimeStep

	// --------------------------------- Simulation -------------------------------------\\


	void RunSimulation(); //Simulator to choose the GUI mode
		
	// ----------------------------------- Events -------------------------------------\\

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	
	bool RemoveFromnList(int id);       // Remove the cancelled order from normal list  
	void GetProOrder(int id);           // Get the Promoted Order to be put in VIP queue  

	void Generate_R();                  // generate the random number R so
	                                    // we can compare it with the injuring probability

	void Decrement_Orders_Count_For_Cancellation();
	

	// ----------------------------------- Setter and Getter -------------------------------------\\

	void setmedicalRest(int mp);      
	int getmedicalRest();            //Setters and Getters so they can be accessed in Injured Event

	// ----------------------------------- Orders -------------------------------------\\

	void AddtowaitQueue(Order* po);                  //Add each order in the suitable queue according 
	                                                 //to type of orders who's status are wait

	void heapSortForWaitOrders(Order* arr[], int n); //Algorithim to sort data use heap sort
	void heapify(Order* arr[], int n, int root);     //Turn data into heap to facilitate its sort
	
	
	// ----------------------------------- OutputFile Needs-------------------------------------\\

	//Count for some statistics to be drawn in the output file
	//Initialized in the constructor and modified in the output file function

	int count_Orders;
	int count_N_Orders;
	int count_VG_Orders;
	int count_VIP_Orders;

	int count_Cooks;
	int count_N_Cooks;
	int count_VG_Cooks;
	int count_VIP_Cooks;

	int count_autoPromoted;
	int count_urgent;
	int count_injured;
	// -------------------------------  Input file --------------------------------------------------\\


	void loadFile(ifstream& fileName); //Function which reads the input file and saves all values in other variables to be then used
	// ------------------------------------------ Simulation -----------------------------------------------\\
	// main function used in the simulation so we can divide the whole wrok into modules


	void PrintingTimestep();                               //  2
	void Reduce_avaliblity_cook();                         //  3
	void ReduceMedicalRest();                              //  4
	void DrawingAllAssignedCooksInTheLastTimeTimestep();   //  6
	void MovingOrdersFromServingToDone();                  //  7
	void serve_waiting_vip();                              //  8  ==> function for urgent orders
	void AssigningOrdersToCooks();                         //  9
	void AutopromotionOfOrders();                          //  10
	void print_number_of_avalible_cook();                  //  11
	void Print_Injured_Cooks();                            //  12 ==> Print injured cooks in GUI status bar
	void Print_Cooks_In_Break();                           //  13 ==> Print cooks in break in GUI status bar
	void DrawAllCooks();                                   //  14
	void DrawingAllWaitingOrders(int mode );               //  15
	void DrawingAllCurrentlyServingOrders();               //  16
	void FinshingOfDrawingAllDoneOrders();                 //  17
	void OutputFileOptimization(ofstream& outputFile);     //  18
	void Dynamic_Deallocation();                           //  19  
};

#endif