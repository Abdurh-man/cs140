#include<iostream>

using namespace std;

//Write a C++ program called hw_1a.cppthat prints the value of argc followed by the addresses of each 
//argvargument as well the corresponding (C-style) strings. The program must contain everything needed 
//to compile. The following is an example output:
//
//unix> ./hw_1a This is great
//Num args = 4
//argv[0] = 0x7fffeb3fb1f8 ./hw_1a 
//argv[1] = 0x7fffeb3fb200 This
//argv[2] = 0x7fffeb3fb208 is
//argv[3] = 0x7fffeb3fb210 great

int main (int argc , char * argv[]){

	cout << "Num args = " << argc << endl;

	int i = 0;

	while(i < argc){
	string arg = argv[i];
	string *addr = &arg;
	cout << addr << ' ' << *addr << endl;
	addr = NULL;
	delete addr;
	i++;}

	return 0;}
