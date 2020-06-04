#ifndef LSFR_H
#define LSFR_H
#include<iostream>
#include<string>
using namespace std;

struct Node
{
	bool data;
	Node *next;
	
	Node(bool x)
	{
		this->data=x;
		next=NULL;	
	}
};

class LSFR
{
	private:
	string seed;
	bool *tap;//pointing to the tap sequence array
	Node *head;  //to point to the first elemt of flipflop
	Node *tail;   //to point to last element of flip-flops
	
	public:
	LSFR(string,bool*);
	void display();//output lsfr values in a string
	bool step();//output for one clockcycle
	long generate(int);//takes an integer-k and returns a k-bit random number
	
};

LSFR::LSFR(string seed,bool *tap)
	{
		int m=seed.length();
		bool flag=0;
		for(int i=0;i<m;i++)
		{
			if(seed[i]=='1')//atlest one bit is 1 ..valid seed
				flag=1;
			if(seed[i]!='1' && seed[i]!='0') //non binary values not allowed
				flag=0;
		}
		//if seed is valid ,initialize lsfr with the seed bit values
		if(flag==1)
		{
			head =new Node(seed[0]-'0');
			Node*trvlptr=head;
			for(int i=1;i<=m-1;i++)
			{
				trvlptr->next=new Node(seed[i]-'0');
				trvlptr=trvlptr->next;
			}tail=trvlptr;
			this->seed=seed;
		}
		//if seed is invalid,initilise lsfr with all zeroes
		else
		{
			string temp="";
			for(int i=0;i<m;i++)temp+='0';
			this->seed=temp;
			head =new Node(0);
			Node*trvlptr=head;
			for(int i=1;i<=m-1;i++)
			{
				trvlptr->next=new Node(0);
				trvlptr=trvlptr->next;
			}tail=trvlptr;
		}
		//assign the tap values to respective flipflops in lsfr
		this->tap=tap;
	}
//mem function that displays the state of the flip-flops currently	
void LSFR::display()
{
	Node *trvlptr=head;
	while(trvlptr!=NULL)
	{
		cout<<trvlptr->data;
		trvlptr=trvlptr->next;
	}
	
}

//member function that outputs the LSFR's output for first clockimpulse
bool LSFR::step()
{
	
	//calculating the feedback loop value
	int i=0;
	Node*trvlptr=head;
	int result=0;
	while(trvlptr!=NULL)
	{
		if(tap[i]==1)
		{
			result+=trvlptr->data;
		}
	trvlptr=trvlptr->next;
	i++;
	}
	result=result%2;
	
	//now inserting the feedback loop value in first flipflop
	Node*temp=head;
	head=new Node(result);
	head->next=temp;
	
	//storing the last flip-flop val and deleting the last element
	bool res=tail->data;
	trvlptr=head;
	while(trvlptr->next->next!=NULL)trvlptr=trvlptr->next; 
	temp=trvlptr->next;
	trvlptr->next=NULL;
	tail=trvlptr;
	delete temp;
	
	//return output of lsfr
	return res;
}
//member fucntion that outputs a k-bit random number
long LSFR::generate(int k)
{
	long result=0;
	int count=1;
	for(int i=0;i<k;i++)
	{
		result+=(this->step())*count;
		count=2*count;
	}
	return result;
}
#endif

		
		
		
		
		
			
			
			
			
			
			
	