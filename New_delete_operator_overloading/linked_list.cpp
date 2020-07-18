#include <iostream>
#include <chrono>

using namespace std;


class Node 
{
private :
int data;
Node * next;

public:
friend class  list;
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
	     
	       free(p);
	      
		
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
};

void list:: insert( int Data, int k)
{
Node * current =head;
Node * newnode = new Node  ();
newnode ->data = Data;
int count =1;
if ( k==0)
{
newnode ->next= head;
head = newnode;
}
else 
{
 while ( current->next && count <= k)
{    
   current =current ->next;
   count =count +1;
}
 
newnode->next= current->next;
current ->next =newnode;
}

}
//template <class T>
void list::Delete( int k)
{ 
Node * prev =head;
Node * current =head;
int count =0;
if (k==0)
head =head->next;

else
{
 while ( current->next && count <=k)
  {
     prev = current;
     current = current ->next;
     count =count +1;
}
prev ->next=current ->next;
delete current;
}

///
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


















