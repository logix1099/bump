/****************************************************************
/*            minheap.cpp
/*            by Gara Pruesse
/*            Oct 30, 2014
/*
/*            reads a heap in from a file
/*            builds heap, provides heap access routines
/*            
/*********************************************************************/

#include <climits>
#include "minheap.h"


minheap::minheap()
{
	n=0;
}


// argument x is the maximum size for the heap
minheap::minheap(int x)
{
	arraysize=x;
   n=0;
   lexset = new deque <int>[arraysize]; 
   heapArray = new int[arraysize]; 
   heapIndex = new int[arraysize];
   
}


minheap::~minheap()
{
   delete[] lexset;
   delete heapArray;
   delete heapIndex;
} 

bool minheap::empty()
{
   return (n<=0);
}

/*void minheap::setsize(int x)
// For the time being, we are using static arrays
{
	n=0;
	arraysize=x;
   lexset = new int[arraysize]; 
   heapArray = new int[arraysize]; 
   heapIndex= new int[arraysize]; 
}

      

void minheap::decreaseKey(int v, int k)
// v is the vertex number
{    
      int temp, i;

      if (v>= arraysize) {
         cerr<< "element "<<v<<" out of range of 0--"<< arraysize<<".\n";
         return;
      }

   	if (key[v]>= k)  // That's not a key increase!
         return;

      key[v]=k;
      i = heapIndex[v];

      int p=parent(i); 
      int vertexparent = heapArray[p];

      // bubble up till parent has greater key
      while (i!=0 && lexset[vertexparent]<k) {
        heapArray[p]=v;
        heapArray[i]=vertexparent;
        heapIndex[vertexparent]=i;
        heapIndex[v]=p;
        i=p;
        p = parent(i);
        vertexparent = heapArray[p];
      }
}
*/
int minheap::insert(deque<int> k, int v)
{
   heapArray[n]=v;
   lexset[v] = k;
   heapIndex[v]=n;
   int i=n;

   n++;


   int p=parent(i);
   int vertexparent = heapArray[p];

   while (i!=0 && lexset[vertexparent]>k) {
      heapArray[p]=v;
      heapArray[i]=vertexparent;
      heapIndex[vertexparent]=i;
      heapIndex[v]=p;
      i=p;
      p = parent(i);
      vertexparent = heapArray[p];
   }


}

int minheap::deleteMin()
{
   if (n<1) {
      cerr<< "removing from empty heap.\n";
      return(-1);
   }
   int element = heapArray[0];

   int xv, xi, pv, pi;
   xv=heapArray[n-1];
   xi=0;
   heapArray[xi]=xv;
   heapIndex[xv]=xi;
   
   n--;

   // bubble down
   int childi = smallerChild(xi);
   while  (childi<xi){
      swap(xi,childi);
      xi = childi;
      childi = smallerChild(xi);
   }

   return (element);
}

int minheap::smallerChild(int i) 
// determines if either of index i's children have a larger key
// than i's key; if not, returns 0; if so, returns the index of the 
// largest-keyed of the two children
{
   int lefti =  2*i+1;
   int righti = 2*i+2;
   
   // if righti is not in the heap, then check if left is in heap
   //if so make comparison and return 0 or lefti
   if (righti >= n) {
      if (lefti >= n) {
         return(0);
      }
      else  {
         if (lexset[heapArray[lefti]]<lexset[heapArray[i]])
            return (lefti);
         else return (0);
      }

   }


   else {// righti and lefti are true heap nodes
   
      if (lexset[heapArray[lefti]]<=lexset[heapArray[righti]]) {
         if (lexset[heapArray[i]]>lexset[heapArray[lefti]]) 
            return(lefti);
         else return (0);
         }
      else  // righti is the larger-keyed child -- is it smaller than i?
         if (lexset[heapArray[i]]>lexset[heapArray[righti]]) {
            return(righti);
         }
   }
   return(0);
}
      

void minheap::swap(int i1, int i2)
{
   int tempv1=heapArray[i1];
   int tempv2=heapArray[i2];
   heapArray[i1] = tempv2;
   heapArray[i2] = tempv1;

   heapIndex[tempv1]=i2;
   heapIndex[tempv2]=i1;

}

int minheap::parent(int i)
{
   if (i<3) return 0;
   return((int) ((i-1)/2));
}

/*int minheap::size()
{
 	return n;		
}

int minheap::minVertex()
{
	
	return heapArray[0];
}
int minheap::minKey()
{
	
	return lexset[heapArray[0]];
}


// call print_node on each node in the heap
void minheap::print_heap()
{
   for (int i=0; i<n; i++)
   {
        cout << "heap["<<i<<"]= "<<heapArray[i] <<" key is "<< key[heapArray[i]]<<endl;
   }
}

void minheap::debug_print()
{
   for (int i=0; i<n; i++)
   {
        cout << "heap["<<i<<"]= "<<heapArray[i] <<" lexset is "<< lexset[heapArray[i]]<<endl;
   }
   for (int i=0; i<arraysize; i++)
   {
        cout << i<<":"<<lexset[i]<< "  " ;
   }
}*/
