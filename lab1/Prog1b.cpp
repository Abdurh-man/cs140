#include<iostream>
using namespace std;

int main(){
		
int number;
int amount;
int sum = 0;
int max;
int min;

// the loop breakes if ctrl-d is given // end of file
while(!cin.eof()){
cin >> number;
// counts the number of inputs
amount++;
// if the inputed number is greater than the max then max should be changed
if(max < number)
	max = number;
// if the inputed nymebr is less than the min then the min should be changed
if(min > number)	
	min = number;
// sum = sum + number
sum += number;
}

// the amount is subtracted by one to fix the increment given
cout << "N   = " << amount - 1 << endl;
// the sum is subtracted by number to fix the sum
cout << "sum = " << sum - number << endl;
cout << "min = " << min << endl;
cout << "max = " << max << endl;
return 0;}
