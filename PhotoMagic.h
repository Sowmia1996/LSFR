#ifndef PHOTOMAGIC_H
#define PHOTOMAGIC_H
#include<fstream>
#include<sstream>
#include<vector>
#include"LSFR.h"
using namespace std;

class PhotoMagic{
	private :
	vector<vector<int>>input_data;
	vector<vector<int>>encrypted;
	ofstream outfile_encrypted;
	ofstream outfile_decrypted;
	
	public:
	PhotoMagic();
	PhotoMagic(ifstream &);
	void read(ifstream &);//reads the data file and stores in input_data
	void encrypt(string,string);//encrypts the input data and stores it outfile_encrypted
	void decrypt(string,string);//decrypts the encrypted and writes to outfile_decrypted
};
PhotoMagic::PhotoMagic()
{}
PhotoMagic::PhotoMagic(ifstream &infile)
{
	vector<vector<string>>data;
	string s,t;
	while(infile)
	{
		
		if(!getline(infile,s))
			break;
		istringstream ss(s);
		vector<string>temp;
		
		while(ss)
		{
			
			if(!getline(ss,t,','))
				break;
			temp.push_back(t);
		}
		data.push_back(temp);
	}
	if(!infile.eof())
	{
		cerr<<"End of file";
	}
	int x;
	for(int i=0;i<data.size();i++)
	{
		vector<int>temp;
		for(int j=0;j<data[0].size();j++)
		{
			t=data[i][j];
			stringstream number(t);
			x=0;
			number>>x;
			temp.push_back(x);
		}
		input_data.push_back(temp);
	}
}
void PhotoMagic::read(ifstream & infile)
{
	vector<vector<string>>data;
	string s,t;
	while(infile)
	{
		
		if(!getline(infile,s))
			break;
		istringstream ss(s);
		vector<string>temp;
		
		while(ss)
		{
			
			if(!getline(ss,t,','))
				break;
			temp.push_back(t);
		}
		data.push_back(temp);
	}
	if(!infile.eof())
	{
		cerr<<"End of file";
	}
	int x;
	for(int i=0;i<data.size();i++)
	{
		vector<int>temp;
		for(int j=0;j<data[0].size();j++)
		{
			t=data[i][j];
			stringstream number(t);
			x=0;
			number>>x;
			temp.push_back(x);
		}
		input_data.push_back(temp);
	}
}
void PhotoMagic::encrypt(string filename,string seed)
{
	//now we encrytp  by XOR-ing the data with a different 
	// newly-generated,random 16-bit integer returned by LFSR.generate(16)
	bool array[]={0,0,0,0,0,1,0,1,0,0,1,1}; //primitve polynomial of degree 12
	LSFR lsfr_en("011010000101",array); //12 bit seed
	int x;
	for(int i=0;i<input_data.size();i++)
	{
		vector<int>temp;
		for(int j=0;j<input_data[0].size();j++)
		{
			x=lsfr_en.generate(16);
			temp.push_back(x^input_data[i][j]);
		}
		encrypted.push_back(temp);
	}
	//we now write the encrypted data to a new text file
	
	outfile_encrypted.open(filename);
	for(int i=0;i<encrypted.size();i++)
	{
		for(int j=0;j<encrypted[0].size()-1;j++)
		{
			outfile_encrypted<<encrypted[i][j]<<',';
		}
		outfile_encrypted<<encrypted[i][encrypted[0].size()-1]<<endl;
	}
	outfile_encrypted.close();
}


void PhotoMagic::decrypt(string filename,string seed)
{
	bool array[]={0,0,1,0,0,0,0,0,0,0,1};
	LSFR lsfr_de("01101000010",array);
	vector<vector<int>>decrypted;
	int x;
	for(int i=0;i<encrypted.size();i++)
	{
		vector<int>temp;
		for(int j=0;j<encrypted[0].size();j++)
		{
			x=lsfr_de.generate(16);
			temp.push_back(x^encrypted[i][j]);
		}
		decrypted.push_back(temp);
	}
	//we now write the encrypted data to a new text file
	

	outfile_decrypted.open(filename);
	for(int i=0;i<decrypted.size();i++)
	{
		for(int j=0;j<decrypted[0].size()-1;j++)
		{
			outfile_decrypted<<decrypted[i][j]<<',';
		}
		outfile_decrypted<<decrypted[i][decrypted[0].size()-1]<<endl;
	}
	outfile_decrypted.close();
}
#endif

	