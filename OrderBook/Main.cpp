/*
 * Main.cpp
 *
 *  Created on: May 3, 2015
 *      Author: lzy
 */

#include <iostream>
#include <functional>
#include "MatchingEngine.h"
#include<chrono>
using namespace std;

void usage()
{
    cout << "-------------Matching Engine---------------" << endl;
    cout << endl;
}

int main( int argc, char** argv )
{ 
    usage();
    string infile = "orders.csv";
    Match::MatchingEngine engine;
    std::chrono::steady_clock::time_point start;
    engine.Run( infile );
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    engine.Display_OrderBook();
}


