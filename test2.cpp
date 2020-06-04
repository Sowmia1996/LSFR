#include<iostream>
#include "LSFR.h"
#include<string>
using namespace std;
int main()
{
	bool array[]={0,0,0,0,0,1,0,1,0,0,1,1};
	string seed="011010000101";
	LSFR obj(seed,array);
	//single ouptput by lsfr
	cout<<"The output produced by calling the function step() is:"<<endl;
	cout<<obj.step()<<endl;
	//producing 10 random 8 bit numbers
	cout<<"testing generate() method by producing 8 bit random numbers"<<endl;
	for(int i=0;i<10;i++)
		cout<<obj.generate(8)<<endl;
	//producing 10 random 16 bit numbers
	cout<<"testing generate() method by producing 16 bit random numbers"<<endl;
	for(int i=0;i<10;i++)
		cout<<obj.generate(16)<<endl;
	return 0;
}