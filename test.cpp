#include "PhotoMagic.h"
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	PhotoMagic obj;
	ifstream infile;
	infile.open("eleph_in.txt");
	obj.read(infile);
	obj.encrypt("eleph_encrypted.txt","011010000101");
	obj.decrypt("eleph_decrypted.txt","011010000101");
	return 0;
}