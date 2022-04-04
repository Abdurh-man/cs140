#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iomanip>
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

// only prime should be changed the rest are const
void extract_prime(const vector<int> &number, const vector<bool> &vecTrue, vector<int> &prime){
	// note number.size is the same as vecTrue.size	
	for(int i = 0; i < number.size();i++){
		// if the value at vecTrue[i] is true then push_back number[i] to prime
		if(vecTrue.at(i))
				prime.push_back(number.at(i));
	}
}
// the vectore shouldnt be changed
void print(const vector<int> &prime){
	for(int i = 0; i < prime.size(); i++){
		cout << setw(4) << prime.at(i);
	// after 20 number have been printed make a new line	
		if(i % 20 == 19)
		cout << endl;
	}
}



int main(int argc, char *argv[])
{
	vector<int>number;
	vector<bool>vecTrue;

	isprime pcheck;
	int N = 140;

	// if a seed is given updated N from default 140
	if(argc == 2)
		N = atoi(argv[1]);

	srand(N);
	// size of number and prime vector equals N
	number.resize(N);
	vecTrue.resize(N);

	// makes random numbers and places them in number this vector hold random values
	generate(number.begin(), number.end(), random_number);

	// takes number vector and sees which values are prime using pcheck
	// pcheck returns true or false using the isprime operator
	// prime vector now hold 0 or 1 depending if its prime or not
	transform(number.begin(), number.end(), vecTrue.begin(), pcheck);

	// counts the numebr of prime numebr in prime vector and assigns them to c
	int c = count(vecTrue.begin(), vecTrue.end(), true);

	cout << "Sequence contains "<< c << " prime numbers.\n";

	// vector hold prime values
	vector<int>prime;
	
	// [1,2,3,5,10,140,130,101,2,3]
	// [F,T,T,T, F ,F , F , T ,T,T]
	// []
	
	// using vector number and vecTrue vector prime holds only time prime values after extraction
	
	extract_prime(number,vecTrue,prime);
	// after extartion prime contents
	// [2,3,5,101,2,3]

	cout << "All numbers in order appearance:\n";

	print(prime);

	
	
	sort(prime.begin(), prime.end());
	// after sort prime contents
	// [2,2,3,3,5,101]

	vector<int>::iterator prime_it;

	// unique returns an iterator to where the repeated numbers start
	prime_it = unique(prime.begin(), prime.end());
	// after unique prime contents
	// [2,3,5,101,2,3]

	prime.erase(prime_it, prime.end());
	// after erase prime contents
	//[ 2,3,5,101]
	cout << "\nUnique values in numerical order:\n";

	print(prime);

	return 0;
}


