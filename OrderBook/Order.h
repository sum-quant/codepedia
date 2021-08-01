
#ifndef ORDER_H_
#define ORDER_H_

#include<string>
using namespace std;
namespace OrderBook
{
    typedef unsigned int Timestamp;
	typedef unsigned int ID;
	typedef char Action[5];
	typedef char OrderSide[5];
	typedef unsigned long Price;
	typedef  long Qunatity;

	class order
	{ 
	    public:
		Timestamp time;
		ID OrderID;
		Action type;
		OrderSide side;
		Price price;
		Qunatity quantity;
		order(Timestamp time, ID orderID, Action type, OrderSide side, Price price, Qunatity quantity) 
		{  
			this->time = time;
			this->OrderID = orderID;
			strcpy(this->type, type);
			strcpy(this->side, side);
			//this->type = type;
			//this->side = side;
			this->price = price;
			this->quantity = quantity;

		};

		
	};
}
#endif