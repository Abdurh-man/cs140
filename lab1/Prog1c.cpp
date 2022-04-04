#include<iostream>

using namespace std;

class stats{
	public:
		void push(int);
	// print doesnt change the given values 	
		void print()const; 
	// assignes the values	
		stats();
	// these values can be accessed by the other member functions but not by the user 	
	private:	
		int N, min, max, sum;
};

stats::stats(){
	sum = 0; min; max = 0; N = 0;
}	
void stats::push(int num){
   // each time an input is given N is incremnet
	N++;
	// if the min is greater than the number given then change the min
    if(min > num)
		min = num;
	// if the max is less than the number given then chagne the max
    if(max < num)
		max = num;
	// the number given is added to sum along with what ever values sum previous had
	sum+= num;
}

void stats::print() const{
	// end of the file counts as one entry
	cout << "N   = "  << N  << endl;
	// adds the last number twice when it reaches end of file
	cout << "sum = " << sum << endl; 
	cout << "min = " << min << endl;
	cout << "max = " << max << endl;
}


int main(){
	stats s;
	int num;

	while(cin>>num)
		s.push(num);

	s.print();

	return 0;}

