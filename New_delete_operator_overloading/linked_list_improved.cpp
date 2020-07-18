#include <iostream>
#include <chrono>
using namespace std;


class Node 
{
private :
int data;
Node * next=NULL;
static Node * deleted_node; 
public:
friend class  list;

public:
void * operator new(size_t size) 
	{ 
	    //cout<<deleted_node;
		cout<< "Overloading new operator with size: " << size << endl; 
	//	void * p = ::new student(); 
		void * p = malloc(size); 
		//will also work fine 
	
		return p; 
	} 
void operator delete(void* p) 
	{    
	     
	       deleted_node=(Node *) p;
	      
		
	} 	
};

class list
{
public:
list()
{
head =NULL;
}
void insert( int data,int k);
void display();
void Delete( int k);

private:
Node  * head;
//static Node *deleted_node;

};

void list:: insert( int Data, int k)
{
Node * current =head;
//cout<< Node::deleted_node<<"sumit"<<" ";


int count =1;
if ( k==0)
{
//newnode ->next= head;
head = new Node();
head->data=Data;
}
else 
{
 while ( current->next && count <= k)
{    
   current =current ->next;
   count =count +1;
}
 
//newnode->next= current->next;
current ->next =Node::deleted_node;
current ->next->data=Data;
}

}
//template <class T>
void list::Delete( int k)
{ 
   
Node * prev =head;
Node * current =head;
 
int count =0;
if (k==0)
{
head =head->next;
}
//delete current;
else
{
 while ( current->next && count <=k)
  {
     prev = current;
     current = current ->next;
     count =count +1;
}
prev ->next=current ->next;
}
delete current;

}
//template <class T>
void list::display()
{
 Node  * curr = head;

while (curr)
{
cout<< curr->data <<" ->";
curr= curr->next;

}
cout <<endl;
}
Node * Node:: deleted_node=NULL;
int main()
{
list  L;
auto start = chrono::high_resolution_clock::now(); 
L.insert( 0, 0);
L.Delete(0);
L.insert(0,0);
L.insert(1,1);
auto end = chrono::high_resolution_clock::now(); 
auto duration =  std::chrono::duration_cast<std::chrono::microseconds>(end - start); 
cout<< duration.count()<<"us"<<endl;
L.display();
//L.Delete(2);
//L.display();
}


















