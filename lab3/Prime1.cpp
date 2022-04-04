#include<iostream>
#include<cmath>
using namespace std;

bool isprime(int number) 
{
	int p_check = 1;
	int p_sqrt = sqrt(number) + 1;
	// numbers that are divisible by a 2 or more its not prime
	// gets the reminder of number first using 2,3,etc if the reminder is 0 for any of them then number is not prime
	while(++p_check < p_sqrt){
		if(number % p_check == 0)
			return false;
	}
	// since 0 and 1 are not prime return true if and only if numebr is greater than 1
	return (1<number);
};

int main()
{
	int number;

	while (!cin.eof()) {
		cin >> number;
	  if (isprime(number))
	    cout << number << " is a prime number\n";
	}
}
