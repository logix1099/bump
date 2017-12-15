#include <stdlib.h>
#include <fstream>
#include <vector>
#include "heap.h"
#include <deque>
#include "minheap.h"
#include <time.h>
using namespace std;
int main(int argc, char* argv[])
{
	int bumpCount = 0;

	int u,v,n,k, prevMinNode, prevMaxNode;
	int nextLexNum = 1;
	int prevLexNum = 0;
	int minNode;
	int maxNode;
	bool bump[n];
	ifstream f;
	vector<int> *LowerCover;
	vector<int> *UpperCover;
	vector<int>::iterator Lowerneighb;
	vector<int>::iterator Upperneighb;
	deque<int> lexset[n];
	f.open(argv[1]);

	if (argc<2)
	{
		cout<<"forgot a filename to open"<<endl;
		return 0;
	}
	if (argc >2)
  		srand (atoi(argv[2]));
	else
  		srand (time(NULL));

	if (!f)
	{
		cerr<<"File not openable. "<<endl; return 0;
	}

	f >> n;
	int key[n];
	int linext[n];
	int numLCovers[n];
	int numUCovers[n];
	LowerCover = new vector<int>[n];
	UpperCover = new vector<int>[n];

	for(int i=0; i<n; i++)
	{
   		numLCovers[i] = 0;
   		numUCovers[i] = 0;
   	}
   	for(int i = 0; i<n; i++)
   	{
   		bump[i] = false;
   	}

	if (n>100000) { cerr<<"n too large: "<<n<<endl; return 0;} // arbitrary
	f >> u;

	while (u<n && f) //generates the less than and tranClosure matrices
	{

   		f >> v;

		while (v <n && f)
      		{
      		UpperCover[u].push_back(v);
         	LowerCover[v].push_back(u);
         	numLCovers[v]++;
         	numUCovers[u]++;
         	f >> v;

      		}

      		f >> u;

   	}
   	clock_t start;
	start = clock();
   	heap H(n);
   	minheap M(n);



   	//start lex labeling
	for (int i=0; i<n;i++)
	{
		key[i] = 12;
	}

	for (int i=n-1; i>=0;i--)
	{
		if (numUCovers[i] == 0)
		{
			key[i] = 0;
			Lowerneighb = LowerCover[i].begin();
			while (Lowerneighb != LowerCover[i].end())
			{
				lexset[*Lowerneighb].push_front(key[i]);
				Lowerneighb++;
			}
		}
	}
	for (int i=0; i<n;i++)
	{
		if (key[i] == 0)
		{
			Lowerneighb = LowerCover[i].begin();
			while (Lowerneighb != LowerCover[i].end())
			{
				cout<<i<<" "<<*Lowerneighb<<" "<<numUCovers[*Lowerneighb]<<endl;
				numUCovers[*Lowerneighb]--;
				if (numUCovers[*Lowerneighb] == 0)
					{
						M.insert(lexset[*Lowerneighb],*Lowerneighb);
					}
						Lowerneighb++;
			}
		}
	}

   	while(!M.empty())
   	{
   		minNode = M.deleteMin();
   		//cout<<minNode<<endl;
   		//assign next lex num
   			key[minNode] = nextLexNum;
   			nextLexNum++;

   		//build lexset
   		Lowerneighb = LowerCover[minNode].begin();
   		while (Lowerneighb != LowerCover[minNode].end())
			{
			lexset[*Lowerneighb].push_front(key[minNode]);
			numUCovers[*Lowerneighb]--;
			Lowerneighb++;
			}
			//add to minheap
			if (M.empty())
   		{
   			for (int i=0; i<n;i++)
				{
					if (numUCovers[i] == 0 && key[i] == 12)
					{
						M.insert(lexset[i],i);
					}
				}
   		}
   	}

   	//end lex labeling
	//begin building linear extention
    	for (int i = 0; i<n; i++)
	{
		if (numLCovers[i] == 0)
		{
			H.insert(key[i],i);
		}
	}
	int j = 0;


   	maxNode = H.deleteMax();
   	linext[j] = maxNode;
	if(H.empty())
        {
        	Upperneighb = UpperCover[maxNode].begin();
                while(Upperneighb != UpperCover[maxNode].end())
                {
                	numLCovers[*Upperneighb]--;
                        if (numLCovers[*Upperneighb] == 0)
                        {
                        	H.insert(key[*Upperneighb],*Upperneighb);
                           bump[maxNode] = true;
                        }
                        Upperneighb++;
                }
	}

	j++;
  	while(!H.empty())
        {
		prevMaxNode = maxNode;
   		maxNode = H.deleteMax();
   		linext[j] = maxNode;
   		j++;
   		//take prev max and puts it upper covers in heap

   		Upperneighb = UpperCover[prevMaxNode].begin();
   		while(Upperneighb != UpperCover[prevMaxNode].end())
  		{
			numLCovers[*Upperneighb]--;
   			if (numLCovers[*Upperneighb] == 0)
  			{
  				H.insert(key[*Upperneighb],*Upperneighb);
  			}
  			Upperneighb++;
  		}
  		//takes max and puts it uppercovers into the heap if
  		//heap is empty
  		if(H.empty())
  		{
   			Upperneighb = UpperCover[maxNode].begin();
   			while(Upperneighb != UpperCover[maxNode].end())
   			{
   				numLCovers[*Upperneighb]--;
   				if (numLCovers[*Upperneighb] == 0)
   				{
   					H.insert(key[*Upperneighb],*Upperneighb);
   					bump[maxNode] = true;
   				}
   				Upperneighb++;
   			}
   		}
     	}

	for (int i = 0;i < n;i++)
	{
		cout <<"("<<linext[i]<<")"<<key[linext[i]];
		if (bump[i] == true)
		{
			cout<<"--";
			bumpCount++;
		}
	}
	cout <<"["<<bumpCount<<" Bump] (Time is "<<(clock()-start)/(double(CLOCKS_PER_SEC/1000))<<")";
   	cout<<endl;
   	f.close();
}
