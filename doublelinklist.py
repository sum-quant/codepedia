import sys

class node (object):
    def __init__(self, data):
         self.data =data
         self.next= None
         self.prev= None
    

class list(object):
        
    def __init__( self):
         self.head = None
     
    def insert( self,k, d):
    
         new_node = node(d)
         if k==0 :
           
           new_node.next= self.head
           new_node.prev=None
           self.head= new_node
           
           
  
         else:
           curr= self.head
           
             
           count =0
           
           while(curr.next and count<=k):
               curr =curr.next
           
           
           new_node.prev=curr
           new_node.next=curr.next
           curr.next= new_node

               
    def display(self):
            curr= self.head
            #print(f"{curr.data}-><-")
            while(curr!=None):
                
                print(curr.data,"-><-",end = '')
                curr=curr.next
    
    def delete(self,  k):
            curr= self.head
            count =0;
            while(curr.next and count<k):
                 
                 count =count +1
                 curr= curr.next

          
            
            curr.prev.next=curr.next        
                 
                 
       

  
 
l= list()
l.insert(0,1)
l.insert(1,2)
l.insert(2,3)
l.insert(3,4)
l.delete(3)
l.delete(3)
l.display()

           

            

       
                      







                                                 
          
         
         
                  
           








   
