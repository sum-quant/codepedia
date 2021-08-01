#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <cstring>
#include<map>
#include "MatchingEngine.h"
#include "Order.h"
# define isBuy(b) b=="BUY"? true:false

void Match::MatchingEngine::Run(const string infile)
{
    FILE* file = fopen(infile.c_str(), "r");
    if (NULL == file) {
        fprintf(stderr, "Cannot open file at %s\n", infile.c_str());
        //return -1;
    }

    OrderBook::Timestamp time;
    OrderBook::ID   id;
    char action[5];
    char  Side[5];
    OrderBook::Price price;
    OrderBook::Qunatity qt;
    while (!feof(file)) 
    {
        int nItemsRead = fscanf(file, "%u,%u,%[^,],%[^,],%lu,%lu\n",
            &time, &id, action, Side, &price, &qt);
        if (nItemsRead != 6)
        {
            cout << "Bad line" << endl;
        }
        OrderBook::order* orderptr = new  OrderBook::order(time, id, action, Side, price, qt);
        Match::MatchingEngine::ManageOrder(orderptr);
    }
}

    void Match::MatchingEngine::ManageOrder( OrderBook::order * orderptr)
    {
        string str = orderptr->type;
        if(!str.compare("A"))
        {
            OrderBook::Qunatity &tradequantity = orderptr->quantity;
            if (orderptr->quantity > 0)
            {
                Match::MatchingEngine::ExecuteTrade(orderptr, tradequantity);
            }
            if (tradequantity > 0)
            {
                Match::MatchingEngine::AddOrderBook(*orderptr);
            }
        }
        else if(!str.compare("M"))
        {
            OrderBook::Qunatity tradequantity = orderptr->quantity;
            if (orderptr->quantity > 0)
            {
                Match::MatchingEngine::ModifyOrder(*orderptr);

            }

        }
        else 
        {
            OrderBook::Qunatity tradequantity = orderptr->quantity;
            if (orderptr->quantity > 0)
            {
                Match::MatchingEngine::ReduceOrderBook(*orderptr);

            }

        }
    }

    void Match::MatchingEngine::ExecuteTrade( OrderBook::order* orderptr, OrderBook::Qunatity& tradequantity)
    {
        string sside = orderptr->side;
        if (isBuy(sside))
        {
            for (auto it = Asks.begin(); (it != Asks.end()) && (tradequantity > 0);)
            {
                if (orderptr->price >= it->first)
                {
                    OrderBook::Qunatity currQuantity = it->second.quantity;
                    OrderBook::Qunatity execQuantity = min(currQuantity, tradequantity);
                    tradequantity = tradequantity - execQuantity;
                    it->second.quantity = currQuantity >= execQuantity ? currQuantity - execQuantity : 0;
                    if (it->second.quantity == 0)
                    {   
                        indexOrder.erase(it->second.OrderID);
                        Asks.erase(it++);
                       
                    }
                    else
                    {
                        ++it;
                    }
                }
                else
                    break;
            }

        }
        else
            for (auto it = Bids.rbegin();(it != Bids.rend() )&& (tradequantity > 0);)  // it++ here fails in c++17 
                
            {
                if (orderptr->price <= it->first)  /// it++ here fails in c++17 
                {
                    OrderBook::Qunatity currQuantity = it->second.quantity;
                    OrderBook::Qunatity execQuantity = min(currQuantity, tradequantity);
                    tradequantity = tradequantity - execQuantity;
                    it->second.quantity = currQuantity >= execQuantity ? currQuantity - execQuantity : 0;
                    if (it->second.quantity == 0)
                    {
                        indexOrder.erase(it->second.OrderID);
                        Bids.erase(std::next(it).base()); //  gets cached locally
                        
                    }
                    else
                    {
                        ++it;
                    }
                }
                else
                    break;
                

              
            }

    }
   

    void Match::MatchingEngine::AddOrderBook(const OrderBook::order &order)
    {
        
        string sside = order.side;

        if (isBuy(sside))
        {
            OrderHashing ob;
            auto itBids=  Bids.emplace(order.price, order);
            strcpy(ob.side, order.side);
            ob.indexMap = itBids;
            indexOrder[order.OrderID] = ob;
          }
        else
        {
            OrderHashing ob2;
            strcpy(ob2.side, order.side);
            auto itAsks= Asks.emplace(order.price, order);
            ob2.indexMap = itAsks;
            indexOrder[order.OrderID] = ob2;
        }
    }


    void Match::MatchingEngine::ReduceOrderBook( const OrderBook::order& order)
    {
        auto it = indexOrder.find(order.OrderID);
        
        if (it != indexOrder.end())
        {
            
           // auto mapit = it->second.indexMap;
            auto hashobj = &it->second;
            auto  mapit = hashobj->indexMap;
            auto &currQuant = mapit->second.quantity;
            string sside = hashobj->side;

            auto reducedQuantity =  currQuant - order.quantity; 
            if (reducedQuantity < 0)
            {
               
                if (isBuy(sside))
                {
                    Bids.erase(mapit);
                }
                else
                {
                    Asks.erase(mapit);
                }
                indexOrder.erase(order.OrderID);
            }
            else

                currQuant = reducedQuantity;
            
            
        }
    }
    void Match::MatchingEngine::ModifyOrder(const OrderBook::order& order)
    {
        auto it = indexOrder.find(order.OrderID);

        if (it != indexOrder.end())
        {

            
            auto hashobj = &it->second;
            auto  mapit = hashobj->indexMap;
            auto &currQuant = mapit->second.quantity;
            string sside = hashobj->side;

            currQuant = order.quantity;


        }
    }

    void Match::MatchingEngine::Display_OrderBook()
    {
        if (!Bids.empty())
        {
            cout << "-----------Bids side Order--------------\n";
            cout << Bids;
        }
        
          
        if (!Asks.empty())
        {

            cout << "-----------Asks side Order--------------\n";
            cout << Asks;
        }
          
    }
    
