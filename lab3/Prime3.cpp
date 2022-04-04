#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

class isprime {
	public:
		isprime(){cache.push_back(2);}
		bool operator()(int);

	private:
		void magic(int);
		bool is_prime(int);
		vector<int>cache;
};

bool isprime::operator()(int number){
	// expand the cache using maginc
	magic(number);

	// search cache if found binary_search returns true else it returns false
	return (binary_search(cache.begin(),cache.end(),number));
}

int random_number(){
	// generate random from 0-139 + 1
	return (rand() % 140 + 1);
}

bool isprime::is_prime(int number){
	int pri = 1;
	int p_sqrt = sqrt(number) + 1;
	while(++pri < p_sqrt){
		if(number % pri == 0)
			return false;
	}
	return(1 < number);
}

// if the number is not found in cache and is prime then add it to cahce
void isprime::magic(int number){
	// add one so the last value is not added twice
	for(int i = cache.back() + 1; i <= number; i++){
		if(is_prime(i))
			cache.push_back(i);
	}
}

int main(int argc, char *argv[])
{
	vector<int>number;
	vector<bool>prime;
	
	isprime pcheck;
	int N = 140;

	// if a seed is given updated N from default 140
	if(argc == 2)
		N = atoi(argv[1]);

	srand(N);
	// size of number and prime vector equals N 
	number.resize(N);
	prime.resize(N);

	// makes random numbers and places them in number this vector hold random values 
	generate(number.begin(), number.end(), random_number);
	
	// takes number vector and sees which values are prime using pcheck
	// pcheck returns true or false using the isprime operator
	// prime vector now hold 0 or 1 depending if its prime or not
	transform(number.begin(), number.end(), prime.begin(), pcheck);

	// counts the numebr of prime numebr in prime vector and assigns them to c
	int c = count(prime.begin(), prime.end(), true);

	cout << "Sequence contains "<< c << " prime numbers.\n";
}
