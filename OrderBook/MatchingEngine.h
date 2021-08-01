#pragma once
#ifndef MATCHINGENGINE_H_
#define MATCHINGENGINE_H_

#include "Order.h"
#include<map>
#include<unordered_map>
#include<functional>
#include<string>
using namespace std;
namespace Match
{

class  MatchingEngine
{
public:
	MatchingEngine() {};
	void Run(const string file);
	void Display_OrderBook();
	
private:

	multimap <OrderBook::Price, OrderBook::order> Bids;
	multimap <OrderBook::Price, OrderBook::order> Asks;
	void ManageOrder( OrderBook::order*);
	void ExecuteTrade( OrderBook::order*, OrderBook::Qunatity &);
	void AddOrderBook(const OrderBook::order&);
	void ReduceOrderBook(const OrderBook::order&);
	void OrderMatching(const OrderBook::order&);
	void ModifyOrder(const OrderBook::order&);
public:
	class OrderHashing
	{  
	 
	public:
		OrderBook::OrderSide side;
		multimap<OrderBook::Price, OrderBook::order>::iterator indexMap;
	};
    
	unordered_map<OrderBook::ID, Match::MatchingEngine::OrderHashing> indexOrder;

	friend std::ostream& operator<< (std::ostream& out, const MatchingEngine& point);
};
template<class A,class B>
std::ostream& operator<< (std::ostream& os, const std::multimap< A, B > m)
{ 
	
		for (const auto& i : m) {    /////-----------------------------------------------------------
			os << "OrderID: "<<i.second.OrderID <<","<<"Price: " << i.first << ",";
			os << "Quantity: " << i.second.quantity << std::endl;
		}
	
	return os; 
}
}
#endif