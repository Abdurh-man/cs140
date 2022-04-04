#include<iostream>

using namespace std;

//Pointer refrence
// p = &X[1] ==> *(P-1) = X[0]
//
// int n = 3
// int *p = &n
// int **q = &p
//
// p == &n adds of var
// *p == n values
// q == *p addr of ptr
// *q == &n addr of variable
// **q == n values


int strlen(char *s){
int i = 0;
// breakes the array of charaters one by one
while(*s != '\0'){
	*s = *(s + i);
	i++;}
// i is subtracted since the null varialb is counted
return (i - 1);}

int main (int argc , char * argv[]){

	cout << "Num args = " <<argc << endl;
	for(int i; i < argc; i++){
	
	// arg now hold the value of argv
	char *arg = argv[i];
	// assignes the addres of argv to addr
	char **add = &argv[i];
	
	// and *arg gets a single character	
	cout << add << ' ' << arg;
	cout<< " (strlen="  << strlen(arg) << ')' << endl;
	}


	return 0;}
