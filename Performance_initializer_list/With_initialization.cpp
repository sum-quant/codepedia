#include<iostream> 
using namespace std; 

class A 
{ 
	// data members of A 
public: 
	A()		 { cout << "\n A's constructor"; /* Initialize data members */ } 
	A(const A &a) { cout << "\n A's Copy constructor"; /* Copy data members */ } 
	A& operator= (const A &a) // Assignemt Operator 
	{ 
		// Handle self-assignment: 
		if(this == &a) return *this; 

		// Copy data members 
		cout << "\n A's Assignment Operator"; return *this; 
	} 
}; 

class B 
{ 
	A a; 
	// Other members of B 
public: 
	B(A &a):a(a) { cout << "\n B's constructor"; } 
}; 

int main() 
{ 
	A a; 
	B b(a); 
	return 0; 
} 
